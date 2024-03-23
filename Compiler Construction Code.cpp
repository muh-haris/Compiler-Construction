#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include <sstream>
using namespace std;

typedef enum
{
    space = 1,
    tab,
    newline,
    comma,
    semicolon,
    LRB,
    RRB,
    LCB,
    RCB,
    LSB,
    RSB,
    not_known,
    Plus,
    Equal,
    Minus,
    mult,
    Div,
    plusplus,
    minusminus,
    equalequal,
    plusequal,
    minusequal,
    Greater,
    Less,
    greaterequal,
    DIGIT,
    lessequal,
    SingleLineComment,
    MultiLineComment,
    DataType,
    Identifier,
    stringdata
} tokentype;

fstream myfile;

struct token
{
    tokentype tt;
    string entryno;
    string variable;
};
bool isKeyword(string word)
{
    string keywords[] = {"int", "float", "double", "char", "bool", "if", "else", "for", "while", "do",
                         "return", "break", "continue"};

    for (int i = 0; i < 13; i++)
    {
        if (word == keywords[i])
        {
            return true;
        }
    }

    return false;
}

fstream lexicalfile;
struct Node
{
    string uid;
    Node *next;
};
class Symbol_Table_UID
{
private:
    Node *head;
    Node *tail;

public:
    Symbol_Table_UID()
    {
        head = NULL;
        tail = NULL;
    }
    void enqueue(string uid)
    {
        Node *temp = new Node();
        temp->uid = uid;
        temp->next = NULL;
        if (head == NULL)
        {
            head = temp;
            tail = temp;
        }
        else
        {
            tail->next = temp;
            tail = tail->next;
        }
    }
    void display()
    {
        if (head == NULL)
        {
            cout << "Symbol table is empty.\n";
            return;
        }
        cout << "\nSymbol table for UID :\n";
        Node *temp = head;
        while (temp != NULL)
        {
            cout << temp->uid << endl;
            temp = temp->next;
        }
    }
};

class Symbol_Table_DIG
{
private:
    Node *head;
    Node *tail;

public:
    Symbol_Table_DIG()
    {
        head = NULL;
        tail = NULL;
    }
    void enqueue(string uid)
    {
        Node *temp = new Node();
        temp->uid = uid;
        temp->next = NULL;
        if (head == NULL)
        {
            head = temp;
            tail = temp;
        }
        else
        {
            tail->next = temp;
            tail = tail->next;
        }
    }
    void display()
    {
        if (head == NULL)
        {
            cout << "Symbol table is empty.\n";
            return;
        }
        cout << "\nSymbol table for DIG :\n";
        Node *temp = head;
        while (temp != NULL)
        {
            cout << temp->uid << endl;
            temp = temp->next;
        }
    }
};

class Symbol_Table_string
{
private:
    Node *head;
    Node *tail;

public:
    Symbol_Table_string()
    {
        head = NULL;
        tail = NULL;
    }
    void enqueue(string uid)
    {
        Node *temp = new Node();
        temp->uid = uid;
        temp->next = NULL;
        if (head == NULL)
        {
            head = temp;
            tail = temp;
        }
        else
        {
            tail->next = temp;
            tail = tail->next;
        }
    }
    void display()
    {
        if (head == NULL)
        {
            cout << "Symbol table is empty.\n";
            return;
        }
        cout << "\nSymbol table for String Values :\n";
        Node *temp = head;
        while (temp != NULL)
        {
            cout << "\"" << temp->uid << endl;
            temp = temp->next;
        }
    }
};

Symbol_Table_UID str_uid;
Symbol_Table_DIG str_dig;
Symbol_Table_string str_val;

token mylex(char c)
{
    token t;
    if (c == ' ')
    {
        t.tt = space;
        t.entryno = "Space";
        return t;
    }
    else if (c == '\t')
    {
        t.tt = tab;
        t.entryno = "Tab";
        return t;
    }
    else if (c == '\n')
    {
        t.tt = newline;
        t.entryno = "NewLine";
        return t;
    }
    else if (c == ',')
    {
        t.tt = comma;
        t.entryno = "Comma";
        return t;
    }
    else if (c == ';')
    {
        t.tt = semicolon;
        t.entryno = "Semicolon";
        return t;
    }
    else if (c == '(')
    {
        t.tt = LRB;
        t.entryno = "Left Round Bracket";
        return t;
    }
    else if (c == ')')
    {
        t.tt = RRB;
        t.entryno = "Right Round Bracket";
        return t;
    }
    else if (c == '{')
    {
        t.tt = LCB;
        t.entryno = "Left Curly Bracket";
        return t;
    }
    else if (c == '}')
    {
        t.tt = RCB;
        t.entryno = "Right Curly Bracket";
        return t;
    }
    else if (c == '[')
    {
        t.tt = LSB;
        t.entryno = "Left Square Bracket";
        return t;
    }
    else if (c == ']')
    {
        t.tt = RSB;
        t.entryno = "Right Square Bracket";
        return t;
    }
    else if (c == '+')
    {
        if (myfile.peek() == '+')
        {
            myfile.get(c);
            t.tt = plusplus;
            t.entryno = "Plus Plus";
            return t;
        }
        else if (myfile.peek() == '=')
        {
            myfile.get(c);
            t.tt = plusequal;
            t.entryno = "Plus Equal";
            return t;
        }
        else
        {
            t.tt = Plus;
            t.entryno = "Plus";
            return t;
        }
    }
    else if (c == '-')
    {
        if (myfile.peek() == '-')
        {
            t.tt = minusminus;
            t.entryno = "Minus Minus";
            return t;
        }
        else if (myfile.peek() == '=')
        {
            t.tt = minusequal;
            t.entryno = "Minus Equal";
            return t;
        }
        else
        {
            t.tt = Minus;
            t.entryno = "Minus";
            return t;
        }
    }
    else if (c == '=')
    {
        if (myfile.peek() == '=')
        {
            t.tt = equalequal;
            t.entryno = "Equal Equal";
            return t;
        }
        else
        {
            t.tt = Equal;
            t.entryno = "Equal";
            return t;
        }
    }
    else if (c == '*')
    {

        t.tt = mult;
        t.entryno = "Multiply";
        return t;
    }
    else if (c == '>')
    {
        if (myfile.peek() == '=')
        {
            t.tt = greaterequal;
            t.entryno = "Greater Equal";
            return t;
        }
        else
        {
            t.tt = Greater;
            t.entryno = "Greater";
            return t;
        }
    }
    else if (c == '<')
    {
        if (myfile.peek() == '=')
        {
            t.tt = lessequal;
            t.entryno = "Less Equal";
            return t;
        }
        else
        {
            t.tt = Less;
            t.entryno = "Less";
            return t;
        }
    }
    else if (c == '/')
    {
        if (myfile.peek() == '/')
        {
            while (myfile.get(c))
            {
                if (c == '\n')
                {
                    break;
                }
            }
            t.tt = SingleLineComment;
            t.entryno = "SingleLineComment";
            return t;
        }
        else if (myfile.peek() == '*')
        {
            myfile.get(c);
            while (myfile.get(c))
            {
                if (c == '*')
                {
                    if (myfile.peek() == '/')
                    {
                        myfile.get(c);
                        break;
                    }
                }
            }
            t.tt = MultiLineComment;
            t.entryno = "Multi Line Comment";
            return t;
        }
        else
        {
            t.tt = Div;
            t.entryno = "Div";
            return t;
        }
    }
    else if (c == '"')
    {
        t.tt = stringdata;
        string value;
        t.entryno = "String Data";
        while (true)
        {
            myfile.get(c);
            value += c;
            if (c == '"')
            {
                myfile.get(c);
                str_val.enqueue(value);
                break;
            }
        }
        return t;
    }
    else if (isdigit(c))
    {
        string n;
        n = c;
        while (isdigit(myfile.peek()))
        {
            // n += c;
            myfile.get(c);
            n += c;
        }
        t.tt = DIGIT;
        t.entryno = "number";
        t.variable = n;
        str_dig.enqueue(t.variable);
        return t;
    }
    else if (isalpha(c) || c == '_')
    {
        string s;
        s += c;
        while (isalnum(myfile.peek()) || myfile.peek() == '_')
        {
            s += myfile.get();
        }
        if (isKeyword(s))
        {
            t.tt = DataType;
            t.entryno = "Keyword";
            t.variable = s;
            return t;
        }
        else
        {
            t.tt = Identifier;
            t.entryno = "Identifier";
            t.variable = s;
            str_uid.enqueue(t.variable);
            return t;
        }
    }
}

struct RecursiveDescentParser
{ //--------------cfg
    string input;
    size_t index;

    RecursiveDescentParser(const string &input) : input(input), index(0) {}

    bool parseExp();
    bool parseTerm();
    bool parseOp();
    bool parse();
};

bool RecursiveDescentParser::parseExp()
{
    if (parseTerm())
    {
        while (parseOp() && parseTerm())
        {
        }
        return true;
    }
    return false;
}
bool RecursiveDescentParser::parseTerm()
{
    if (isdigit(input[index]))
    {
        ++index;
        return true;
    }
    else if (input[index] == '(')
    {
        ++index;
        if (parseExp() && input[index] == ')')
        {
            ++index;
            return true;
        }
    }
    return false;
}
bool RecursiveDescentParser::parseOp()
{
    if (input[index] == '+' || input[index] == '-' || input[index] == '*')
    {
        ++index;
        return true;
    }
    return false;
}
bool RecursiveDescentParser::parse()
{
    return parseExp() && index == input.size();
}

enum class TokenType
{ //----------parser
    NUMBER,
    ID,
    ADDOPR,
    MULOPR,
    LPAREN,
    RPAREN,
    ASSIGN,
    SEMICOLON,
    END
};

struct Token
{
    TokenType type;
    string value;
};

class Parser
{
    istringstream input;
    Token token;
    string output;

    void nextToken()
    {
        char ch;
        if (!(input >> ch))
        {
            token.type = TokenType::END;
            return;
        }

        switch (ch)
        {
        case '+':
            token.type = TokenType::ADDOPR;
            token.value = "plus";
            break;
        case '-':
            token.type = TokenType::ADDOPR;
            token.value = "minus";
            break;
        case '*':
            token.type = TokenType::MULOPR;
            token.value = "Mul";
            break;
        case '/':
            token.type = TokenType::MULOPR;
            token.value = "Div";
            break;
        case '(':
            token.type = TokenType::LPAREN;
            break;
        case ')':
            token.type = TokenType::RPAREN;
            break;
        case '=':
            token.type = TokenType::ASSIGN;
            break;
        case ';':
            token.type = TokenType::SEMICOLON;
            break;
        default:
            if (isdigit(ch))
            {
                input.putback(ch);
                int number;
                input >> number;
                token.type = TokenType::NUMBER;
                token.value = to_string(number);
            }
            else if (isalpha(ch))
            {
                token.type = TokenType::ID;
                token.value = ch;
            }
            break;
        }
    }

    void match(TokenType expected)
    {
        if (token.type != expected)
        {
            throw runtime_error("Unexpected token");
        }
        if (token.type == TokenType::NUMBER || token.type == TokenType::ADDOPR || token.type == TokenType::MULOPR)
        {
            output += token.value + " ";
        }
        nextToken();
    }

    void factor()
    {
        if (token.type == TokenType::NUMBER)
        {
            match(TokenType::NUMBER);
        }
        else if (token.type == TokenType::LPAREN)
        {
            match(TokenType::LPAREN);
            output += "( ";
            expression();
            match(TokenType::RPAREN);
            output += ") ";
        }
        else
        {
            throw runtime_error("Factor expected");
        }
    }

    void term()
    {
        factor();
        while (token.type == TokenType::MULOPR)
        {
            match(TokenType::MULOPR);
            factor();
        }
    }

    void expression()
    {
        term();
        while (token.type == TokenType::ADDOPR)
        {
            match(TokenType::ADDOPR);
            term();
        }
    }

    void statement()
    {
        match(TokenType::ID);
        match(TokenType::ASSIGN);
        expression();
        match(TokenType::SEMICOLON);
    }

public:
    void parse(const string &str)
    {
        input = istringstream(str);
        nextToken();
        statement();
        if (token.type != TokenType::END)
        {
            throw runtime_error("End of input expected");
        }
    }

    void parseFromFile(const string &filename)
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            throw runtime_error("Failed to open file");
        }

        ostringstream buffer;
        buffer << file.rdbuf();
        parse(buffer.str());
    }

    string getOutput()
    {
        return output;
    }
};

//------------------RE
bool isvalidassignment(const string &c)
{
    const string pattern = "^\\s*((int|string|double|float)?)\\s*[A-Za-z_]+\\w*\\s*\=(\\s*?)(\\d+|\\d+\.\\d+|\"(\\s*\\w*)\")\\s;$";
    regex regexpattern(pattern);
    return regex_match(c, regexpattern);
}
bool isvalidcopy(const string &c)
{
    const string pattern = "^\\s*((int|string|double|float)?)\\s*[A-Za-z_]\\s*\=\\s*[A-Za-z_]\\s*(\\+\\s*[A-Za-z_]\\s*)*;$";
    regex regexpattern(pattern);
    return regex_match(c, regexpattern);
}
bool isvalidunconditional(const string &c)
{
    const string pattern = "^\goto\\s+[A-Za-z_]+;$";
    regex regexpattern(pattern);
    return regex_match(c, regexpattern);
}
bool isvalidproceduralcall(const string &c)
{
    const string pattern = "^\\s*[A-Za-z_]+\\s*\\(\\s*[A-Za-z_0-9](,\\s[A-Za-z_0-9]+)*\\)\;$";
    regex regexpattern(pattern);
    return regex_match(c, regexpattern);
}
bool isvalidconditional(const string &c)
{
    const string pattern = "^\\s*\if\\s*\\(\\s*[A-Za-z_]+\\s*(==|<|>|<=|>=)\\s*[A-Za-z_]+\\s*\\)\\s*\\{.\\}\\s\\else\\s*\\{.*\\}$";
    regex regexpattern(pattern);
    return regex_match(c, regexpattern);
}
bool isvalidfunction(const string &c)
{
    const string pattern = "^\\s*(void|int|string|double|float)\\s+[A-Za-z_]+\\(\\s*((void|int|string|double|float)\\s+[A-Za-z_]+)(,\\s(void|int|string|double|float)\\s+[A-Za-z_]+)*\\)\\{.*\\}$";
    regex regexpattern(pattern);
    return regex_match(c, regexpattern);
}
bool isvalidswitch(const string &c)
{
    const string pattern = "^\\s*\switch\\s*\\(\\s*[A-Za-z_]+\\s*\\)\\s*\\{(\case\\s+[A-Za-z0-9]+\:.*break;)+\default:\\s*break;\\}$";
    regex regexpattern(pattern);
    return regex_match(c, regexpattern);
}
bool isvalidloop(const string &c)
{
    const string pattern = "^\\s*(\while\\s*\\(\\s*[A-Za-z0-9]+\\s*(==|<|>|<=|>=)\\s*[A-Za-z0-9]+\\s*\\)\\s*\\{.\\})|(\do\\s\\{.\\}\while\\([A-Za-z0-9]+(==|<|>|<=|>=)[A-Za-z0-9]+\\);)|(\\s*for\\s\\((int|double)\\s+[A-Za-z_]+=\\d+\\s*;\\s*[A-Za-z_]+(<|>|==|<=|>=)[A-Za-z0-9]+\\s*;\\s*[A-Za-z_]+(\\++|\\--)\\s*\\)\\s*\\{.*\\})$";
    regex regexpattern(pattern);
    return regex_match(c, regexpattern);
}
bool isvalidarray1(const string &c)
{
    const string pattern = "^\\s*(int|string)\\s*[A-Za-z_]+\\s*\\[\\s*\\d+\\s*\\]\\s*=\\s*\\{\\s*([0-9](\"[A-Za-z_]*\")*)(,[0-9]*(\"[A-Za-z_]*\")*)*\\}\\s;$";
    regex regexpattern(pattern);
    return regex_match(c, regexpattern);
}
bool isvalidarray2(const string &c)
{
    const string pattern = "^\\s*(int|string)\\s*[A-Za-z_]+\\s*\\[\\s*\\d+\\s*\\]\\s*\\[\\s*\\d+\\s*\\]\\s*=\\s*\\{\\{\\s*([0-9](\"[A-Za-z_]*\")*)(,[0-9]*(\"[A-Za-z_]*\")*)*\\},\\{\\s([0-9]*(\"[A-Za-z_]*\")*)(,[0-9]*(\"[A-Za-z_]*\")*)*\\}\\};$";
    regex regexpattern(pattern);
    return regex_match(c, regexpattern);
}
bool isvalidarray3(const string &c)
{
    const string pattern = "^\\s*(int|string)\\s*[A-Za-z_]+\\s*\\[\\s*\\d+\\s*\\]\\s*\\[\\s*\\d+\\s*\\]\\s*\\[\\s*\\d+\\s*\\]\\s*=\\s*\\{\\{\\s*([0-9](\"[A-Za-z_]*\")*)(,[0-9]*(\"[A-Za-z_]*\")*)*\\},\\{\\s([0-9](\"[A-Za-z_]*\")*)(,[0-9]*(\"[A-Za-z_]*\")*)*\\},\\{\\s([0-9]*(\"[A-Za-z_]*\")*)(,[0-9]*(\"[A-Za-z_]*\")*)*\\}\\};$";
    regex regexpattern(pattern);
    return regex_match(c, regexpattern);
}
bool isvalidpointer(const string &c)
{
    const string pattern = "^((int|string)\\s*\\[A-Za-z_]+;)|(int|string)\\s\\[A-Za-z_]+=\\s&[A-Za-z_]+;$";
    regex regexpattern(pattern);
    return regex_match(c, regexpattern);
}
void verify(string c)
{
    if (isvalidassignment(c))
    {
        cout << "valid assignment statement" << endl;
    }
    else if (isvalidcopy(c))
    {
        cout << "valid copy statement" << endl;
    }
    else if (isvalidunconditional(c))
    {
        cout << "valid unconditional statement" << endl;
    }
    else if (isvalidproceduralcall(c))
    {
        cout << "valid procedural statement" << endl;
    }
    else if (isvalidconditional(c))
    {
        cout << "valid conditional jump" << endl;
    }
    else if (isvalidfunction(c))
    {
        cout << "valid function" << endl;
    }
    else if (isvalidswitch(c))
    {
        cout << "valid switch" << endl;
    }
    else if (isvalidloop(c))
    {
        cout << "valid loop" << endl;
    }
    else if (isvalidarray1(c))
    {
        cout << "valid array 1D" << endl;
    }
    else if (isvalidarray2(c))
    {
        cout << "valid array 2D" << endl;
    }
    else if (isvalidarray3(c))
    {
        cout << "valid array 3D" << endl;
    }
    else if (isvalidpointer(c))
    {
        cout << "valid pointer" << endl;
    }
    else
    {
        cout << "invalid statement" << endl;
    }
}

//------syntax analyzer
void removeComments(ifstream &sourceFile, ofstream &outputFile)
{
    cout << "Removing comments\n\n";

    char currentChar, nextChar;
    bool isMultiLineComment = false;

    while (sourceFile.get(currentChar))
    {
        if (currentChar == '/' && sourceFile.get(nextChar))
        {
            if (nextChar == '/')
            {
                while (sourceFile.get(currentChar))
                {
                    if (currentChar == '\n')
                    {
                        break;
                    }
                }
            }
            else if (nextChar == '*')
            {
                isMultiLineComment = true;
                while (sourceFile.get(currentChar))
                {
                    if (currentChar == '*')
                    {
                        if (sourceFile.get(nextChar) && nextChar == '/')
                        {
                            isMultiLineComment = false;
                            break;
                        }
                    }
                }
            }
            else
            {
                cout << currentChar;
                outputFile.put(currentChar);
            }
        }
        else
        {
            cout << currentChar;
            outputFile.put(currentChar);
        }
    }
}

void WhiteSpaceRemover(ifstream &sourceFile)
{
    cout << "\nRemove White Space: \n\n";
    char ch;
    while (sourceFile.get(ch))
    {
        if (ch != ' ' && ch != '\t' && ch != '\n')
        {
            cout << ch;
        }
    }
}
bool iskeyword(string word)
{
    string keywords[] = {"int", "float", "double", "char", "bool", "if", "else", "for", "while", "do",
                         "return", "break", "continue"};

    for (string r : keywords)
    {
        if (word == r)
        {
            return true;
        }
    }

    return false;
}

bool isIdentifier(string word)
{
    if (isdigit(word[0]))
    {
        return false;
    }

    for (char c : word)
    {
        if (!isalnum(c) && c != '_')
        {
            return false;
        }
    }

    return true;
}
bool isConstant(string word)
{
    for (char c : word)
    {
        if (!isdigit(c))
        {
            return false;
        }
    }

    return true;
}
bool Operator(string word)
{
    string operators[] = {"+", "-", "*", ">", "<<", ">>", "=", "%"};

    for (string op : operators)
    {
        if (word == op)
        {
            return true;
        }
    }
    return false;
}

//-----3 a c
void parseCPlusPlusCode(const string &inputFileName)
{
    ifstream inputFile(inputFileName);
    if (!inputFile.is_open())
    {
        cerr << "Unable to open the input file." << endl;
        return;
    }

    try
    {
        string code((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());

        regex assignmentPattern(R"(\b(\w+)\s*=\s*(.+?);)");
        regex copyPattern(R"(\b(\w+)\s*=\s*(\w+);)");

        smatch match;
        for (sregex_iterator it(code.begin(), code.end(), assignmentPattern); it != sregex_iterator(); ++it)
        {
            match = *it;

            cout << "Three Address Code: " << match[1] << " = " << match[2] << endl;

            // cout << "Assembly Code: MOV " << match[1] << ", " << match[2] << endl;
        }
    }
    catch (const exception &e)
    {
        cerr << "Exception: " << e.what() << endl;
    }
}

int main()
{
    token t;
    char c;
    myfile.open("lexical.txt");
    ifstream inputFile("cfg.txt");

    int no;
    do
    {
        cout << "\n\n\n\n";
        cout << "\n********     *********     *         *     ********      *      *              *********     ********";
        cout << "\n*            *       *     * *     * *     *       *     *      *              *             *       *";
        cout << "\n*            *       *     *   * *   *     *       *     *      *              *             *       *";
        cout << "\n*            *       *     *    *    *     ********      *      *              *******       ********";
        cout << "\n*            *       *     *         *     *             *      *              *             *    *";
        cout << "\n*            *       *     *         *     *             *      *              *             *     *";
        cout << "\n********     *********     *         *     *             *      *********      *********     *      *";
        cout << "\n\n\n\n\t====================================================";
        cout << "\n\tEnter 1 for Lexical Analyzer / Token Generator";
        cout << "\n\tEnter 2 for Symbol Table";
        cout << "\n\tEnter 3 for CFG";
        cout << "\n\tEnter 4 for Parsing Tree";
        cout << "\n\tEnter 5 for RE";
        cout << "\n\tEnter 6 for Syntax Analyzer";
        cout << "\n\tEnter 7 for 3 Address Code";
        cout << "\n\tEnter 0 for Exit";
        cout << "\n\t====================================================";
        cout << "\nEnter input: ";
        cin >> no;
        cout << "\n\t\t--------------------------------------------------\n";

        if (no == 1)
        {
            if (!myfile.is_open())
            {
                cout << "Error: Unable to open file.\n";
                return 1;
            }

            if (myfile.is_open())
            {
                while (myfile.peek() != EOF)
                {
                    myfile.get(c);
                    t = mylex(c);
                    cout << t.tt << "\t" << t.entryno << "\t\t\t" << t.variable << "\n";
                }
            }
        }
        else if (no == 2)
        {
            str_uid.display();
            str_dig.display();
            str_val.display();
        }
        else if (no == 3)
        {
            if (!inputFile.is_open())
            {
                cout << "Error: Unable to open file.\n";
                return 1;
            }

            cout << "\nexp -> exp op exp | (exp) | number \nop -> + | - | *\n";

            string inputExpression;
            while (inputFile.peek() != EOF)
            {
                getline(inputFile, inputExpression);

                RecursiveDescentParser parser(inputExpression);

                if (parser.parse() && (inputExpression.back() != '+' && inputExpression.back() != '-' && inputExpression.back() != '*'))
                {
                    cout << "Valid grammar.\n";
                }
                else
                {
                    cout << "Invalid grammar.\n";
                }
            }
        }
        else if (no == 4)
        {
            Parser parser;
            try
            {

                parser.parseFromFile("parser.txt");
                cout << "Parsing successful. Output: " << parser.getOutput() << endl;
            }
            catch (const runtime_error &e)
            {
                cout << "Parsing failed: " << e.what() << endl;
            }
        }
        else if (no == 5)
        {
            string word;
            ifstream myfile;
            myfile.open("re.txt");
            while (getline(myfile, word))
            {
                verify(word);
            }
            myfile.close();
        }
        else if (no == 6)
        {
            ifstream sourceFile("source.txt");
            ofstream outputFile("output.txt");

            removeComments(sourceFile, outputFile);
            sourceFile.close();
            outputFile.close();

            sourceFile.open("output.txt");
            WhiteSpaceRemover(sourceFile);
            sourceFile.close();

            cout << "\n\n--------------------------------\n\n";

            ifstream input("output.txt");
            string line;
            while (getline(input, line))
            {
                stringstream a(line);
                string word;
                while (a >> word)
                {
                    if (iskeyword(word))
                    {
                        cout << "Keyword: " << word << endl;
                    }
                    else if (isIdentifier(word))
                    {
                        cout << "Identifier: " << word << endl;
                    }
                    else if (isConstant(word))
                    {
                        cout << "Constant: " << word << endl;
                    }
                    else if (Operator(word))
                    {
                        cout << "operator: " << word << endl;
                    }
                }
            }
        }
        else if (no == 7)
        {
            string inputFileName = "2.c++";
            parseCPlusPlusCode(inputFileName);
        }

    } while (no != 0);

    myfile.close();
    inputFile.close();
}