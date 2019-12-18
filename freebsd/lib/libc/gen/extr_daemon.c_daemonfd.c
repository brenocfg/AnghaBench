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
struct sigaction {scalar_t__ sa_flags; int /*<<< orphan*/  sa_handler; int /*<<< orphan*/  sa_mask; } ;
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  STDERR_FILENO ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int __libc_sigaction (int /*<<< orphan*/ ,struct sigaction*,struct sigaction*) ; 
 int /*<<< orphan*/  _dup2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/  fchdir (int) ; 
 int fork () ; 
 int setsid () ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 

int
daemonfd(int chdirfd, int nullfd)
{
	struct sigaction osa, sa;
	pid_t newgrp;
	int oerrno;
	int osa_ok;

	/* A SIGHUP may be thrown when the parent exits below. */
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
	osa_ok = __libc_sigaction(SIGHUP, &sa, &osa);

	switch (fork()) {
	case -1:
		return (-1);
	case 0:
		break;
	default:
		/*
		 * A fine point:  _exit(0), not exit(0), to avoid triggering
		 * atexit(3) processing
		 */
		_exit(0);
	}

	newgrp = setsid();
	oerrno = errno;
	if (osa_ok != -1)
		__libc_sigaction(SIGHUP, &osa, NULL);

	if (newgrp == -1) {
		errno = oerrno;
		return (-1);
	}

	if (chdirfd != -1)
		(void)fchdir(chdirfd);

	if (nullfd != -1) {
		(void)_dup2(nullfd, STDIN_FILENO);
		(void)_dup2(nullfd, STDOUT_FILENO);
		(void)_dup2(nullfd, STDERR_FILENO);
	}
	return (0);
}