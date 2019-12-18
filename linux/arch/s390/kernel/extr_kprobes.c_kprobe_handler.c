#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int addr; } ;
struct pt_regs {TYPE_2__ psw; } ;
struct kprobe_ctlblk {int /*<<< orphan*/  kprobe_status; } ;
struct TYPE_3__ {scalar_t__ insn; } ;
struct kprobe {TYPE_1__ ainsn; scalar_t__ (* pre_handler ) (struct kprobe*,struct pt_regs*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  KPROBE_HIT_ACTIVE ; 
 int /*<<< orphan*/  KPROBE_HIT_SS ; 
 int /*<<< orphan*/  KPROBE_REENTER ; 
 int /*<<< orphan*/  enable_singlestep (struct kprobe_ctlblk*,struct pt_regs*,unsigned long) ; 
 struct kprobe* get_kprobe (void*) ; 
 struct kprobe_ctlblk* get_kprobe_ctlblk () ; 
 int /*<<< orphan*/  kprobe_reenter_check (struct kprobe_ctlblk*,struct kprobe*) ; 
 scalar_t__ kprobe_running () ; 
 int /*<<< orphan*/  pop_kprobe (struct kprobe_ctlblk*) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable_no_resched () ; 
 int /*<<< orphan*/  push_kprobe (struct kprobe_ctlblk*,struct kprobe*) ; 
 scalar_t__ stub1 (struct kprobe*,struct pt_regs*) ; 

__attribute__((used)) static int kprobe_handler(struct pt_regs *regs)
{
	struct kprobe_ctlblk *kcb;
	struct kprobe *p;

	/*
	 * We want to disable preemption for the entire duration of kprobe
	 * processing. That includes the calls to the pre/post handlers
	 * and single stepping the kprobe instruction.
	 */
	preempt_disable();
	kcb = get_kprobe_ctlblk();
	p = get_kprobe((void *)(regs->psw.addr - 2));

	if (p) {
		if (kprobe_running()) {
			/*
			 * We have hit a kprobe while another is still
			 * active. This can happen in the pre and post
			 * handler. Single step the instruction of the
			 * new probe but do not call any handler function
			 * of this secondary kprobe.
			 * push_kprobe and pop_kprobe saves and restores
			 * the currently active kprobe.
			 */
			kprobe_reenter_check(kcb, p);
			push_kprobe(kcb, p);
			kcb->kprobe_status = KPROBE_REENTER;
		} else {
			/*
			 * If we have no pre-handler or it returned 0, we
			 * continue with single stepping. If we have a
			 * pre-handler and it returned non-zero, it prepped
			 * for changing execution path, so get out doing
			 * nothing more here.
			 */
			push_kprobe(kcb, p);
			kcb->kprobe_status = KPROBE_HIT_ACTIVE;
			if (p->pre_handler && p->pre_handler(p, regs)) {
				pop_kprobe(kcb);
				preempt_enable_no_resched();
				return 1;
			}
			kcb->kprobe_status = KPROBE_HIT_SS;
		}
		enable_singlestep(kcb, regs, (unsigned long) p->ainsn.insn);
		return 1;
	} /* else:
	   * No kprobe at this address and no active kprobe. The trap has
	   * not been caused by a kprobe breakpoint. The race of breakpoint
	   * vs. kprobe remove does not exist because on s390 as we use
	   * stop_machine to arm/disarm the breakpoints.
	   */
	preempt_enable_no_resched();
	return 0;
}