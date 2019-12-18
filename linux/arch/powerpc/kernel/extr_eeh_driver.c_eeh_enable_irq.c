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
struct eeh_dev {int mode; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int EEH_DEV_IRQ_DISABLED ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_get_irq_data (int /*<<< orphan*/ ) ; 
 scalar_t__ irqd_irq_disabled (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void eeh_enable_irq(struct eeh_dev *edev)
{
	if ((edev->mode) & EEH_DEV_IRQ_DISABLED) {
		edev->mode &= ~EEH_DEV_IRQ_DISABLED;
		/*
		 * FIXME !!!!!
		 *
		 * This is just ass backwards. This maze has
		 * unbalanced irq_enable/disable calls. So instead of
		 * finding the root cause it works around the warning
		 * in the irq_enable code by conditionally calling
		 * into it.
		 *
		 * That's just wrong.The warning in the core code is
		 * there to tell people to fix their asymmetries in
		 * their own code, not by abusing the core information
		 * to avoid it.
		 *
		 * I so wish that the assymetry would be the other way
		 * round and a few more irq_disable calls render that
		 * shit unusable forever.
		 *
		 *	tglx
		 */
		if (irqd_irq_disabled(irq_get_irq_data(edev->pdev->irq)))
			enable_irq(edev->pdev->irq);
	}
}