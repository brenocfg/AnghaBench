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
 int /*<<< orphan*/  ULP_PM_RUN ; 
 int /*<<< orphan*/  ULP_PM_STOP ; 
 int /*<<< orphan*/  ULP_PM_WAIT ; 
 int /*<<< orphan*/  cpu_do_idle () ; 
 int /*<<< orphan*/  imx7ulp_set_lpm (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int imx7ulp_enter_wait(struct cpuidle_device *dev,
			    struct cpuidle_driver *drv, int index)
{
	if (index == 1)
		imx7ulp_set_lpm(ULP_PM_WAIT);
	else
		imx7ulp_set_lpm(ULP_PM_STOP);

	cpu_do_idle();

	imx7ulp_set_lpm(ULP_PM_RUN);

	return index;
}