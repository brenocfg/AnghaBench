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
struct irq_domain {int dummy; } ;
struct irq_data {int /*<<< orphan*/  irq; } ;
struct apic_chip_data {scalar_t__ has_reserved; scalar_t__ is_managed; int /*<<< orphan*/  can_reserve; } ;

/* Variables and functions */
 int activate_managed (struct irq_data*) ; 
 int activate_reserved (struct irq_data*) ; 
 struct apic_chip_data* apic_chip_data (struct irq_data*) ; 
 scalar_t__ irqd_is_managed_and_shutdown (struct irq_data*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  trace_vector_activate (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vector_assign_managed_shutdown (struct irq_data*) ; 
 int /*<<< orphan*/  vector_lock ; 

__attribute__((used)) static int x86_vector_activate(struct irq_domain *dom, struct irq_data *irqd,
			       bool reserve)
{
	struct apic_chip_data *apicd = apic_chip_data(irqd);
	unsigned long flags;
	int ret = 0;

	trace_vector_activate(irqd->irq, apicd->is_managed,
			      apicd->can_reserve, reserve);

	/* Nothing to do for fixed assigned vectors */
	if (!apicd->can_reserve && !apicd->is_managed)
		return 0;

	raw_spin_lock_irqsave(&vector_lock, flags);
	if (reserve || irqd_is_managed_and_shutdown(irqd))
		vector_assign_managed_shutdown(irqd);
	else if (apicd->is_managed)
		ret = activate_managed(irqd);
	else if (apicd->has_reserved)
		ret = activate_reserved(irqd);
	raw_spin_unlock_irqrestore(&vector_lock, flags);
	return ret;
}