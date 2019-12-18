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

/* Variables and functions */
 int /*<<< orphan*/  SCU_PM_NORMAL ; 
 int /*<<< orphan*/  SCU_PM_POWEROFF ; 
 int /*<<< orphan*/  am43xx_check_off_mode_enable () ; 
 int /*<<< orphan*/  amx3_post_suspend_common () ; 
 int /*<<< orphan*/  amx3_pre_suspend_common () ; 
 int cpu_suspend (unsigned long,int (*) (unsigned long)) ; 
 int /*<<< orphan*/  scu_base ; 
 int /*<<< orphan*/  scu_power_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int am43xx_suspend(unsigned int state, int (*fn)(unsigned long),
			  unsigned long args)
{
	int ret = 0;

	amx3_pre_suspend_common();
	scu_power_mode(scu_base, SCU_PM_POWEROFF);
	ret = cpu_suspend(args, fn);
	scu_power_mode(scu_base, SCU_PM_NORMAL);

	if (!am43xx_check_off_mode_enable())
		amx3_post_suspend_common();

	return ret;
}