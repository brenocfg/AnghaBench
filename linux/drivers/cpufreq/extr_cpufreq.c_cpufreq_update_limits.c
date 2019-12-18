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
struct TYPE_2__ {int /*<<< orphan*/  (* update_limits ) (unsigned int) ;} ;

/* Variables and functions */
 TYPE_1__* cpufreq_driver ; 
 int /*<<< orphan*/  cpufreq_update_policy (unsigned int) ; 
 int /*<<< orphan*/  stub1 (unsigned int) ; 

void cpufreq_update_limits(unsigned int cpu)
{
	if (cpufreq_driver->update_limits)
		cpufreq_driver->update_limits(cpu);
	else
		cpufreq_update_policy(cpu);
}