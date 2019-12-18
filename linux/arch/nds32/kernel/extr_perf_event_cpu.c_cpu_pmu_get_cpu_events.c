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
struct pmu_hw_events {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_hw_events ; 
 struct pmu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct pmu_hw_events *cpu_pmu_get_cpu_events(void)
{
	return this_cpu_ptr(&cpu_hw_events);
}