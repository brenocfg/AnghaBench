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
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  SIG_UNBLOCK ; 
 int /*<<< orphan*/  audit_logout () ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  pam_cleanup () ; 
 int /*<<< orphan*/ * pwd ; 
 int /*<<< orphan*/  raise (int) ; 
 int /*<<< orphan*/  sigaction (int,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sleep (int) ; 

__attribute__((used)) static void
bail_internal(int sec, int eval, int signo)
{
	struct sigaction sa;

	pam_cleanup();
#ifdef USE_BSM_AUDIT
	if (pwd != NULL)
		audit_logout();
#endif
	(void)sleep(sec);
	if (signo == 0)
		exit(eval);
	else {
		sa.sa_handler = SIG_DFL;
		sa.sa_flags = 0;
		(void)sigemptyset(&sa.sa_mask);
		(void)sigaction(signo, &sa, NULL);
		(void)sigaddset(&sa.sa_mask, signo);
		(void)sigprocmask(SIG_UNBLOCK, &sa.sa_mask, NULL);
		raise(signo);
		exit(128 + signo);
	}
}