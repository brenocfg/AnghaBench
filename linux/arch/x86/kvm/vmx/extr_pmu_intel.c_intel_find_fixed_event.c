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
struct TYPE_2__ {int event_type; } ;

/* Variables and functions */
 int ARRAY_SIZE (size_t*) ; 
 int PERF_COUNT_HW_MAX ; 
 size_t* fixed_pmc_events ; 
 TYPE_1__* intel_arch_events ; 

__attribute__((used)) static unsigned intel_find_fixed_event(int idx)
{
	if (idx >= ARRAY_SIZE(fixed_pmc_events))
		return PERF_COUNT_HW_MAX;

	return intel_arch_events[fixed_pmc_events[idx]].event_type;
}