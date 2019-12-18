#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {unsigned long orig_ax; scalar_t__ ip; scalar_t__ gs; int /*<<< orphan*/  cs; } ;
struct TYPE_5__ {scalar_t__ addr; } ;
struct optimized_kprobe {TYPE_1__ kp; } ;
struct kprobe_ctlblk {int /*<<< orphan*/  kprobe_status; } ;

/* Variables and functions */
 scalar_t__ INT3_SIZE ; 
 int /*<<< orphan*/  KPROBE_HIT_ACTIVE ; 
 int /*<<< orphan*/  __KERNEL_CS ; 
 int /*<<< orphan*/  __this_cpu_write (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  current_kprobe ; 
 int /*<<< orphan*/  get_kernel_rpl () ; 
 struct kprobe_ctlblk* get_kprobe_ctlblk () ; 
 scalar_t__ kprobe_disabled (TYPE_1__*) ; 
 scalar_t__ kprobe_running () ; 
 int /*<<< orphan*/  kprobes_inc_nmissed_count (TYPE_1__*) ; 
 int /*<<< orphan*/  opt_pre_handler (TYPE_1__*,struct pt_regs*) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 

__attribute__((used)) static void
optimized_callback(struct optimized_kprobe *op, struct pt_regs *regs)
{
	/* This is possible if op is under delayed unoptimizing */
	if (kprobe_disabled(&op->kp))
		return;

	preempt_disable();
	if (kprobe_running()) {
		kprobes_inc_nmissed_count(&op->kp);
	} else {
		struct kprobe_ctlblk *kcb = get_kprobe_ctlblk();
		/* Save skipped registers */
		regs->cs = __KERNEL_CS;
#ifdef CONFIG_X86_32
		regs->cs |= get_kernel_rpl();
		regs->gs = 0;
#endif
		regs->ip = (unsigned long)op->kp.addr + INT3_SIZE;
		regs->orig_ax = ~0UL;

		__this_cpu_write(current_kprobe, &op->kp);
		kcb->kprobe_status = KPROBE_HIT_ACTIVE;
		opt_pre_handler(&op->kp, regs);
		__this_cpu_write(current_kprobe, NULL);
	}
	preempt_enable();
}