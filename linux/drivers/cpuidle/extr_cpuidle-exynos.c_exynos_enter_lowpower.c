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
struct cpuidle_driver {int safe_state_index; } ;
struct cpuidle_device {scalar_t__ cpu; } ;

/* Variables and functions */
 int arm_cpuidle_simple_enter (struct cpuidle_device*,struct cpuidle_driver*,int) ; 
 int /*<<< orphan*/  exynos_enter_aftr () ; 
 int num_online_cpus () ; 

__attribute__((used)) static int exynos_enter_lowpower(struct cpuidle_device *dev,
				struct cpuidle_driver *drv,
				int index)
{
	int new_index = index;

	/* AFTR can only be entered when cores other than CPU0 are offline */
	if (num_online_cpus() > 1 || dev->cpu != 0)
		new_index = drv->safe_state_index;

	if (new_index == 0)
		return arm_cpuidle_simple_enter(dev, drv, new_index);

	exynos_enter_aftr();

	return new_index;
}