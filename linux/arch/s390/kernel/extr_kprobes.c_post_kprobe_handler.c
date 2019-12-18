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
struct TYPE_2__ {int mask; } ;
struct pt_regs {TYPE_1__ psw; } ;
struct kprobe_ctlblk {scalar_t__ kprobe_status; } ;
struct kprobe {int /*<<< orphan*/  (* post_handler ) (struct kprobe*,struct pt_regs*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ KPROBE_HIT_SSDONE ; 
 scalar_t__ KPROBE_REENTER ; 
 int PSW_MASK_PER ; 
 struct kprobe_ctlblk* get_kprobe_ctlblk () ; 
 struct kprobe* kprobe_running () ; 
 int /*<<< orphan*/  pop_kprobe (struct kprobe_ctlblk*) ; 
 int /*<<< orphan*/  preempt_enable_no_resched () ; 
 int /*<<< orphan*/  resume_execution (struct kprobe*,struct pt_regs*) ; 
 int /*<<< orphan*/  stub1 (struct kprobe*,struct pt_regs*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int post_kprobe_handler(struct pt_regs *regs)
{
	struct kprobe_ctlblk *kcb = get_kprobe_ctlblk();
	struct kprobe *p = kprobe_running();

	if (!p)
		return 0;

	if (kcb->kprobe_status != KPROBE_REENTER && p->post_handler) {
		kcb->kprobe_status = KPROBE_HIT_SSDONE;
		p->post_handler(p, regs, 0);
	}

	resume_execution(p, regs);
	pop_kprobe(kcb);
	preempt_enable_no_resched();

	/*
	 * if somebody else is singlestepping across a probe point, psw mask
	 * will have PER set, in which case, continue the remaining processing
	 * of do_single_step, as if this is not a probe hit.
	 */
	if (regs->psw.mask & PSW_MASK_PER)
		return 0;

	return 1;
}