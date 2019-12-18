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
struct TYPE_2__ {int wakeup_path; int /*<<< orphan*/  lock; int /*<<< orphan*/  ignore_children; } ;
struct device {TYPE_1__ power; struct device* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dpm_propagate_wakeup_to_parent(struct device *dev)
{
	struct device *parent = dev->parent;

	if (!parent)
		return;

	spin_lock_irq(&parent->power.lock);

	if (dev->power.wakeup_path && !parent->power.ignore_children)
		parent->power.wakeup_path = true;

	spin_unlock_irq(&parent->power.lock);
}