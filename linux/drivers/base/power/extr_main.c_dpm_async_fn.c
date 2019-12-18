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
struct TYPE_2__ {int /*<<< orphan*/  completion; } ;
struct device {TYPE_1__ power; } ;
typedef  int /*<<< orphan*/  async_func_t ;

/* Variables and functions */
 int /*<<< orphan*/  async_schedule (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  get_device (struct device*) ; 
 scalar_t__ is_async (struct device*) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool dpm_async_fn(struct device *dev, async_func_t func)
{
	reinit_completion(&dev->power.completion);

	if (is_async(dev)) {
		get_device(dev);
		async_schedule(func, dev);
		return true;
	}

	return false;
}