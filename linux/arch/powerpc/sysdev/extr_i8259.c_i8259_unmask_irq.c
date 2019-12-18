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
struct irq_data {int irq; } ;

/* Variables and functions */
 int cached_21 ; 
 int cached_A1 ; 
 int /*<<< orphan*/  i8259_lock ; 
 int /*<<< orphan*/  i8259_set_irq_mask (int) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void i8259_unmask_irq(struct irq_data *d)
{
	unsigned long flags;

	pr_debug("i8259_unmask_irq(%d)\n", d->irq);

	raw_spin_lock_irqsave(&i8259_lock, flags);
	if (d->irq < 8)
		cached_21 &= ~(1 << d->irq);
	else
		cached_A1 &= ~(1 << (d->irq-8));
	i8259_set_irq_mask(d->irq);
	raw_spin_unlock_irqrestore(&i8259_lock, flags);
}