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
 int /*<<< orphan*/  cpu_do_idle () ; 
 int /*<<< orphan*/  imx6_set_lpm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx6sl_set_wait_clk (int) ; 

__attribute__((used)) static int imx6sl_enter_wait(struct cpuidle_device *dev,
			    struct cpuidle_driver *drv, int index)
{
	imx6_set_lpm(WAIT_UNCLOCKED);
	/*
	 * Software workaround for ERR005311, see function
	 * description for details.
	 */
	imx6sl_set_wait_clk(true);
	cpu_do_idle();
	imx6sl_set_wait_clk(false);
	imx6_set_lpm(WAIT_CLOCKED);

	return index;
}