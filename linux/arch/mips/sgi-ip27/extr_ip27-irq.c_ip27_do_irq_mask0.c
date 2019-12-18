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
typedef  unsigned long u64 ;
struct irq_domain {int dummy; } ;
struct irq_desc {int dummy; } ;
typedef  int /*<<< orphan*/  cpuid_t ;

/* Variables and functions */
 unsigned long CPU_CALL_A_IRQ ; 
 unsigned long CPU_CALL_B_IRQ ; 
 unsigned long CPU_RESCHED_A_IRQ ; 
 unsigned long CPU_RESCHED_B_IRQ ; 
 int /*<<< orphan*/  LOCAL_HUB_CLR_INTR (unsigned long) ; 
 unsigned long LOCAL_HUB_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PI_INT_PEND0 ; 
 int /*<<< orphan*/  __ffs (unsigned long) ; 
 int /*<<< orphan*/  generic_handle_irq (int) ; 
 int /*<<< orphan*/  generic_smp_call_function_interrupt () ; 
 struct irq_domain* irq_desc_get_handler_data (struct irq_desc*) ; 
 int /*<<< orphan*/  irq_enable_mask ; 
 int irq_linear_revmap (struct irq_domain*,int /*<<< orphan*/ ) ; 
 unsigned long* per_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scheduler_ipi () ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  spurious_interrupt () ; 

__attribute__((used)) static void ip27_do_irq_mask0(struct irq_desc *desc)
{
	cpuid_t cpu = smp_processor_id();
	unsigned long *mask = per_cpu(irq_enable_mask, cpu);
	struct irq_domain *domain;
	u64 pend0;
	int irq;

	/* copied from Irix intpend0() */
	pend0 = LOCAL_HUB_L(PI_INT_PEND0);

	pend0 &= mask[0];		/* Pick intrs we should look at */
	if (!pend0)
		return;

#ifdef CONFIG_SMP
	if (pend0 & (1UL << CPU_RESCHED_A_IRQ)) {
		LOCAL_HUB_CLR_INTR(CPU_RESCHED_A_IRQ);
		scheduler_ipi();
	} else if (pend0 & (1UL << CPU_RESCHED_B_IRQ)) {
		LOCAL_HUB_CLR_INTR(CPU_RESCHED_B_IRQ);
		scheduler_ipi();
	} else if (pend0 & (1UL << CPU_CALL_A_IRQ)) {
		LOCAL_HUB_CLR_INTR(CPU_CALL_A_IRQ);
		generic_smp_call_function_interrupt();
	} else if (pend0 & (1UL << CPU_CALL_B_IRQ)) {
		LOCAL_HUB_CLR_INTR(CPU_CALL_B_IRQ);
		generic_smp_call_function_interrupt();
	} else
#endif
	{
		domain = irq_desc_get_handler_data(desc);
		irq = irq_linear_revmap(domain, __ffs(pend0));
		if (irq)
			generic_handle_irq(irq);
		else
			spurious_interrupt();
	}

	LOCAL_HUB_L(PI_INT_PEND0);
}