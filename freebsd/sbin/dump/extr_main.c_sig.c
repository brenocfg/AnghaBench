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
#define  SIGALRM 134 
#define  SIGBUS 133 
#define  SIGFPE 132 
#define  SIGHUP 131 
#define  SIGSEGV 130 
#define  SIGTERM 129 
#define  SIGTRAP 128 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  X_REWRITE ; 
 int /*<<< orphan*/  close_rewind () ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  msg (char*) ; 
 int /*<<< orphan*/  pipeout ; 
 int /*<<< orphan*/  quit (char*) ; 
 int /*<<< orphan*/  signal (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

void
sig(int signo)
{
	switch(signo) {
	case SIGALRM:
	case SIGBUS:
	case SIGFPE:
	case SIGHUP:
	case SIGTERM:
	case SIGTRAP:
		if (pipeout)
			quit("Signal on pipe: cannot recover\n");
		msg("Rewriting attempted as response to unknown signal.\n");
		(void)fflush(stderr);
		(void)fflush(stdout);
		close_rewind();
		exit(X_REWRITE);
		/* NOTREACHED */
	case SIGSEGV:
		msg("SIGSEGV: ABORTING!\n");
		(void)signal(SIGSEGV, SIG_DFL);
		(void)kill(0, SIGSEGV);
		/* NOTREACHED */
	}
}