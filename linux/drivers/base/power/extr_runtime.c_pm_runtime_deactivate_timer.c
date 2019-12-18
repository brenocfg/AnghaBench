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
struct TYPE_2__ {scalar_t__ timer_expires; int /*<<< orphan*/  suspend_timer; } ;
struct device {TYPE_1__ power; } ;

/* Variables and functions */
 int /*<<< orphan*/  hrtimer_try_to_cancel (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pm_runtime_deactivate_timer(struct device *dev)
{
	if (dev->power.timer_expires > 0) {
		hrtimer_try_to_cancel(&dev->power.suspend_timer);
		dev->power.timer_expires = 0;
	}
}