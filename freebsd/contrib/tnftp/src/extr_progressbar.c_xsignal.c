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

/* Variables and functions */
#define  SIGALRM 135 
#define  SIGINFO 134 
#define  SIGINT 133 
#define  SIGPIPE 132 
#define  SIGQUIT 131 
#define  SIGUSR1 130 
#define  SIGUSR2 129 
#define  SIGWINCH 128 
 int /*<<< orphan*/  errx (int,char*,int) ; 
 int /*<<< orphan*/  xsignal_restart (int,int /*<<< orphan*/ ,int) ; 

sigfunc
xsignal(int sig, sigfunc func)
{
	int restartable;

	/*
	 * Some signals print output or change the state of the process.
	 * There should be restartable, so that reads and writes are
	 * not affected.  Some signals should cause program flow to change;
	 * these signals should not be restartable, so that the system call
	 * will return with EINTR, and the program will go do something
	 * different.  If the signal handler calls longjmp() or siglongjmp(),
	 * it doesn't matter if it's restartable.
	 */

	switch(sig) {
#ifdef SIGINFO
	case SIGINFO:
#endif
	case SIGQUIT:
	case SIGUSR1:
	case SIGUSR2:
	case SIGWINCH:
		restartable = 1;
		break;

	case SIGALRM:
	case SIGINT:
	case SIGPIPE:
		restartable = 0;
		break;

	default:
		/*
		 * This is unpleasant, but I don't know what would be better.
		 * Right now, this "can't happen"
		 */
		errx(1, "xsignal_restart: called with signal %d", sig);
	}

	return(xsignal_restart(sig, func, restartable));
}