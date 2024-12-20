#include <iostream>
#include <unistd.h>

void pipeline(const char* process1, const char* process2)
{
    int fd[2];
    pipe(fd);
    if(fork() != 0){ // Parent Process
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);

        system(process1);
    }
    else{
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[1]);

        system(process2);
    }
}

int main()
{
    pipeline("cat main.cpp", "grep hello");
    return 0;
}