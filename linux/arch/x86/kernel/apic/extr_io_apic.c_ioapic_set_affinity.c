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
struct irq_data {TYPE_1__* chip; struct irq_data* parent_data; } ;
struct cpumask {int dummy; } ;
struct TYPE_2__ {int (* irq_set_affinity ) (struct irq_data*,struct cpumask const*,int) ;} ;

/* Variables and functions */
 int IRQ_SET_MASK_OK_DONE ; 
 int /*<<< orphan*/  ioapic_configure_entry (struct irq_data*) ; 
 int /*<<< orphan*/  ioapic_lock ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct irq_data*,struct cpumask const*,int) ; 

__attribute__((used)) static int ioapic_set_affinity(struct irq_data *irq_data,
			       const struct cpumask *mask, bool force)
{
	struct irq_data *parent = irq_data->parent_data;
	unsigned long flags;
	int ret;

	ret = parent->chip->irq_set_affinity(parent, mask, force);
	raw_spin_lock_irqsave(&ioapic_lock, flags);
	if (ret >= 0 && ret != IRQ_SET_MASK_OK_DONE)
		ioapic_configure_entry(irq_data);
	raw_spin_unlock_irqrestore(&ioapic_lock, flags);

	return ret;
}