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
struct pt_regs {int flags; } ;
struct kprobe_ctlblk {int kprobe_saved_flags; scalar_t__ kprobe_status; } ;
struct kprobe {int /*<<< orphan*/  (* post_handler ) (struct kprobe*,struct pt_regs*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ KPROBE_HIT_SSDONE ; 
 scalar_t__ KPROBE_REENTER ; 
 int X86_EFLAGS_TF ; 
 struct kprobe_ctlblk* get_kprobe_ctlblk () ; 
 struct kprobe* kprobe_running () ; 
 int /*<<< orphan*/  reset_current_kprobe () ; 
 int /*<<< orphan*/  restore_previous_kprobe (struct kprobe_ctlblk*) ; 
 int /*<<< orphan*/  resume_execution (struct kprobe*,struct pt_regs*,struct kprobe_ctlblk*) ; 
 int /*<<< orphan*/  stub1 (struct kprobe*,struct pt_regs*,int /*<<< orphan*/ ) ; 

int kprobe_debug_handler(struct pt_regs *regs)
{
	struct kprobe *cur = kprobe_running();
	struct kprobe_ctlblk *kcb = get_kprobe_ctlblk();

	if (!cur)
		return 0;

	resume_execution(cur, regs, kcb);
	regs->flags |= kcb->kprobe_saved_flags;

	if ((kcb->kprobe_status != KPROBE_REENTER) && cur->post_handler) {
		kcb->kprobe_status = KPROBE_HIT_SSDONE;
		cur->post_handler(cur, regs, 0);
	}

	/* Restore back the original saved kprobes variables and continue. */
	if (kcb->kprobe_status == KPROBE_REENTER) {
		restore_previous_kprobe(kcb);
		goto out;
	}
	reset_current_kprobe();
out:
	/*
	 * if somebody else is singlestepping across a probe point, flags
	 * will have TF set, in which case, continue the remaining processing
	 * of do_debug, as if this is not a probe hit.
	 */
	if (regs->flags & X86_EFLAGS_TF)
		return 0;

	return 1;
}