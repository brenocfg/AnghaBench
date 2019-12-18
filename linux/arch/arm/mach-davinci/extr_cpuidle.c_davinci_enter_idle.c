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
 int /*<<< orphan*/  cpu_do_idle () ; 
 int /*<<< orphan*/  davinci_save_ddr_power (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ddr2_pdown ; 

__attribute__((used)) static int davinci_enter_idle(struct cpuidle_device *dev,
			      struct cpuidle_driver *drv, int index)
{
	davinci_save_ddr_power(1, ddr2_pdown);
	cpu_do_idle();
	davinci_save_ddr_power(0, ddr2_pdown);

	return index;
}