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
struct pt_regs {unsigned long nip; int msr; } ;
struct kprobe_ctlblk {scalar_t__ kprobe_status; int kprobe_saved_msr; } ;
struct TYPE_2__ {scalar_t__ insn; } ;
struct kprobe {scalar_t__ addr; int /*<<< orphan*/  (* post_handler ) (struct kprobe*,struct pt_regs*,int /*<<< orphan*/ ) ;TYPE_1__ ainsn; } ;

/* Variables and functions */
 scalar_t__ KPROBE_HIT_SSDONE ; 
 scalar_t__ KPROBE_REENTER ; 
 int MSR_SINGLESTEP ; 
 struct kprobe_ctlblk* get_kprobe_ctlblk () ; 
 struct kprobe* kprobe_running () ; 
 int /*<<< orphan*/  preempt_enable_no_resched () ; 
 int /*<<< orphan*/  reset_current_kprobe () ; 
 int /*<<< orphan*/  restore_previous_kprobe (struct kprobe_ctlblk*) ; 
 int /*<<< orphan*/  stub1 (struct kprobe*,struct pt_regs*,int /*<<< orphan*/ ) ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

int kprobe_post_handler(struct pt_regs *regs)
{
	struct kprobe *cur = kprobe_running();
	struct kprobe_ctlblk *kcb = get_kprobe_ctlblk();

	if (!cur || user_mode(regs))
		return 0;

	/* make sure we got here for instruction we have a kprobe on */
	if (((unsigned long)cur->ainsn.insn + 4) != regs->nip)
		return 0;

	if ((kcb->kprobe_status != KPROBE_REENTER) && cur->post_handler) {
		kcb->kprobe_status = KPROBE_HIT_SSDONE;
		cur->post_handler(cur, regs, 0);
	}

	/* Adjust nip to after the single-stepped instruction */
	regs->nip = (unsigned long)cur->addr + 4;
	regs->msr |= kcb->kprobe_saved_msr;

	/*Restore back the original saved kprobes variables and continue. */
	if (kcb->kprobe_status == KPROBE_REENTER) {
		restore_previous_kprobe(kcb);
		goto out;
	}
	reset_current_kprobe();
out:
	preempt_enable_no_resched();

	/*
	 * if somebody else is singlestepping across a probe point, msr
	 * will have DE/SE set, in which case, continue the remaining processing
	 * of do_debug, as if this is not a probe hit.
	 */
	if (regs->msr & MSR_SINGLESTEP)
		return 0;

	return 1;
}