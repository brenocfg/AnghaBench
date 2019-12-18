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
struct irq_data {unsigned int irq; } ;
struct cpumask {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  titan_cached_irq_mask ; 
 int /*<<< orphan*/  titan_cpu_set_irq_affinity (unsigned int,struct cpumask const) ; 
 int /*<<< orphan*/  titan_irq_lock ; 
 int /*<<< orphan*/  titan_update_irq_hw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
titan_set_irq_affinity(struct irq_data *d, const struct cpumask *affinity,
		       bool force)
{ 
	unsigned int irq = d->irq;
	spin_lock(&titan_irq_lock);
	titan_cpu_set_irq_affinity(irq - 16, *affinity);
	titan_update_irq_hw(titan_cached_irq_mask);
	spin_unlock(&titan_irq_lock);

	return 0;
}