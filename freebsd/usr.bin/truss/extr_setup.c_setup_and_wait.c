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
struct trussinfo {int dummy; } ;
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  PT_TRACE_ME ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  execvp (char*,char**) ; 
 int /*<<< orphan*/  new_proc (struct trussinfo*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vfork () ; 
 scalar_t__ waitpid (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
setup_and_wait(struct trussinfo *info, char *command[])
{
	pid_t pid;

	pid = vfork();
	if (pid == -1)
		err(1, "fork failed");
	if (pid == 0) {	/* Child */
		ptrace(PT_TRACE_ME, 0, 0, 0);
		execvp(command[0], command);
		err(1, "execvp %s", command[0]);
	}

	/* Only in the parent here */
	if (waitpid(pid, NULL, 0) < 0)
		err(1, "unexpect stop in waitpid");

	new_proc(info, pid, 0);
}