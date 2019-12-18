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
struct rapl_pmu {int dummy; } ;
struct TYPE_2__ {unsigned int maxdie; struct rapl_pmu** pmus; } ;

/* Variables and functions */
 TYPE_1__* rapl_pmus ; 
 unsigned int topology_logical_die_id (unsigned int) ; 

__attribute__((used)) static inline struct rapl_pmu *cpu_to_rapl_pmu(unsigned int cpu)
{
	unsigned int dieid = topology_logical_die_id(cpu);

	/*
	 * The unsigned check also catches the '-1' return value for non
	 * existent mappings in the topology map.
	 */
	return dieid < rapl_pmus->maxdie ? rapl_pmus->pmus[dieid] : NULL;
}