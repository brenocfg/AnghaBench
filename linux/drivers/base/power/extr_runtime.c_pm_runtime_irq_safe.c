#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int irq_safe; int /*<<< orphan*/  lock; } ;
struct device {TYPE_1__ power; scalar_t__ parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  pm_runtime_get_sync (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void pm_runtime_irq_safe(struct device *dev)
{
	if (dev->parent)
		pm_runtime_get_sync(dev->parent);
	spin_lock_irq(&dev->power.lock);
	dev->power.irq_safe = 1;
	spin_unlock_irq(&dev->power.lock);
}