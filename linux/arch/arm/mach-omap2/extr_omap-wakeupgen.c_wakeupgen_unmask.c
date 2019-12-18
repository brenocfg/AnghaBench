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
struct irq_data {size_t hwirq; } ;

/* Variables and functions */
 int /*<<< orphan*/  _wakeupgen_set (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_chip_unmask_parent (struct irq_data*) ; 
 int /*<<< orphan*/ * irq_target_cpu ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wakeupgen_lock ; 

__attribute__((used)) static void wakeupgen_unmask(struct irq_data *d)
{
	unsigned long flags;

	raw_spin_lock_irqsave(&wakeupgen_lock, flags);
	_wakeupgen_set(d->hwirq, irq_target_cpu[d->hwirq]);
	raw_spin_unlock_irqrestore(&wakeupgen_lock, flags);
	irq_chip_unmask_parent(d);
}