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
 int /*<<< orphan*/  WARN_ON (int) ; 
 int* cpu_to_node_map ; 
 int /*<<< orphan*/  cpumask_clear_cpu (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_test_cpu (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * node_to_cpu_mask ; 

void unmap_cpu_from_node(int cpu, int nid)
{
	WARN_ON(!cpumask_test_cpu(cpu, &node_to_cpu_mask[nid]));
	WARN_ON(cpu_to_node_map[cpu] != nid);
	cpu_to_node_map[cpu] = 0;
	cpumask_clear_cpu(cpu, &node_to_cpu_mask[nid]);
}