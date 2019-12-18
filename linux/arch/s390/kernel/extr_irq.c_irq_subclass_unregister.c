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
typedef  enum irq_subclass { ____Placeholder_irq_subclass } irq_subclass ;

/* Variables and functions */
 int /*<<< orphan*/  ctl_clear_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  irq_subclass_lock ; 
 int /*<<< orphan*/ * irq_subclass_refcount ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void irq_subclass_unregister(enum irq_subclass subclass)
{
	spin_lock(&irq_subclass_lock);
	irq_subclass_refcount[subclass]--;
	if (!irq_subclass_refcount[subclass])
		ctl_clear_bit(0, subclass);
	spin_unlock(&irq_subclass_lock);
}