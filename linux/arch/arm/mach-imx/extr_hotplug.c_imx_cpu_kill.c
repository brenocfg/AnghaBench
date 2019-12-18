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
 int /*<<< orphan*/  imx_enable_cpu (unsigned int,int) ; 
 scalar_t__ imx_get_cpu_arg (unsigned int) ; 
 int /*<<< orphan*/  imx_set_cpu_arg (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

int imx_cpu_kill(unsigned int cpu)
{
	unsigned long timeout = jiffies + msecs_to_jiffies(50);

	while (imx_get_cpu_arg(cpu) == 0)
		if (time_after(jiffies, timeout))
			return 0;
	imx_enable_cpu(cpu, false);
	imx_set_cpu_arg(cpu, 0);
	return 1;
}