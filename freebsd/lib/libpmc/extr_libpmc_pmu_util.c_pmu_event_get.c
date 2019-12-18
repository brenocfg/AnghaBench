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
struct pmu_events_map {struct pmu_event* table; } ;
struct pmu_event {int /*<<< orphan*/ * name; scalar_t__ event; scalar_t__ desc; } ;

/* Variables and functions */
 struct pmu_events_map* pmu_events_map_get (char const*) ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static const struct pmu_event *
pmu_event_get(const char *cpuid, const char *event_name, int *idx)
{
	const struct pmu_events_map *pme;
	const struct pmu_event *pe;
	int i;

	if ((pme = pmu_events_map_get(cpuid)) == NULL)
		return (NULL);
	for (i = 0, pe = pme->table; pe->name || pe->desc || pe->event; pe++, i++) {
		if (pe->name == NULL)
			continue;
		if (strcasecmp(pe->name, event_name) == 0) {
			if (idx)
				*idx = i;
			return (pe);
		}
	}
	return (NULL);
}