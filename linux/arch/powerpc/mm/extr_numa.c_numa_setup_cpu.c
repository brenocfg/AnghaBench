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
struct device_node {int dummy; } ;

/* Variables and functions */
 int NUMA_NO_NODE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ cpu_present (unsigned long) ; 
 int first_online_node ; 
 int /*<<< orphan*/  map_cpu_to_node (unsigned long,int) ; 
 int /*<<< orphan*/  node_possible (int) ; 
 int* numa_cpu_lookup_table ; 
 struct device_node* of_get_cpu_node (unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int of_node_to_nid_single (struct device_node*) ; 

__attribute__((used)) static int numa_setup_cpu(unsigned long lcpu)
{
	int nid = NUMA_NO_NODE;
	struct device_node *cpu;

	/*
	 * If a valid cpu-to-node mapping is already available, use it
	 * directly instead of querying the firmware, since it represents
	 * the most recent mapping notified to us by the platform (eg: VPHN).
	 */
	if ((nid = numa_cpu_lookup_table[lcpu]) >= 0) {
		map_cpu_to_node(lcpu, nid);
		return nid;
	}

	cpu = of_get_cpu_node(lcpu, NULL);

	if (!cpu) {
		WARN_ON(1);
		if (cpu_present(lcpu))
			goto out_present;
		else
			goto out;
	}

	nid = of_node_to_nid_single(cpu);

out_present:
	if (nid < 0 || !node_possible(nid))
		nid = first_online_node;

	map_cpu_to_node(lcpu, nid);
	of_node_put(cpu);
out:
	return nid;
}