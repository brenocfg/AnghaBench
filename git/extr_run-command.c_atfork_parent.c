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
struct atfork_state {int /*<<< orphan*/  old; int /*<<< orphan*/  cs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_BUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  die_errno (char*) ; 
 int /*<<< orphan*/  pthread_setcancelstate (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_sigmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void atfork_parent(struct atfork_state *as)
{
#ifdef NO_PTHREADS
	if (sigprocmask(SIG_SETMASK, &as->old, NULL))
		die_errno("sigprocmask");
#else
	CHECK_BUG(pthread_setcancelstate(as->cs, NULL),
		"re-enabling cancellation");
	CHECK_BUG(pthread_sigmask(SIG_SETMASK, &as->old, NULL),
		"restoring signal mask");
#endif
}