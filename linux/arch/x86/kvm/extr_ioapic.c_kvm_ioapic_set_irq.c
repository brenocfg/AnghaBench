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
struct kvm_ioapic {int /*<<< orphan*/  lock; int /*<<< orphan*/ * irq_states; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int IOAPIC_NUM_PINS ; 
 int __kvm_irq_line_state (int /*<<< orphan*/ *,int,int) ; 
 int ioapic_set_irq (struct kvm_ioapic*,int,int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int kvm_ioapic_set_irq(struct kvm_ioapic *ioapic, int irq, int irq_source_id,
		       int level, bool line_status)
{
	int ret, irq_level;

	BUG_ON(irq < 0 || irq >= IOAPIC_NUM_PINS);

	spin_lock(&ioapic->lock);
	irq_level = __kvm_irq_line_state(&ioapic->irq_states[irq],
					 irq_source_id, level);
	ret = ioapic_set_irq(ioapic, irq, irq_level, line_status);

	spin_unlock(&ioapic->lock);

	return ret;
}