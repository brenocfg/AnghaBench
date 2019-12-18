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
typedef  int pid_t ;

/* Variables and functions */
 scalar_t__ ECHILD ; 
 scalar_t__ ENOENT ; 
 int WEXITSTATUS (int) ; 
 scalar_t__ WIFSIGNALED (int) ; 
 int /*<<< orphan*/  WTERMSIG (int) ; 
 scalar_t__ childerr ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ pids_full () ; 
 int rval ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 
 int /*<<< orphan*/  warnx (char*,char const*,...) ; 
 int xwait (int,int*) ; 

__attribute__((used)) static void
waitchildren(const char *name, int waitall)
{
	pid_t pid;
	int status;
	int cause_exit = 0;

	while ((pid = xwait(waitall || pids_full(), &status)) > 0) {
		/*
		 * If we couldn't invoke the utility or if utility exited
		 * because of a signal or with a value of 255, warn (per
		 * POSIX), and then wait until all other children have
		 * exited before exiting 1-125. POSIX requires us to stop
		 * reading if child exits because of a signal or with 255,
		 * but it does not require us to exit immediately; waiting
		 * is preferable to orphaning.
		 */
		if (childerr != 0 && cause_exit == 0) {
			errno = childerr;
			waitall = 1;
			cause_exit = ENOENT ? 127 : 126;
			warn("%s", name);
		} else if (WIFSIGNALED(status)) {
			waitall = cause_exit = 1;
			warnx("%s: terminated with signal %d; aborting",
			    name, WTERMSIG(status));
		} else if (WEXITSTATUS(status) == 255) {
			waitall = cause_exit = 1;
			warnx("%s: exited with status 255; aborting", name);
		} else if (WEXITSTATUS(status))
 			rval = 1;
	}

 	if (cause_exit)
		exit(cause_exit);
	if (pid == -1 && errno != ECHILD)
		err(1, "waitpid");
}