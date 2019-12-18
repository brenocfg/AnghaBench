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
struct servtab {int se_numchild; scalar_t__* se_pids; scalar_t__ se_maxchild; int /*<<< orphan*/  se_server; struct servtab* se_next; } ;
struct rusage {int dummy; } ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_WARNING ; 
 scalar_t__ WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 scalar_t__ WIFSIGNALED (int) ; 
 int /*<<< orphan*/  WNOHANG ; 
 scalar_t__ WTERMSIG (int) ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  enable (struct servtab*) ; 
 int /*<<< orphan*/  reapchild_conn (scalar_t__) ; 
 struct servtab* servtab ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,char*,scalar_t__) ; 
 scalar_t__ wait3 (int*,int /*<<< orphan*/ ,struct rusage*) ; 
 int /*<<< orphan*/  warnx (char*,scalar_t__,char*,scalar_t__) ; 

__attribute__((used)) static void
reapchild(void)
{
	int k, status;
	pid_t pid;
	struct servtab *sep;

	for (;;) {
		pid = wait3(&status, WNOHANG, (struct rusage *)0);
		if (pid <= 0)
			break;
		if (debug)
			warnx("%d reaped, %s %u", pid,
			    WIFEXITED(status) ? "status" : "signal",
			    WIFEXITED(status) ? WEXITSTATUS(status)
				: WTERMSIG(status));
		for (sep = servtab; sep; sep = sep->se_next) {
			for (k = 0; k < sep->se_numchild; k++)
				if (sep->se_pids[k] == pid)
					break;
			if (k == sep->se_numchild)
				continue;
			if (sep->se_numchild == sep->se_maxchild)
				enable(sep);
			sep->se_pids[k] = sep->se_pids[--sep->se_numchild];
			if (WIFSIGNALED(status) || WEXITSTATUS(status))
				syslog(LOG_WARNING,
				    "%s[%d]: exited, %s %u",
				    sep->se_server, pid,
				    WIFEXITED(status) ? "status" : "signal",
				    WIFEXITED(status) ? WEXITSTATUS(status)
					: WTERMSIG(status));
			break;
		}
		reapchild_conn(pid);
	}
}