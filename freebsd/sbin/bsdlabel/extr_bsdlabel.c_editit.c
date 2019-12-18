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
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 char* DEFEDITOR ; 
 scalar_t__ EAGAIN ; 
 scalar_t__ EPROCLIM ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  execlp (char const*,char const*,int /*<<< orphan*/ ,char*) ; 
 int fork () ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  getgid () ; 
 int /*<<< orphan*/  getuid () ; 
 int setresgid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int setresuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sigblock (int) ; 
 int sigmask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigsetmask (int) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  tmpfil ; 
 int wait (int*) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static int
editit(void)
{
	int pid, xpid;
	int locstat, omask;
	const char *ed;
	uid_t uid;
	gid_t gid;

	omask = sigblock(sigmask(SIGINT)|sigmask(SIGQUIT)|sigmask(SIGHUP));
	while ((pid = fork()) < 0) {
		if (errno == EPROCLIM) {
			warnx("you have too many processes");
			return(0);
		}
		if (errno != EAGAIN) {
			warn("fork");
			return(0);
		}
		sleep(1);
	}
	if (pid == 0) {
		sigsetmask(omask);
		gid = getgid();
		if (setresgid(gid, gid, gid) == -1)
			err(1, "setresgid");
		uid = getuid();
		if (setresuid(uid, uid, uid) == -1)
			err(1, "setresuid");
		if ((ed = getenv("EDITOR")) == (char *)0)
			ed = DEFEDITOR;
		execlp(ed, ed, tmpfil, (char *)0);
		err(1, "%s", ed);
	}
	while ((xpid = wait(&locstat)) >= 0)
		if (xpid == pid)
			break;
	sigsetmask(omask);
	return(!locstat);
}