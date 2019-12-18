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
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  SYSLOG_LEVEL_DEBUG1 ; 
 int /*<<< orphan*/  SYSLOG_LEVEL_INFO ; 
 scalar_t__ WEXITSTATUS (int) ; 
 scalar_t__ WIFSIGNALED (int) ; 
 int /*<<< orphan*/  WTERMSIG (int) ; 
 int /*<<< orphan*/  do_log2 (int /*<<< orphan*/ ,char*,char const*,char const*,scalar_t__) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error (char*,char const*,char const*,...) ; 
 char* strerror (scalar_t__) ; 
 int waitpid (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

int
exited_cleanly(pid_t pid, const char *tag, const char *cmd, int quiet)
{
	int status;

	while (waitpid(pid, &status, 0) == -1) {
		if (errno != EINTR) {
			error("%s: waitpid: %s", tag, strerror(errno));
			return -1;
		}
	}
	if (WIFSIGNALED(status)) {
		error("%s %s exited on signal %d", tag, cmd, WTERMSIG(status));
		return -1;
	} else if (WEXITSTATUS(status) != 0) {
		do_log2(quiet ? SYSLOG_LEVEL_DEBUG1 : SYSLOG_LEVEL_INFO,
		    "%s %s failed, status %d", tag, cmd, WEXITSTATUS(status));
		return -1;
	}
	return 0;
}