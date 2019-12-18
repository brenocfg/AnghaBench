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
typedef  int /*<<< orphan*/  sig_t ;
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  execl (char const*,char const*,char*,char const*,char*) ; 
 int sigblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigmask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigsetmask (int) ; 
 int vfork () ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 

__attribute__((used)) static int
exec_shell(const char *command, const char *use_shell, const char *use_name)
{
	pid_t pid;
	int omask, pstat;
	sig_t intsave, quitsave;

	if (!command)		/* just checking... */
		return(1);

	omask = sigblock(sigmask(SIGCHLD));
	switch(pid = vfork()) {
	case -1:			/* error */
		err(1, "vfork");
	case 0:				/* child */
		(void)sigsetmask(omask);
		execl(use_shell, use_name, "-c", command, (char *)NULL);
		warn("%s", use_shell);
		_exit(1);
	}
	intsave = signal(SIGINT, SIG_IGN);
	quitsave = signal(SIGQUIT, SIG_IGN);
	pid = waitpid(pid, &pstat, 0);
	(void)sigsetmask(omask);
	(void)signal(SIGINT, intsave);
	(void)signal(SIGQUIT, quitsave);
	return(pid == -1 ? -1 : pstat);
}