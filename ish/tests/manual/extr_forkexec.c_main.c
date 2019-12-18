#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 scalar_t__ execv (char*,char**) ; 
 int fork () ; 
 int /*<<< orphan*/  perror (char*) ; 
 int waitpid (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int main(int argc, char *argv[]) {
    int pid = fork();
    if (pid < 0) {
        perror("fork");
        abort();
    }
    if (pid == 0) {
        // child
        if (execv(argv[1], argv + 1) < 0) {
            perror("exec");
            abort();
        }
    } else {
        // parent
        if (waitpid(pid, NULL, 0) != pid) {
            perror("wait");
            abort();
        }
    }
}