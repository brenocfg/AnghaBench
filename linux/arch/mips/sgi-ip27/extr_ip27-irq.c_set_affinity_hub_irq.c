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
struct irq_data {int dummy; } ;
struct hub_irq_data {int /*<<< orphan*/  cpu; } ;
struct cpumask {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  cpumask_of (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_hub_irq (struct irq_data*) ; 
 int /*<<< orphan*/  enable_hub_irq (struct irq_data*) ; 
 struct hub_irq_data* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irq_data_update_effective_affinity (struct irq_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ irqd_is_started (struct irq_data*) ; 
 int /*<<< orphan*/  setup_hub_mask (struct hub_irq_data*,struct cpumask const*) ; 

__attribute__((used)) static int set_affinity_hub_irq(struct irq_data *d, const struct cpumask *mask,
				bool force)
{
	struct hub_irq_data *hd = irq_data_get_irq_chip_data(d);

	if (!hd)
		return -EINVAL;

	if (irqd_is_started(d))
		disable_hub_irq(d);

	setup_hub_mask(hd, mask);

	if (irqd_is_started(d))
		enable_hub_irq(d);

	irq_data_update_effective_affinity(d, cpumask_of(hd->cpu));

	return 0;
}