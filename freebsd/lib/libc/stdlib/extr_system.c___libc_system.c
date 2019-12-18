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
struct sigaction {int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_handler; } ;
struct rusage {int dummy; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int pid_t ;
typedef  int /*<<< orphan*/  ign ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  _PATH_BSHELL ; 
 int /*<<< orphan*/  __libc_sigaction (int /*<<< orphan*/ ,struct sigaction*,struct sigaction*) ; 
 int /*<<< orphan*/  __libc_sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __sys_sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _exit (int) ; 
 int _wait4 (int,int*,int /*<<< orphan*/ ,struct rusage*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  execl (int /*<<< orphan*/ ,char*,char*,char const*,char*) ; 
 int /*<<< orphan*/  memset (struct sigaction*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int vfork () ; 

int
__libc_system(const char *command)
{
	pid_t pid, savedpid;
	int pstat;
	struct sigaction ign, intact, quitact;
	sigset_t newsigblock, oldsigblock;

	if (!command)		/* just checking... */
		return(1);

	(void)sigemptyset(&newsigblock);
	(void)sigaddset(&newsigblock, SIGCHLD);
	(void)sigaddset(&newsigblock, SIGINT);
	(void)sigaddset(&newsigblock, SIGQUIT);
	(void)__libc_sigprocmask(SIG_BLOCK, &newsigblock, &oldsigblock);
	switch(pid = vfork()) {
	/*
	 * In the child, use unwrapped syscalls.  libthr is in
	 * undefined state after vfork().
	 */
	case -1:			/* error */
		(void)__libc_sigprocmask(SIG_SETMASK, &oldsigblock, NULL);
		return (-1);
	case 0:				/* child */
		/*
		 * Restore original signal dispositions and exec the command.
		 */
		(void)__sys_sigprocmask(SIG_SETMASK, &oldsigblock, NULL);
		execl(_PATH_BSHELL, "sh", "-c", command, (char *)NULL);
		_exit(127);
	}
	/* 
	 * If we are running means that the child has either completed
	 * its execve, or has failed.
	 * Block SIGINT/QUIT because sh -c handles it and wait for
	 * it to clean up.
	 */
	memset(&ign, 0, sizeof(ign));
	ign.sa_handler = SIG_IGN;
	(void)sigemptyset(&ign.sa_mask);
	(void)__libc_sigaction(SIGINT, &ign, &intact);
	(void)__libc_sigaction(SIGQUIT, &ign, &quitact);
	savedpid = pid;
	do {
		pid = _wait4(savedpid, &pstat, 0, (struct rusage *)0);
	} while (pid == -1 && errno == EINTR);
	(void)__libc_sigaction(SIGINT, &intact, NULL);
	(void)__libc_sigaction(SIGQUIT,  &quitact, NULL);
	(void)__libc_sigprocmask(SIG_SETMASK, &oldsigblock, NULL);
	return (pid == -1 ? -1 : pstat);
}