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
typedef  int /*<<< orphan*/  sigfunc ;
typedef  int /*<<< orphan*/  shellnam ;
typedef  int pid_t ;

/* Variables and functions */
 int MAXPATHLEN ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  UPRINTF (char*,char*) ; 
 char* _PATH_BSHELL ; 
 int /*<<< orphan*/  altarg ; 
 int /*<<< orphan*/  closefrom (int) ; 
 int code ; 
 int /*<<< orphan*/  execl (char const*,char*,char*,...) ; 
 int /*<<< orphan*/  exit (int) ; 
 int fork () ; 
 int /*<<< orphan*/  fputs (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ ftp_debug ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 char* strrchr (char const*,char) ; 
 int /*<<< orphan*/  ttyout ; 
 int wait (int*) ; 
 int /*<<< orphan*/  warn (char*,...) ; 
 int /*<<< orphan*/  xsignal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
shell(int argc, char *argv[])
{
	pid_t pid;
	sigfunc oldintr;
	char shellnam[MAXPATHLEN];
	const char *shellp, *namep;
	int wait_status;

	if (argc == 0) {
		UPRINTF("usage: %s [command [args]]\n", argv[0]);
		code = -1;
		return;
	}
	oldintr = xsignal(SIGINT, SIG_IGN);
	if ((pid = fork()) == 0) {
		(void)closefrom(3);
		(void)xsignal(SIGINT, SIG_DFL);
		shellp = getenv("SHELL");
		if (shellp == NULL)
			shellp = _PATH_BSHELL;
		namep = strrchr(shellp, '/');
		if (namep == NULL)
			namep = shellp;
		else
			namep++;
		(void)strlcpy(shellnam, namep, sizeof(shellnam));
		if (ftp_debug) {
			fputs(shellp, ttyout);
			putc('\n', ttyout);
		}
		if (argc > 1) {
			execl(shellp, shellnam, "-c", altarg, (char *)0);
		}
		else {
			execl(shellp, shellnam, (char *)0);
		}
		warn("Can't execute `%s'", shellp);
		code = -1;
		exit(1);
	}
	if (pid > 0)
		while (wait(&wait_status) != pid)
			;
	(void)xsignal(SIGINT, oldintr);
	if (pid == -1) {
		warn("Can't fork a subshell; try again later");
		code = -1;
	} else
		code = 0;
}