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
struct apic_chip_data {int has_reserved; int can_reserve; } ;

/* Variables and functions */
 struct apic_chip_data* apic_chip_data (struct irq_data*) ; 
 int assign_irq_vector_any_locked (struct irq_data*) ; 
 int /*<<< orphan*/  cpumask_subset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_data_get_affinity_mask (struct irq_data*) ; 
 int /*<<< orphan*/  irq_data_get_effective_affinity_mask (struct irq_data*) ; 
 int /*<<< orphan*/  irqd_can_reserve (struct irq_data*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int activate_reserved(struct irq_data *irqd)
{
	struct apic_chip_data *apicd = apic_chip_data(irqd);
	int ret;

	ret = assign_irq_vector_any_locked(irqd);
	if (!ret) {
		apicd->has_reserved = false;
		/*
		 * Core might have disabled reservation mode after
		 * allocating the irq descriptor. Ideally this should
		 * happen before allocation time, but that would require
		 * completely convoluted ways of transporting that
		 * information.
		 */
		if (!irqd_can_reserve(irqd))
			apicd->can_reserve = false;
	}

	/*
	 * Check to ensure that the effective affinity mask is a subset
	 * the user supplied affinity mask, and warn the user if it is not
	 */
	if (!cpumask_subset(irq_data_get_effective_affinity_mask(irqd),
			    irq_data_get_affinity_mask(irqd))) {
		pr_warn("irq %u: Affinity broken due to vector space exhaustion.\n",
			irqd->irq);
	}

	return ret;
}