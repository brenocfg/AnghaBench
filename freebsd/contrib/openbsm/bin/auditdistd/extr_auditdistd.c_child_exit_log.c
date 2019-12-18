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
 int WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 scalar_t__ WIFSIGNALED (int) ; 
 int WTERMSIG (int) ; 
 int /*<<< orphan*/  pjdlog_debug (int,char*,char const*,unsigned int) ; 
 int /*<<< orphan*/  pjdlog_error (char*,char const*,unsigned int,int) ; 

__attribute__((used)) static void
child_exit_log(const char *type, unsigned int pid, int status)
{

	if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
		pjdlog_debug(1, "%s process exited gracefully (pid=%u).",
		    type, pid);
	} else if (WIFSIGNALED(status)) {
		pjdlog_error("%s process killed (pid=%u, signal=%d).",
		    type, pid, WTERMSIG(status));
	} else {
		pjdlog_error("%s process exited ungracefully (pid=%u, exitcode=%d).",
		    type, pid, WIFEXITED(status) ? WEXITSTATUS(status) : -1);
	}
}