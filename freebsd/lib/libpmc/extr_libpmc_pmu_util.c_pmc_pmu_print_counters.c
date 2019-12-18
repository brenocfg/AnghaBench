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
struct pmu_event_desc {int dummy; } ;
struct pmu_event {char* name; scalar_t__ event; scalar_t__ desc; } ;

/* Variables and functions */
 char* getenv (char*) ; 
 struct pmu_events_map* pmu_events_map_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmu_parse_event (struct pmu_event_desc*,scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/ * strcasestr (char*,char const*) ; 
 scalar_t__ strcmp (char*,char*) ; 

void
pmc_pmu_print_counters(const char *event_name)
{
	const struct pmu_events_map *pme;
	const struct pmu_event *pe;
	struct pmu_event_desc ped;
	char *debug;
	int do_debug;

	debug = getenv("PMUDEBUG");
	do_debug = 0;

	if (debug != NULL && strcmp(debug, "true") == 0)
		do_debug = 1;
	if ((pme = pmu_events_map_get(NULL)) == NULL)
		return;
	for (pe = pme->table; pe->name || pe->desc || pe->event; pe++) {
		if (pe->name == NULL)
			continue;
		if (event_name != NULL && strcasestr(pe->name, event_name) == NULL)
			continue;
		printf("\t%s\n", pe->name);
		if (do_debug)
			pmu_parse_event(&ped, pe->event);
	}
}