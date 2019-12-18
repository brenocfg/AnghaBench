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
struct cpuidle_driver {TYPE_1__* states; } ;
struct cpuidle_device {int dummy; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int MVEBU_V7_FLAG_DEEP_IDLE ; 
 int /*<<< orphan*/  cpu_pm_enter () ; 
 int /*<<< orphan*/  cpu_pm_exit () ; 
 int mvebu_v7_cpu_suspend (int) ; 

__attribute__((used)) static int mvebu_v7_enter_idle(struct cpuidle_device *dev,
				struct cpuidle_driver *drv,
				int index)
{
	int ret;
	bool deepidle = false;
	cpu_pm_enter();

	if (drv->states[index].flags & MVEBU_V7_FLAG_DEEP_IDLE)
		deepidle = true;

	ret = mvebu_v7_cpu_suspend(deepidle);
	cpu_pm_exit();

	if (ret)
		return ret;

	return index;
}