#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct pt_regs {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EXIT_TO_USERMODE_LOOP_FLAGS ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIF_NOTIFY_RESUME ; 
 int _TIF_NEED_RESCHED ; 
 int _TIF_NOTIFY_RESUME ; 
 int _TIF_PATCH_PENDING ; 
 int _TIF_SIGPENDING ; 
 int _TIF_UPROBE ; 
 int _TIF_USER_RETURN_NOTIFY ; 
 int /*<<< orphan*/  clear_thread_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 TYPE_1__* current_thread_info () ; 
 int /*<<< orphan*/  do_signal (struct pt_regs*) ; 
 int /*<<< orphan*/  fire_user_return_notifiers () ; 
 int /*<<< orphan*/  klp_update_patch_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  rseq_handle_notify_resume (int /*<<< orphan*/ *,struct pt_regs*) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  tracehook_notify_resume (struct pt_regs*) ; 
 int /*<<< orphan*/  uprobe_notify_resume (struct pt_regs*) ; 

__attribute__((used)) static void exit_to_usermode_loop(struct pt_regs *regs, u32 cached_flags)
{
	/*
	 * In order to return to user mode, we need to have IRQs off with
	 * none of EXIT_TO_USERMODE_LOOP_FLAGS set.  Several of these flags
	 * can be set at any time on preemptible kernels if we have IRQs on,
	 * so we need to loop.  Disabling preemption wouldn't help: doing the
	 * work to clear some of the flags can sleep.
	 */
	while (true) {
		/* We have work to do. */
		local_irq_enable();

		if (cached_flags & _TIF_NEED_RESCHED)
			schedule();

		if (cached_flags & _TIF_UPROBE)
			uprobe_notify_resume(regs);

		if (cached_flags & _TIF_PATCH_PENDING)
			klp_update_patch_state(current);

		/* deal with pending signal delivery */
		if (cached_flags & _TIF_SIGPENDING)
			do_signal(regs);

		if (cached_flags & _TIF_NOTIFY_RESUME) {
			clear_thread_flag(TIF_NOTIFY_RESUME);
			tracehook_notify_resume(regs);
			rseq_handle_notify_resume(NULL, regs);
		}

		if (cached_flags & _TIF_USER_RETURN_NOTIFY)
			fire_user_return_notifiers();

		/* Disable IRQs and retry */
		local_irq_disable();

		cached_flags = READ_ONCE(current_thread_info()->flags);

		if (!(cached_flags & EXIT_TO_USERMODE_LOOP_FLAGS))
			break;
	}
}