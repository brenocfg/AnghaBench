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
struct sigaction {int /*<<< orphan*/  sa_mask; scalar_t__ sa_flags; int /*<<< orphan*/  sa_handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGABRT ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  __cleanup () ; 
 int /*<<< orphan*/  __libc_sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __libc_sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  raise (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigdelset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigfillset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 () ; 

void
abort(void)
{
	struct sigaction act;

	/*
	 * POSIX requires we flush stdio buffers on abort.
	 * XXX ISO C requires that abort() be async-signal-safe.
	 */
	if (__cleanup)
		(*__cleanup)();

	sigfillset(&act.sa_mask);
	/*
	 * Don't block SIGABRT to give any handler a chance; we ignore
	 * any errors -- ISO C doesn't allow abort to return anyway.
	 */
	sigdelset(&act.sa_mask, SIGABRT);
	(void)__libc_sigprocmask(SIG_SETMASK, &act.sa_mask, NULL);
	(void)raise(SIGABRT);

	/*
	 * If SIGABRT was ignored, or caught and the handler returns, do
	 * it again, only harder.
	 */
	act.sa_handler = SIG_DFL;
	act.sa_flags = 0;
	sigfillset(&act.sa_mask);
	(void)__libc_sigaction(SIGABRT, &act, NULL);
	sigdelset(&act.sa_mask, SIGABRT);
	(void)__libc_sigprocmask(SIG_SETMASK, &act.sa_mask, NULL);
	(void)raise(SIGABRT);
	exit(1);
}