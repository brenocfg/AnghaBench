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
typedef  int u64 ;

/* Variables and functions */
 int K_BCM1480_INT_MBOX_0_0 ; 
 unsigned int SMP_CALL_FUNCTION ; 
 unsigned int SMP_RESCHEDULE_YOURSELF ; 
 int __raw_readq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writeq (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_smp_call_function_interrupt () ; 
 int /*<<< orphan*/  irq_enter () ; 
 int /*<<< orphan*/  irq_exit () ; 
 int /*<<< orphan*/  kstat_incr_irq_this_cpu (int) ; 
 int /*<<< orphan*/ * mailbox_0_clear_regs ; 
 int /*<<< orphan*/ * mailbox_0_regs ; 
 int /*<<< orphan*/  scheduler_ipi () ; 
 int smp_processor_id () ; 

void bcm1480_mailbox_interrupt(void)
{
	int cpu = smp_processor_id();
	int irq = K_BCM1480_INT_MBOX_0_0;
	unsigned int action;

	kstat_incr_irq_this_cpu(irq);
	/* Load the mailbox register to figure out what we're supposed to do */
	action = (__raw_readq(mailbox_0_regs[cpu]) >> 48) & 0xffff;

	/* Clear the mailbox to clear the interrupt */
	__raw_writeq(((u64)action)<<48, mailbox_0_clear_regs[cpu]);

	if (action & SMP_RESCHEDULE_YOURSELF)
		scheduler_ipi();

	if (action & SMP_CALL_FUNCTION) {
		irq_enter();
		generic_smp_call_function_interrupt();
		irq_exit();
	}
}