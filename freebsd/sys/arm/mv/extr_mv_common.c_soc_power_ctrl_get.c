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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_PM_CTRL ; 
 int /*<<< orphan*/  CPU_PM_CTRL_NONE ; 
 int /*<<< orphan*/  read_cpu_ctrl (int /*<<< orphan*/ ) ; 

uint32_t
soc_power_ctrl_get(uint32_t mask)
{

#if SOC_MV_POWER_STAT_SUPPORTED
	if (mask != CPU_PM_CTRL_NONE)
		mask &= read_cpu_ctrl(CPU_PM_CTRL);

	return (mask);
#else
	return (mask);
#endif
}