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
 char* pmu_alias_get (char const*) ; 
 int /*<<< orphan*/ * pmu_event_get (char const*,char const*,int*) ; 

int
pmc_pmu_idx_get_by_event(const char *cpuid, const char *event)
{
	int idx;
	const char *realname;

	realname = pmu_alias_get(event);
	if (pmu_event_get(cpuid, realname, &idx) == NULL)
		return (-1);
	return (idx);
}