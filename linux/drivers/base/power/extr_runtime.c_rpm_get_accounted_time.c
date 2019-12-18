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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  active_time; int /*<<< orphan*/  suspended_time; } ;
struct device {TYPE_1__ power; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  update_pm_runtime_accounting (struct device*) ; 

__attribute__((used)) static u64 rpm_get_accounted_time(struct device *dev, bool suspended)
{
	u64 time;
	unsigned long flags;

	spin_lock_irqsave(&dev->power.lock, flags);

	update_pm_runtime_accounting(dev);
	time = suspended ? dev->power.suspended_time : dev->power.active_time;

	spin_unlock_irqrestore(&dev->power.lock, flags);

	return time;
}