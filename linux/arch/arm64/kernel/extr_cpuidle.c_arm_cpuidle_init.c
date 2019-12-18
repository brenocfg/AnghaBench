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
struct TYPE_2__ {int (* cpu_init_idle ) (unsigned int) ;scalar_t__ cpu_suspend; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 TYPE_1__** cpu_ops ; 
 int stub1 (unsigned int) ; 

int arm_cpuidle_init(unsigned int cpu)
{
	int ret = -EOPNOTSUPP;

	if (cpu_ops[cpu] && cpu_ops[cpu]->cpu_suspend &&
			cpu_ops[cpu]->cpu_init_idle)
		ret = cpu_ops[cpu]->cpu_init_idle(cpu);

	return ret;
}