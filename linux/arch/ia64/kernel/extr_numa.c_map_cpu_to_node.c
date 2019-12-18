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
 int* cpu_to_node_map ; 
 int /*<<< orphan*/  cpumask_set_cpu (int,int /*<<< orphan*/ *) ; 
 scalar_t__ cpumask_test_cpu (int,int /*<<< orphan*/ *) ; 
 int first_online_node ; 
 int /*<<< orphan*/  node_online (int) ; 
 int /*<<< orphan*/ * node_to_cpu_mask ; 

void map_cpu_to_node(int cpu, int nid)
{
	int oldnid;
	if (nid < 0) { /* just initialize by zero */
		cpu_to_node_map[cpu] = 0;
		return;
	}
	/* sanity check first */
	oldnid = cpu_to_node_map[cpu];
	if (cpumask_test_cpu(cpu, &node_to_cpu_mask[oldnid])) {
		return; /* nothing to do */
	}
	/* we don't have cpu-driven node hot add yet...
	   In usual case, node is created from SRAT at boot time. */
	if (!node_online(nid))
		nid = first_online_node;
	cpu_to_node_map[cpu] = nid;
	cpumask_set_cpu(cpu, &node_to_cpu_mask[nid]);
	return;
}