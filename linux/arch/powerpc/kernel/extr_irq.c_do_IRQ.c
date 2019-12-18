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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int THREAD_SIZE ; 
 int /*<<< orphan*/  __do_irq (struct pt_regs*) ; 
 int /*<<< orphan*/  call_do_irq (struct pt_regs*,void*) ; 
 int current_stack_pointer () ; 
 void** hardirq_ctx ; 
 size_t raw_smp_processor_id () ; 
 struct pt_regs* set_irq_regs (struct pt_regs*) ; 
 void** softirq_ctx ; 
 scalar_t__ unlikely (int) ; 

void do_IRQ(struct pt_regs *regs)
{
	struct pt_regs *old_regs = set_irq_regs(regs);
	void *cursp, *irqsp, *sirqsp;

	/* Switch to the irq stack to handle this */
	cursp = (void *)(current_stack_pointer() & ~(THREAD_SIZE - 1));
	irqsp = hardirq_ctx[raw_smp_processor_id()];
	sirqsp = softirq_ctx[raw_smp_processor_id()];

	/* Already there ? */
	if (unlikely(cursp == irqsp || cursp == sirqsp)) {
		__do_irq(regs);
		set_irq_regs(old_regs);
		return;
	}
	/* Switch stack and call */
	call_do_irq(regs, irqsp);

	set_irq_regs(old_regs);
}