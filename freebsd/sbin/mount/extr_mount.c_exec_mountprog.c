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
 int /*<<< orphan*/  ENOENT ; 
 int WEXITSTATUS (int) ; 
 int /*<<< orphan*/  WIFEXITED (int) ; 
 int /*<<< orphan*/  WIFSIGNALED (int) ; 
 size_t WTERMSIG (int) ; 
 int /*<<< orphan*/  _PATH_SYSPATH ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  execvP (char const*,int /*<<< orphan*/ ,char* const*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fork () ; 
 int /*<<< orphan*/ * sys_siglist ; 
 int /*<<< orphan*/  waitpid (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,...) ; 
 int /*<<< orphan*/  warnx (char*,char const*,...) ; 

__attribute__((used)) static int
exec_mountprog(const char *name, const char *execname, char *const argv[])
{
	pid_t pid;
	int status;

	switch (pid = fork()) {
	case -1:				/* Error. */
		warn("fork");
		exit (1);
	case 0:					/* Child. */
		/* Go find an executable. */
		execvP(execname, _PATH_SYSPATH, argv);
		if (errno == ENOENT) {
			warn("exec %s not found", execname);
			if (execname[0] != '/') {
				warnx("in path: %s", _PATH_SYSPATH);
			}
		}
		exit(1);
	default:				/* Parent. */
		if (waitpid(pid, &status, 0) < 0) {
			warn("waitpid");
			return (1);
		}

		if (WIFEXITED(status)) {
			if (WEXITSTATUS(status) != 0)
				return (WEXITSTATUS(status));
		} else if (WIFSIGNALED(status)) {
			warnx("%s: %s", name, sys_siglist[WTERMSIG(status)]);
			return (1);
		}
		break;
	}

	return (0);
}