#include <iostream> 
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

bool isValid(const string&, int);



int main(int argc,char* argv[])
{

    if (argc != 3)
    {
        cerr << "Неправильно указаны аргументы при запуске\nИспользуйте образец ./text_filter <входной_файл> <выходной_файл>" <<endl;
        return 1;
    }
    string inputPath = argv[1];
    string outputPath = argv[2];

    ifstream in(inputPath);
    if (!in.is_open())
    {
        cerr<<"Ошибка при открытии файла"<<endl;
        return 1;
    }

    string line{};

    string header{};
    string targetColumn{"Z"};
    int targetPosition{};
    bool targetFlag{};

    vector<string> validLines {};

    if(getline(in,header))
    {
        int counter{};
        stringstream ss(header);
        string str;

        while(getline(ss,str,','))
        {
            if (str ==targetColumn)
            {
                targetPosition = counter;
                targetFlag = true;
                break; 
            }
            ++counter;
        }
    }

    if (!targetFlag)
    {
        cerr<<"Искомого столбца нет в заголовке файла"<<endl;
        return 1;

    }

    while(getline(in,line))
    {
        if (line.empty())
        {
            continue;
        }
        if(isValid(line,targetPosition))
        {
            validLines.push_back(line);
        }
    }


    ofstream out(outputPath);
    if(out.is_open())
    {
        out << header<<endl;
        for(int i{};i<validLines.size();++i)
        {
            out << validLines[i]<<endl;
        }
    }

    in.close();
    out.close();
    
    
}

bool isValid(const string& line, int targetPosition)
{
    stringstream ss(line);
    string str;

    int counter{};
    while(getline(ss,str,','))
    {
        if (counter ==targetPosition)
        {
            if(stod(str) <0)
            {
                return false;
            }
        }
        ++counter;
    }
    return true;

}
