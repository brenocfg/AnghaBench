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
struct pt_regs {unsigned long ip; int /*<<< orphan*/  flags; } ;
struct kprobe_ctlblk {scalar_t__ kprobe_status; int /*<<< orphan*/  kprobe_old_flags; } ;
struct TYPE_2__ {scalar_t__ insn; } ;
struct kprobe {scalar_t__ (* fault_handler ) (struct kprobe*,struct pt_regs*,int) ;scalar_t__ addr; TYPE_1__ ainsn; } ;

/* Variables and functions */
 scalar_t__ KPROBE_HIT_ACTIVE ; 
 scalar_t__ KPROBE_HIT_SS ; 
 scalar_t__ KPROBE_HIT_SSDONE ; 
 scalar_t__ KPROBE_REENTER ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  X86_EFLAGS_TF ; 
 struct kprobe_ctlblk* get_kprobe_ctlblk () ; 
 struct kprobe* kprobe_running () ; 
 int /*<<< orphan*/  kprobes_inc_nmissed_count (struct kprobe*) ; 
 int /*<<< orphan*/  reset_current_kprobe () ; 
 int /*<<< orphan*/  restore_previous_kprobe (struct kprobe_ctlblk*) ; 
 scalar_t__ stub1 (struct kprobe*,struct pt_regs*,int) ; 
 scalar_t__ unlikely (int) ; 

int kprobe_fault_handler(struct pt_regs *regs, int trapnr)
{
	struct kprobe *cur = kprobe_running();
	struct kprobe_ctlblk *kcb = get_kprobe_ctlblk();

	if (unlikely(regs->ip == (unsigned long)cur->ainsn.insn)) {
		/* This must happen on single-stepping */
		WARN_ON(kcb->kprobe_status != KPROBE_HIT_SS &&
			kcb->kprobe_status != KPROBE_REENTER);
		/*
		 * We are here because the instruction being single
		 * stepped caused a page fault. We reset the current
		 * kprobe and the ip points back to the probe address
		 * and allow the page fault handler to continue as a
		 * normal page fault.
		 */
		regs->ip = (unsigned long)cur->addr;
		/*
		 * Trap flag (TF) has been set here because this fault
		 * happened where the single stepping will be done.
		 * So clear it by resetting the current kprobe:
		 */
		regs->flags &= ~X86_EFLAGS_TF;

		/*
		 * If the TF flag was set before the kprobe hit,
		 * don't touch it:
		 */
		regs->flags |= kcb->kprobe_old_flags;

		if (kcb->kprobe_status == KPROBE_REENTER)
			restore_previous_kprobe(kcb);
		else
			reset_current_kprobe();
	} else if (kcb->kprobe_status == KPROBE_HIT_ACTIVE ||
		   kcb->kprobe_status == KPROBE_HIT_SSDONE) {
		/*
		 * We increment the nmissed count for accounting,
		 * we can also use npre/npostfault count for accounting
		 * these specific fault cases.
		 */
		kprobes_inc_nmissed_count(cur);

		/*
		 * We come here because instructions in the pre/post
		 * handler caused the page_fault, this could happen
		 * if handler tries to access user space by
		 * copy_from_user(), get_user() etc. Let the
		 * user-specified handler try to fix it first.
		 */
		if (cur->fault_handler && cur->fault_handler(cur, regs, trapnr))
			return 1;
	}

	return 0;
}