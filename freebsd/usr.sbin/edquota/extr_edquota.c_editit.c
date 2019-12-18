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
 scalar_t__ EAGAIN ; 
 scalar_t__ EPROCLIM ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGQUIT ; 
 scalar_t__ WEXITSTATUS (int) ; 
 int /*<<< orphan*/  WIFEXITED (int) ; 
 char* _PATH_VI ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  execlp (char const*,char const*,char*,char*) ; 
 int fork () ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  getgid () ; 
 int /*<<< orphan*/  getuid () ; 
 scalar_t__ setgid (int /*<<< orphan*/ ) ; 
 scalar_t__ setuid (int /*<<< orphan*/ ) ; 
 long sigblock (int) ; 
 int sigmask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigsetmask (long) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  waitpid (int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*) ; 

int
editit(char *tmpf)
{
	long omask;
	int pid, status;

	omask = sigblock(sigmask(SIGINT)|sigmask(SIGQUIT)|sigmask(SIGHUP));
 top:
	if ((pid = fork()) < 0) {

		if (errno == EPROCLIM) {
			warnx("you have too many processes");
			return(0);
		}
		if (errno == EAGAIN) {
			sleep(1);
			goto top;
		}
		warn("fork");
		return (0);
	}
	if (pid == 0) {
		const char *ed;

		sigsetmask(omask);
		if (setgid(getgid()) != 0)
			err(1, "setgid failed");
		if (setuid(getuid()) != 0)
			err(1, "setuid failed");
		if ((ed = getenv("EDITOR")) == (char *)0)
			ed = _PATH_VI;
		execlp(ed, ed, tmpf, (char *)0);
		err(1, "%s", ed);
	}
	waitpid(pid, &status, 0);
	sigsetmask(omask);
	if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
		return (0);
	return (1);
}