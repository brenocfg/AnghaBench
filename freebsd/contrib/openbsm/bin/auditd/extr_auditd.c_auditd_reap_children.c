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
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 int /*<<< orphan*/  WNOHANG ; 
 int /*<<< orphan*/  WTERMSIG (int) ; 
 int /*<<< orphan*/  auditd_log_info (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waitpid (int,int*,int /*<<< orphan*/ ) ; 

void
auditd_reap_children(void)
{
	pid_t child;
	int wstatus;

	while ((child = waitpid(-1, &wstatus, WNOHANG)) > 0) {
		if (!wstatus)
			continue;
		auditd_log_info("warn process [pid=%d] %s %d.", child,
		    ((WIFEXITED(wstatus)) ? "exited with non-zero status" :
		    "exited as a result of signal"),
		    ((WIFEXITED(wstatus)) ? WEXITSTATUS(wstatus) :
		    WTERMSIG(wstatus)));
	}
}