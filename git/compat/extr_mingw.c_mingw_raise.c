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
 int /*<<< orphan*/  EINVAL ; 
#define  SIGABRT 136 
#define  SIGABRT_COMPAT 135 
#define  SIGALRM 134 
#define  SIGBREAK 133 
#define  SIGFPE 132 
#define  SIGILL 131 
#define  SIGINT 130 
#define  SIGSEGV 129 
#define  SIGTERM 128 
 int /*<<< orphan*/  SIG_DFL (int const) ; 
 int /*<<< orphan*/  SIG_IGN (int const) ; 
 int /*<<< orphan*/  STDERR_FILENO ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isatty (int /*<<< orphan*/ ) ; 
 int raise (int) ; 
 int /*<<< orphan*/  sigint_fn (int const) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  timer_fn (int const) ; 

int mingw_raise(int sig)
{
	switch (sig) {
	case SIGALRM:
		if (timer_fn == SIG_DFL) {
			if (isatty(STDERR_FILENO))
				fputs("Alarm clock\n", stderr);
			exit(128 + SIGALRM);
		} else if (timer_fn != SIG_IGN)
			timer_fn(SIGALRM);
		return 0;

	case SIGINT:
		if (sigint_fn == SIG_DFL)
			exit(128 + SIGINT);
		else if (sigint_fn != SIG_IGN)
			sigint_fn(SIGINT);
		return 0;

#if defined(_MSC_VER)
	case SIGILL:
	case SIGFPE:
	case SIGSEGV:
	case SIGTERM:
	case SIGBREAK:
	case SIGABRT:
	case SIGABRT_COMPAT:
		/*
		 * The <signal.h> header in the MS C Runtime defines 8 signals
		 * as being supported on the platform. Anything else causes an
		 * "Invalid signal or error" (which in DEBUG builds causes the
		 * Abort/Retry/Ignore dialog). We by-pass the CRT for things we
		 * already know will fail.
		 */
		return raise(sig);
	default:
		errno = EINVAL;
		return -1;

#else

	default:
		return raise(sig);

#endif

	}
}