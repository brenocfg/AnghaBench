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
 int per_cpu (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sched_core_priority ; 

int arch_asym_cpu_priority(int cpu)
{
	return per_cpu(sched_core_priority, cpu);
}