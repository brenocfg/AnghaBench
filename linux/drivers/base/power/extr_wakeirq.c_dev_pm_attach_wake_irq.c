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
struct wake_irq {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; struct wake_irq* wakeirq; } ;
struct device {TYPE_1__ power; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 scalar_t__ dev_WARN_ONCE (struct device*,struct wake_irq*,char*) ; 
 int /*<<< orphan*/  device_wakeup_attach_irq (struct device*,struct wake_irq*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int dev_pm_attach_wake_irq(struct device *dev, int irq,
				  struct wake_irq *wirq)
{
	unsigned long flags;

	if (!dev || !wirq)
		return -EINVAL;

	spin_lock_irqsave(&dev->power.lock, flags);
	if (dev_WARN_ONCE(dev, dev->power.wakeirq,
			  "wake irq already initialized\n")) {
		spin_unlock_irqrestore(&dev->power.lock, flags);
		return -EEXIST;
	}

	dev->power.wakeirq = wirq;
	device_wakeup_attach_irq(dev, wirq);

	spin_unlock_irqrestore(&dev->power.lock, flags);
	return 0;
}