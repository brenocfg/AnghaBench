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
 int /*<<< orphan*/  PTRACE_SINGLESTEP ; 
 int SIGTRAP ; 
 scalar_t__ WIFSTOPPED (int) ; 
 int WSTOPSIG (int) ; 
 int /*<<< orphan*/  printk (char*,int) ; 
 int /*<<< orphan*/  ptrace (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  trycall (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  waitpid (int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int step(int pid) {
    trycall(ptrace(PTRACE_SINGLESTEP, pid, NULL, 0), "ptrace step");
    int status;
    trycall(waitpid(pid, &status, 0), "wait step");
    if (WIFSTOPPED(status) && WSTOPSIG(status) != SIGTRAP) {
        int signal = WSTOPSIG(status);
        printk("child received signal %d\n", signal);
        // a signal arrived, we now have to actually deliver it
        trycall(ptrace(PTRACE_SINGLESTEP, pid, NULL, signal), "ptrace step");
        trycall(waitpid(pid, &status, 0), "wait step");
        return 1;
    }
    return 0;
}