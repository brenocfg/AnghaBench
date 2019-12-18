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
 int ADDR_NO_RANDOMIZE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  PR_SET_TSC ; 
 int /*<<< orphan*/  PR_TSC_SIGSEGV ; 
 int /*<<< orphan*/  PTRACE_TRACEME ; 
 int SIGRTMIN ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  WIFSTOPPED (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fexecve (int /*<<< orphan*/ ,char* const*,char* const*) ; 
 int fork () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  openat (int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int personality (int) ; 
 int /*<<< orphan*/  prctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  trycall (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wait (int*) ; 

int start_tracee(int at, const char *path, char *const argv[], char *const envp[]) {
    // shut off aslr
    int persona = personality(0xffffffff);
    persona |= ADDR_NO_RANDOMIZE;
    personality(persona);

    int pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    }
    if (pid == 0) {
        // child
        // enable segfaulting on rdtsc and cpuid
        trycall(prctl(PR_SET_TSC, PR_TSC_SIGSEGV), "rdtsc faulting");
        /* trycall(arch_prctl(ARCH_SET_CPUID, 0), "cpuid faulting"); */
        trycall(ptrace(PTRACE_TRACEME, 0, NULL, NULL), "ptrace traceme");
        // get rid of signal handlers
        for (int sig = 0; sig < SIGRTMIN - 1; sig++)
            signal(sig, SIG_DFL);
        trycall(fexecve(openat(at, path, O_RDONLY), argv, envp), "execve");
    } else {
        // parent, wait for child to stop after exec
        int status;
        trycall(wait(&status), "wait");
        if (!WIFSTOPPED(status)) {
            fprintf(stderr, "child failed to start\n");
            exit(1);
        }
    }
    return pid;
}