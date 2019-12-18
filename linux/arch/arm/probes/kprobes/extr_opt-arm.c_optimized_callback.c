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
struct pt_regs {unsigned long ARM_pc; unsigned long ARM_ORIG_r0; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* insn_singlestep ) (int /*<<< orphan*/ ,TYPE_1__*,struct pt_regs*) ;int /*<<< orphan*/  kprobe_direct_exec; } ;
struct kprobe {TYPE_1__ ainsn; int /*<<< orphan*/  opcode; scalar_t__ addr; } ;
struct optimized_kprobe {struct kprobe kp; } ;
struct kprobe_ctlblk {int /*<<< orphan*/  kprobe_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  KPROBE_HIT_ACTIVE ; 
 int /*<<< orphan*/  __this_cpu_write (int /*<<< orphan*/ ,struct kprobe*) ; 
 int /*<<< orphan*/  current_kprobe ; 
 struct kprobe_ctlblk* get_kprobe_ctlblk () ; 
 scalar_t__ kprobe_running () ; 
 int /*<<< orphan*/  kprobes_inc_nmissed_count (struct kprobe*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  opt_pre_handler (struct kprobe*,struct pt_regs*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_1__*,struct pt_regs*) ; 

__attribute__((used)) static void
optimized_callback(struct optimized_kprobe *op, struct pt_regs *regs)
{
	unsigned long flags;
	struct kprobe *p = &op->kp;
	struct kprobe_ctlblk *kcb;

	/* Save skipped registers */
	regs->ARM_pc = (unsigned long)op->kp.addr;
	regs->ARM_ORIG_r0 = ~0UL;

	local_irq_save(flags);
	kcb = get_kprobe_ctlblk();

	if (kprobe_running()) {
		kprobes_inc_nmissed_count(&op->kp);
	} else {
		__this_cpu_write(current_kprobe, &op->kp);
		kcb->kprobe_status = KPROBE_HIT_ACTIVE;
		opt_pre_handler(&op->kp, regs);
		__this_cpu_write(current_kprobe, NULL);
	}

	/*
	 * We singlestep the replaced instruction only when it can't be
	 * executed directly during restore.
	 */
	if (!p->ainsn.kprobe_direct_exec)
		op->kp.ainsn.insn_singlestep(p->opcode, &p->ainsn, regs);

	local_irq_restore(flags);
}