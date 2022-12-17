#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <cstdlib>
#include <time.h>
using namespace std;

class home
{
protected:
    string filename;

public:
    home() {}

    home(string fname)
    {
        filename = fname;
        // cout << "\n### Welcome To HTML Parser ###\n";
    }
};

class extractor : public home
{
protected:
    string filename;
    string temp;
    string paragraph = "";

public:
    extractor() {}
    extractor(string fname) : home(fname)
    {
        // cout << "\n### Extracting File ###\n\n";
    }
    void openExtractor(string filen = "")
    {

        // cheking file name is present
        if (filen == "")
        {
            filename = home::filename;
        }
        else
        {
            filename = filen;
           
        }

        // creating file object

        ifstream in;
        in.open(filename);

        int body = 0;

        while (!in.eof())
        {
            getline(in, temp);
            // cout << temp << endl;
            if (temp == "<body>")
            {
                body++;
            }
            else if (temp == "</body>")
            {
                body++;
            }
            else if (body > 0 && body < 2)
            {
                paragraph += temp + "\n";
            }
        }
        body = 0;
        // cout << paragraph;
    }
};

class htmlParser : public extractor
{
protected:
    string tempstr = " ";

public:
    htmlParser() {}
    htmlParser(string fname) : extractor(fname)
    {
        // cout << "\n### html parser ###\n\n";
    }
    void parser()
    {
        // cout << paragraph;
        int i = 0;
        int tagopen = 0;
        int tagclose = 0;
        int slash = 0;
        int s1 = 0;
        int s2 = 0;
        while (i < paragraph.length())
        {
            // cout << paragraph.at(i);
            if (paragraph.at(i) == '<')
            {
                tagopen++;
            }
            else if (paragraph.at(i) == '>')
            {
                if (slash == 1)
                {
                    tagclose = 0;
                    slash = 0;
                }
                else
                {
                    tagclose++;
                }
            }
            else if (paragraph.at(i) == '/')
            {
                tagopen = 0;
                slash = 1;
            }
            else if (tagopen == 1 && tagclose == 1)
            {
                if (paragraph.at(i) == ' ' && paragraph.at(i + 1) == ' ')
                {
                }
                else
                {
                    tempstr += paragraph[i];
                }
            }

            i++;
        }

        cout << "\n\n### Your HTML Content Is Extract Successfully : \n\nContent : \n\n" << tempstr;

        // cout <<"\n" <<tagopen << " "<<tagclose << " " << slash;

        // cout << "\n paragraph : \n"<<tempstr;

    }

    void insertion()
    {
        ofstream out;
        srand(time(0));
        int randnum = rand();
        // cout << randnum;
        string fname = "htmlContant" + to_string(randnum) + ".txt";
        // cout << fname;
        out.open(fname);
        out << tempstr;
        cout <<"\n\n### You Content is Saved In : "<<fname<<endl<<endl;
    }
};

int main()
{

    htmlParser parser;

    while (1)
    {
        int option;
        cout << "\n### Welcome to HTML Parser ###\n";
        cout << "\n1.Start";
        cout << "\n2.Exit \n \nSelect Option ::: ";
        cin >> option;
        string tname;
        switch (option)
        {
        case 1:
            cout << "\n\nEnter HTML File Name (Ex: index.html) : ";
            cin >> tname;
            parser.openExtractor(tname);
            parser.parser();
            parser.insertion();
            break;

        case 2:
            exit(0);
            break;

        default:
            cout<<"\n\n## Invalid Option \n\n";
            break;
        }
    }

    return 0;
}