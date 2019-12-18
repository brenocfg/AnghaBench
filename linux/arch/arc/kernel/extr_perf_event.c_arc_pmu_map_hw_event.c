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
struct TYPE_2__ {int* ev_hw_idx; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 TYPE_1__* arc_pmu ; 
 int /*<<< orphan*/  arc_pmu_ev_hw_map ; 
 scalar_t__ event_in_hw_event_map (int,char*) ; 
 int /*<<< orphan*/  pr_debug (char*,int,char*,int) ; 

__attribute__((used)) static void arc_pmu_map_hw_event(int j, char *str)
{
	int i;

	/* See if HW condition has been mapped to a perf event_id */
	for (i = 0; i < ARRAY_SIZE(arc_pmu_ev_hw_map); i++) {
		if (event_in_hw_event_map(i, str)) {
			pr_debug("mapping perf event %2d to h/w event \'%8s\' (idx %d)\n",
				 i, str, j);
			arc_pmu->ev_hw_idx[i] = j;
		}
	}
}