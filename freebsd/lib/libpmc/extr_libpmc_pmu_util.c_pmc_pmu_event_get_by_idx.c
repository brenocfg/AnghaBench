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
struct pmu_events_map {TYPE_1__* table; } ;
struct TYPE_2__ {char const* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (char const*) ; 
 struct pmu_events_map* pmu_events_map_get (char const*) ; 

const char *
pmc_pmu_event_get_by_idx(const char *cpuid, int idx)
{
	const struct pmu_events_map *pme;

	if ((pme = pmu_events_map_get(cpuid)) == NULL)
		return (NULL);
	assert(pme->table[idx].name);
	return (pme->table[idx].name);
}