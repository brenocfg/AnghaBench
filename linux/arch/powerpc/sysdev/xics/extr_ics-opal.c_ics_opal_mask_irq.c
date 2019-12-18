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
struct irq_data {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 unsigned int XICS_IPI ; 
 unsigned int XICS_IRQ_SPURIOUS ; 
 int /*<<< orphan*/  ics_opal_mask_real_irq (unsigned int) ; 
 scalar_t__ irqd_to_hwirq (struct irq_data*) ; 
 int /*<<< orphan*/  pr_devel (char*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void ics_opal_mask_irq(struct irq_data *d)
{
	unsigned int hw_irq = (unsigned int)irqd_to_hwirq(d);

	pr_devel("ics-hal: mask virq %d [hw 0x%x]\n", d->irq, hw_irq);

	if (hw_irq == XICS_IPI || hw_irq == XICS_IRQ_SPURIOUS)
		return;
	ics_opal_mask_real_irq(hw_irq);
}