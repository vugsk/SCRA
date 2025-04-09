#include <iostream>
#include <vector>
#include <stack>

enum class Command {
    PUSH,
    ADD,
    SUB,
    MUL,
    PRINT,
    HALT
};

struct Instruction {
    Command cmd;
    int arg;
};

class VirtualMachine {
public:
    VirtualMachine(const Instruction* program, size_t size)
        : program(program), programSize(size) {}

    void run() {
        std::vector<int> stack;
        size_t pc = 0; // Program Counter

        while (pc < programSize) {
            const Instruction& instr = program[pc];
            switch (instr.cmd) {
                case Command::PUSH:
                    stack.push_back(instr.arg);
                    break;
                case Command::ADD:
                    if (stack.size() >= 2) {
                        int a = stack.back(); stack.pop_back();
                        int b = stack.back(); stack.pop_back();
                        stack.push_back(a + b);
                    }
                    break;
                case Command::SUB:
                    if (stack.size() >= 2) {
                        int a = stack.back(); stack.pop_back();
                        int b = stack.back(); stack.pop_back();
                        stack.push_back(b - a); // Вычитаем в обратном порядке
                    }
                    break;
                case Command::MUL:
                    if (stack.size() >= 2) {
                        int a = stack.back(); stack.pop_back();
                        int b = stack.back(); stack.pop_back();
                        stack.push_back(a * b);
                    }
                    break;
                case Command::PRINT:
                    if (!stack.empty()) {
                        std::cout << stack.back() << std::endl;
                    }
                    break;
                case Command::HALT:
                    return;
                default:
                    std::cerr << "Unknown command" << std::endl;
                    return;
            }
            pc++;
        }
    }

private:
    const Instruction* program;
    size_t programSize;
};

int main() {
    // Пример программы: (5 + 3) * 2
    Instruction program[] = {
        {Command::PUSH, 5},
        {Command::PUSH, 3},
        {Command::ADD},
        {Command::PUSH, 2},
        {Command::MUL}, // Добавьте MUL в enum и реализацию
        {Command::PRINT},
        {Command::HALT}
    };

    // Для работы примера нужно добавить команду MUL
    // В текущем коде MUL отсутствует, поэтому временно заменим на ADD
    program[4].cmd = Command::ADD;

    VirtualMachine vm(program, std::size(program));
    vm.run();

    return 0;
}