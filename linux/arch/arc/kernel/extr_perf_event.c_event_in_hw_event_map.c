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
 int /*<<< orphan*/ * arc_pmu_ev_hw_map ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool event_in_hw_event_map(int i, char *name)
{
	if (!arc_pmu_ev_hw_map[i])
		return false;

	if (!strlen(arc_pmu_ev_hw_map[i]))
		return false;

	if (strcmp(arc_pmu_ev_hw_map[i], name))
		return false;

	return true;
}