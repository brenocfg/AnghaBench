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
struct cpuidle_driver {int dummy; } ;
struct cpuidle_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WAIT_CLOCKED ; 
 int /*<<< orphan*/  WAIT_UNCLOCKED ; 
 int /*<<< orphan*/  cpu_cluster_pm_enter () ; 
 int /*<<< orphan*/  cpu_cluster_pm_exit () ; 
 int /*<<< orphan*/  cpu_do_idle () ; 
 int /*<<< orphan*/  cpu_pm_enter () ; 
 int /*<<< orphan*/  cpu_pm_exit () ; 
 int /*<<< orphan*/  cpu_suspend (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx6_enable_rbc (int) ; 
 int /*<<< orphan*/  imx6_set_lpm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx6sx_idle_finish ; 
 int /*<<< orphan*/  imx_gpc_set_arm_power_in_lpm (int) ; 
 int /*<<< orphan*/  imx_set_cpu_jump (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v7_cpu_resume ; 

__attribute__((used)) static int imx6sx_enter_wait(struct cpuidle_device *dev,
			    struct cpuidle_driver *drv, int index)
{
	imx6_set_lpm(WAIT_UNCLOCKED);

	switch (index) {
	case 1:
		cpu_do_idle();
		break;
	case 2:
		imx6_enable_rbc(true);
		imx_gpc_set_arm_power_in_lpm(true);
		imx_set_cpu_jump(0, v7_cpu_resume);
		/* Need to notify there is a cpu pm operation. */
		cpu_pm_enter();
		cpu_cluster_pm_enter();

		cpu_suspend(0, imx6sx_idle_finish);

		cpu_cluster_pm_exit();
		cpu_pm_exit();
		imx_gpc_set_arm_power_in_lpm(false);
		imx6_enable_rbc(false);
		break;
	default:
		break;
	}

	imx6_set_lpm(WAIT_CLOCKED);

	return index;
}