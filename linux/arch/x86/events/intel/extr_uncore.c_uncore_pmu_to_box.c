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
struct intel_uncore_pmu {struct intel_uncore_box** boxes; } ;
struct intel_uncore_box {int dummy; } ;

/* Variables and functions */
 unsigned int max_dies ; 
 unsigned int topology_logical_die_id (int) ; 

struct intel_uncore_box *uncore_pmu_to_box(struct intel_uncore_pmu *pmu, int cpu)
{
	unsigned int dieid = topology_logical_die_id(cpu);

	/*
	 * The unsigned check also catches the '-1' return value for non
	 * existent mappings in the topology map.
	 */
	return dieid < max_dies ? pmu->boxes[dieid] : NULL;
}