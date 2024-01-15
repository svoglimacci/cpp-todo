// ToDo App
// Simon Voglimacci
// v0.0.1  2024-01-15

#include <iostream>
#include <list>
#include <string>
#include <ctime>
#include <random>

//Name of each month
const std:: string months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul",
                               "Aug", "Sep", "Oct", "Nov", "Dec"};


//Date class to be used in the Task class
class Date {
 public:
  Date();
  ~Date() = default;
  std::string display();

 private:
  int day;
  int month;
};

//Constructor for the Date class
Date::Date() {
  std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);

  day = now->tm_mday;
  month = now->tm_mon;
}

std::string Date::display() {
  std::string date = months[month] + " " + std::to_string(day);
  return date;
}

//Task class for the ToDo List
class Task {
 protected:
  static int ID;

 private:
  int id;
  std::string description;
  Date date;
  bool done;

 public:
  Task(): id(), description(), date(), done(false) {}
  ~Task() = default;



  bool create(std::string desc) {
    id = ++ID;
    description = desc;
    return true;
  }

  int getId() {return id;}
  std::string getDescription() {return description;}
    void setDone(bool val) {done = val;}
  Date getDate() {return date;}
  bool isDone() {return done;}


};

int Task::ID = 0;

int main() {

  char input_option;
  int input_id;
  std::string input_desc;
  std::string version = "v0.0.1";
  std::list<Task> tasks;
  std::list<Task>::iterator it;

  tasks.clear();

  while (true) {
    system("cls");
    std::cout << "ToDo App " << version << std::endl;
    std::cout << std::endl;

    for (it = tasks.begin(); it != tasks.end(); ++it) {

      std::string done = it->isDone() ? "[\xfb]" : "[ ]";


      std::cout << it->getId() << " | " << it->getDescription() << " | "
                  << it->getDate().display() << " | " << done << std::endl;
    }

    if(tasks.empty()) {
      std::cout << "No tasks to display" << std::endl;
    }

    std::cout << std::endl << std::endl;

    std::cout << "[a] Add a task" << std::endl;
    std::cout << "[c] Complete a task" << std::endl;
    std::cout << "[q] Quit" << std::endl;

    std::cout << "Choice: ";
    std::cin >> input_option;

    if (input_option == 'q') {
      std::cout << "Goodbye!" << std::endl;
        break;
    }
    else if (input_option == 'a') {
      std::cout << "Enter task description: ";
      std::cin.clear();
      std::cin.ignore();
      std::getline(std::cin, input_desc);

      Task task;
      task.create(input_desc);
      tasks.push_back(task);
    }

    else if(input_option == 'c') {
      std::cout << "Enter task ID to mark as completed: ";
      std::cin >> input_id;

      for (it = tasks.begin(); it != tasks.end(); it++) {

        if(input_id == it->getId()) {
          it->setDone(true);
          break;
        }
      }

    }

  }

  return 0;

}