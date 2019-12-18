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
struct event_cmd_exec {int /*<<< orphan*/  line; } ;
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINTR ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  _PATH_BSHELL ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  execl (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,char*) ; 
 int fork () ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*) ; 

int
event_cmd_exec_act(void *this)
{
	struct event_cmd_exec * p = this;
	int status = -1;
	pid_t pid;

	switch ((pid = fork())) {
	case -1:
		warn("cannot fork");
		break;
	case 0:
		/* child process */
		signal(SIGHUP, SIG_DFL);
		signal(SIGCHLD, SIG_DFL);
		signal(SIGTERM, SIG_DFL);
		execl(_PATH_BSHELL, "sh", "-c", p->line, (char *)NULL);
		_exit(127);
	default:
		/* parent process */
		do {
			pid = waitpid(pid, &status, 0);
		} while (pid == -1 && errno == EINTR);
		break;
	}
	return status;
}