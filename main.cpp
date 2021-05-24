#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "inventory.h"

int iterator = 0;
std::string inventory[] = {"-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", };
class class_commands {
    private:
    std::string current_command = "";
    std::string current_item = "";

  public:
  void setter_command(std::string str){
      current_command = str;
  }
  void setter_item(std::string str){
      current_item = str;
  }
  std::string getter_command(void){
      return current_command;
  }
  std::string getter_item(void){
      return current_item;
  }
    void insert(std::string item);
    void remove(std::string item);
    void show(void);
    void help(void);
};

void class_commands::help(void){
    std::cout << "Available commands:" << std::endl;
    std::cout << "1. insert <itemType>" << std::endl;
    std::cout << "2. remove <itemType>" << std::endl;
    std::cout << "3. show" << std::endl;
    std::cout << "3. help" << std::endl;
    std::cout << "3. exit" << std::endl;
}

void class_commands::show(void)
{
    std::cout << "Inventory {";
    int i;
    for(i = 0; i < 12; i++){
        if(i == 11)
            std::cout << inventory[i];
        else
            std::cout << inventory[i] << ", ";
    }
    std::cout << "}" << std::endl;
}

void class_commands::insert(std::string item) {
    if(iterator > 12){
        iterator = 12;
        std::cout << "Inventory is full" << std::endl;   
        return;
    }
    else{
        inventory[iterator] = item;
        iterator++;
    }
}

void class_commands::remove(std::string item) {
    int i = 0;
    if(iterator < 0 || inventory[0] == "-") {
        std::cout << "There is nothing to remove" << std::endl;
        iterator = 0;
        return;
    }
    while(inventory[i] != item){
        if(i >= 12){
            std::cout << "There is no <" << item << ">"<< std::endl;
            return;

        }
        i++;
    }

    inventory[i] = "-";
    iterator--;
}

int validation(class_commands commands, int status){
    if(status == 1){
        std::string tmp_command = commands.getter_command();
        if(tmp_command == "show")
            commands.show();
        else if(tmp_command == "help")
            commands.help();
        else
            return 0;
    }
    else {
        std::string tmp_command = commands.getter_command();
        std::string tmp_item = commands.getter_item();
        if(tmp_item.find_first_not_of("wfap")){
            if(tmp_command == "insert"){
                commands.insert(tmp_item);
            }
            else if(tmp_command == "remove")
                commands.remove(tmp_item);
            else
                std::cout << "Invalid command" << std::endl;    
        }
        else{
            std::cout << "Invalid item" << std::endl;
            return 0;

        }


    }   
}

void parsing(std::string line, class_commands commands){
    std::vector<std::string> words;
    std::string::size_type i = 0;
    std::string::size_type j = line.find(' ');
    if(j > 15){
        commands.setter_command(line);
        validation(commands, 1);
    }
    else{
        words.push_back(line.substr(i, j));
        words.push_back(line.substr(++j, std::string::npos));  
        commands.setter_command(words[0]);
        commands.setter_item(words[1]);
        validation(commands, 2);
    }
}

int main (void) {

    std::string line;
    std::string item;
    class_commands commands;

    while(1){
        std::cout << "Enter command:>";
        std::getline(std::cin, line);
        parsing(line, commands);
    }
}