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
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 scalar_t__ WEXITSTATUS (int) ; 
 scalar_t__ WIFSIGNALED (int) ; 
 int /*<<< orphan*/  WNOHANG ; 
 scalar_t__ WTERMSIG (int) ; 
 int /*<<< orphan*/  log_debugx (char*,scalar_t__) ; 
 int /*<<< orphan*/  log_warnx (char*,scalar_t__,scalar_t__) ; 
 scalar_t__ wait4 (int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
wait_for_children(bool block)
{
	pid_t pid;
	int status;
	int num = 0;

	for (;;) {
		/*
		 * If "block" is true, wait for at least one process.
		 */
		if (block && num == 0)
			pid = wait4(-1, &status, 0, NULL);
		else
			pid = wait4(-1, &status, WNOHANG, NULL);
		if (pid <= 0)
			break;
		if (WIFSIGNALED(status)) {
			log_warnx("child process %d terminated with signal %d",
			    pid, WTERMSIG(status));
		} else if (WEXITSTATUS(status) != 0) {
			log_warnx("child process %d terminated with exit status %d",
			    pid, WEXITSTATUS(status));
		} else {
			log_debugx("child process %d terminated gracefully", pid);
		}
		num++;
	}

	return (num);
}