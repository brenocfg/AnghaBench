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
struct pmu_event {char* name; char* desc; char* event; char* long_desc; char* topic; char* pmu; char* unit; char* perpkg; char* metric_expr; char* metric_name; char* metric_group; } ;

/* Variables and functions */
 struct pmu_events_map* pmu_events_map_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/ * strcasestr (char*,char const*) ; 

void
pmc_pmu_print_counter_full(const char *ev)
{
	const struct pmu_events_map *pme;
	const struct pmu_event *pe;

	if ((pme = pmu_events_map_get(NULL)) == NULL)
		return;
	for (pe = pme->table; pe->name || pe->desc || pe->event; pe++) {
		if (pe->name == NULL)
			continue;
		if (strcasestr(pe->name, ev) == NULL)
			continue;
		printf("name: %s\n", pe->name);
		if (pe->long_desc != NULL)
			printf("desc: %s\n", pe->long_desc);
		else if (pe->desc != NULL)
			printf("desc: %s\n", pe->desc);
		if (pe->event != NULL)
			printf("event: %s\n", pe->event);
		if (pe->topic != NULL)
			printf("topic: %s\n", pe->topic);
		if (pe->pmu != NULL)
			printf("pmu: %s\n", pe->pmu);
		if (pe->unit != NULL)
			printf("unit: %s\n", pe->unit);
		if (pe->perpkg != NULL)
			printf("perpkg: %s\n", pe->perpkg);
		if (pe->metric_expr != NULL)
			printf("metric_expr: %s\n", pe->metric_expr);
		if (pe->metric_name != NULL)
			printf("metric_name: %s\n", pe->metric_name);
		if (pe->metric_group != NULL)
			printf("metric_group: %s\n", pe->metric_group);
	}
}