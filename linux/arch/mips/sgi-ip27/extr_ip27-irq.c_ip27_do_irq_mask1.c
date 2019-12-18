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
 unsigned long LOCAL_HUB_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PI_INT_PEND1 ; 
 scalar_t__ __ffs (unsigned long) ; 
 int /*<<< orphan*/  generic_handle_irq (int) ; 
 struct irq_domain* irq_desc_get_handler_data (struct irq_desc*) ; 
 int /*<<< orphan*/  irq_enable_mask ; 
 int irq_linear_revmap (struct irq_domain*,scalar_t__) ; 
 unsigned long* per_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  spurious_interrupt () ; 

__attribute__((used)) static void ip27_do_irq_mask1(struct irq_desc *desc)
{
	cpuid_t cpu = smp_processor_id();
	unsigned long *mask = per_cpu(irq_enable_mask, cpu);
	struct irq_domain *domain;
	u64 pend1;
	int irq;

	/* copied from Irix intpend0() */
	pend1 = LOCAL_HUB_L(PI_INT_PEND1);

	pend1 &= mask[1];		/* Pick intrs we should look at */
	if (!pend1)
		return;

	domain = irq_desc_get_handler_data(desc);
	irq = irq_linear_revmap(domain, __ffs(pend1) + 64);
	if (irq)
		generic_handle_irq(irq);
	else
		spurious_interrupt();

	LOCAL_HUB_L(PI_INT_PEND1);
}