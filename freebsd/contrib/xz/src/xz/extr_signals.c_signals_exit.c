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
struct sigaction {scalar_t__ sa_flags; int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_ERROR ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int exit_signal ; 
 int /*<<< orphan*/  raise (int) ; 
 int /*<<< orphan*/  set_exit_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigaction (int const,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigfillset (int /*<<< orphan*/ *) ; 

extern void
signals_exit(void)
{
	const int sig = exit_signal;

	if (sig != 0) {
#if defined(TUKLIB_DOSLIKE) || defined(__VMS)
		// Don't raise(), set only exit status. This avoids
		// printing unwanted message about SIGINT when the user
		// presses C-c.
		set_exit_status(E_ERROR);
#else
		struct sigaction sa;
		sa.sa_handler = SIG_DFL;
		sigfillset(&sa.sa_mask);
		sa.sa_flags = 0;
		sigaction(sig, &sa, NULL);
		raise(exit_signal);
#endif
	}

	return;
}