#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sigscratch {int /*<<< orphan*/  pt; } ;
typedef  int /*<<< orphan*/  sigset_t ;
struct TYPE_5__ {scalar_t__ pfm_needs_checking; } ;
struct TYPE_7__ {TYPE_1__ thread; } ;
struct TYPE_6__ {int lp; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIF_NOTIFY_RESUME ; 
 int /*<<< orphan*/  TIF_RESTORE_RSE ; 
 int /*<<< orphan*/  TIF_SIGPENDING ; 
 TYPE_3__* current ; 
 scalar_t__ fsys_mode (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ia64_do_signal (struct sigscratch*,long) ; 
 TYPE_2__* ia64_psr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ia64_sync_krbs () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  pfm_handle_work () ; 
 scalar_t__ test_and_clear_thread_flag (int /*<<< orphan*/ ) ; 
 scalar_t__ test_thread_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tracehook_notify_resume (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (scalar_t__) ; 

void
do_notify_resume_user(sigset_t *unused, struct sigscratch *scr, long in_syscall)
{
	if (fsys_mode(current, &scr->pt)) {
		/*
		 * defer signal-handling etc. until we return to
		 * privilege-level 0.
		 */
		if (!ia64_psr(&scr->pt)->lp)
			ia64_psr(&scr->pt)->lp = 1;
		return;
	}

#ifdef CONFIG_PERFMON
	if (current->thread.pfm_needs_checking)
		/*
		 * Note: pfm_handle_work() allow us to call it with interrupts
		 * disabled, and may enable interrupts within the function.
		 */
		pfm_handle_work();
#endif

	/* deal with pending signal delivery */
	if (test_thread_flag(TIF_SIGPENDING)) {
		local_irq_enable();	/* force interrupt enable */
		ia64_do_signal(scr, in_syscall);
	}

	if (test_and_clear_thread_flag(TIF_NOTIFY_RESUME)) {
		local_irq_enable();	/* force interrupt enable */
		tracehook_notify_resume(&scr->pt);
	}

	/* copy user rbs to kernel rbs */
	if (unlikely(test_thread_flag(TIF_RESTORE_RSE))) {
		local_irq_enable();	/* force interrupt enable */
		ia64_sync_krbs();
	}

	local_irq_disable();	/* force interrupt disable */
}