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
typedef  int /*<<< orphan*/  SCR ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  FREE_SPACE (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ MIN (size_t,int) ; 
 int /*<<< orphan*/  M_ERR ; 
 int /*<<< orphan*/  M_SYSERR ; 
 scalar_t__ SIGPIPE ; 
 scalar_t__ WCOREDUMP (int) ; 
 scalar_t__ WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 scalar_t__ WIFSIGNALED (int) ; 
 scalar_t__ WTERMSIG (int) ; 
 scalar_t__ cmdskip (char const) ; 
 scalar_t__ errno ; 
 char* msg_print (int /*<<< orphan*/ *,char const*,int*) ; 
 int /*<<< orphan*/  msgq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  sigmsg (scalar_t__) ; 
 size_t strlen (char*) ; 
 int waitpid (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

int
proc_wait(SCR *sp, long int pid, const char *cmd, int silent, int okpipe)
{
	size_t len;
	int nf, pstat;
	char *p;

	/* Wait for the utility, ignoring interruptions. */
	for (;;) {
		errno = 0;
		if (waitpid((pid_t)pid, &pstat, 0) != -1)
			break;
		if (errno != EINTR) {
			msgq(sp, M_SYSERR, "waitpid");
			return (1);
		}
	}

	/*
	 * Display the utility's exit status.  Ignore SIGPIPE from the
	 * parent-writer, as that only means that the utility chose to
	 * exit before reading all of its input.
	 */
	if (WIFSIGNALED(pstat) && (!okpipe || WTERMSIG(pstat) != SIGPIPE)) {
		for (; cmdskip(*cmd); ++cmd);
		p = msg_print(sp, cmd, &nf);
		len = strlen(p);
		msgq(sp, M_ERR, "%.*s%s: received signal: %s%s",
		    (int)MIN(len, 20), p, len > 20 ? " ..." : "",
		    sigmsg(WTERMSIG(pstat)),
		    WCOREDUMP(pstat) ? "; core dumped" : "");
		if (nf)
			FREE_SPACE(sp, p, 0);
		return (1);
	}

	if (WIFEXITED(pstat) && WEXITSTATUS(pstat)) {
		/*
		 * Remain silent for "normal" errors when doing shell file
		 * name expansions, they almost certainly indicate nothing
		 * more than a failure to match.
		 *
		 * Remain silent for vi read filter errors.  It's historic
		 * practice.
		 */
		if (!silent) {
			for (; cmdskip(*cmd); ++cmd);
			p = msg_print(sp, cmd, &nf);
			len = strlen(p);
			msgq(sp, M_ERR, "%.*s%s: exited with status %d",
			    (int)MIN(len, 20), p, len > 20 ? " ..." : "",
			    WEXITSTATUS(pstat));
			if (nf)
				FREE_SPACE(sp, p, 0);
		}
		return (1);
	}
	return (0);
}