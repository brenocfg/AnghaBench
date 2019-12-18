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
struct apic_chip_data {int can_reserve; scalar_t__ cpu; int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISA_IRQ_VECTOR (unsigned int) ; 
 int /*<<< orphan*/  apic_update_irq_cfg (struct irq_data*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  clear_irq_vector (struct irq_data*) ; 
 scalar_t__ irqd_is_activated (struct irq_data*) ; 
 int /*<<< orphan*/  irqd_set_can_reserve (struct irq_data*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  trace_vector_setup (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vector_lock ; 

__attribute__((used)) static bool vector_configure_legacy(unsigned int virq, struct irq_data *irqd,
				    struct apic_chip_data *apicd)
{
	unsigned long flags;
	bool realloc = false;

	apicd->vector = ISA_IRQ_VECTOR(virq);
	apicd->cpu = 0;

	raw_spin_lock_irqsave(&vector_lock, flags);
	/*
	 * If the interrupt is activated, then it must stay at this vector
	 * position. That's usually the timer interrupt (0).
	 */
	if (irqd_is_activated(irqd)) {
		trace_vector_setup(virq, true, 0);
		apic_update_irq_cfg(irqd, apicd->vector, apicd->cpu);
	} else {
		/* Release the vector */
		apicd->can_reserve = true;
		irqd_set_can_reserve(irqd);
		clear_irq_vector(irqd);
		realloc = true;
	}
	raw_spin_unlock_irqrestore(&vector_lock, flags);
	return realloc;
}