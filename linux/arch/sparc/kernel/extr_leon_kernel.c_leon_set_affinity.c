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
struct irq_data {scalar_t__ chip_data; } ;
struct cpumask {int dummy; } ;

/* Variables and functions */
 int IRQ_SET_MASK_OK ; 
 unsigned long LEON3_BYPASS_LOAD_PA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LEON3_BYPASS_STORE_PA (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  LEON_IMASK (int) ; 
 int irq_choose_cpu (struct cpumask const*) ; 
 struct cpumask const* irq_data_get_affinity_mask (struct irq_data*) ; 
 int /*<<< orphan*/  leon_irq_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int leon_set_affinity(struct irq_data *data, const struct cpumask *dest,
			     bool force)
{
	unsigned long mask, oldmask, flags;
	int oldcpu, newcpu;

	mask = (unsigned long)data->chip_data;
	oldcpu = irq_choose_cpu(irq_data_get_affinity_mask(data));
	newcpu = irq_choose_cpu(dest);

	if (oldcpu == newcpu)
		goto out;

	/* unmask on old CPU first before enabling on the selected CPU */
	spin_lock_irqsave(&leon_irq_lock, flags);
	oldmask = LEON3_BYPASS_LOAD_PA(LEON_IMASK(oldcpu));
	LEON3_BYPASS_STORE_PA(LEON_IMASK(oldcpu), (oldmask & ~mask));
	oldmask = LEON3_BYPASS_LOAD_PA(LEON_IMASK(newcpu));
	LEON3_BYPASS_STORE_PA(LEON_IMASK(newcpu), (oldmask | mask));
	spin_unlock_irqrestore(&leon_irq_lock, flags);
out:
	return IRQ_SET_MASK_OK;
}