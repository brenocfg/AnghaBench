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
 int /*<<< orphan*/  CATCH_EINTR (int) ; 
 int /*<<< orphan*/  PTRACE_CONT ; 
 int WEXITSTATUS (int) ; 
 int /*<<< orphan*/  WIFEXITED (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  non_fatal (char*,...) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ ptrace (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stop_ptraced_child(int pid, int exitcode, int mustexit)
{
	int status, n, ret = 0;

	if (ptrace(PTRACE_CONT, pid, 0, 0) < 0) {
		perror("stop_ptraced_child : ptrace failed");
		return -1;
	}
	CATCH_EINTR(n = waitpid(pid, &status, 0));
	if (!WIFEXITED(status) || (WEXITSTATUS(status) != exitcode)) {
		int exit_with = WEXITSTATUS(status);
		if (exit_with == 2)
			non_fatal("check_ptrace : child exited with status 2. "
				  "\nDisabling SYSEMU support.\n");
		non_fatal("check_ptrace : child exited with exitcode %d, while "
			  "expecting %d; status 0x%x\n", exit_with,
			  exitcode, status);
		if (mustexit)
			exit(1);
		ret = -1;
	}

	return ret;
}