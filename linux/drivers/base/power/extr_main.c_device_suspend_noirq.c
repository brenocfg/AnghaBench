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
struct device {int dummy; } ;

/* Variables and functions */
 int __device_suspend_noirq (struct device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  async_suspend_noirq ; 
 scalar_t__ dpm_async_fn (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_transition ; 

__attribute__((used)) static int device_suspend_noirq(struct device *dev)
{
	if (dpm_async_fn(dev, async_suspend_noirq))
		return 0;

	return __device_suspend_noirq(dev, pm_transition, false);
}