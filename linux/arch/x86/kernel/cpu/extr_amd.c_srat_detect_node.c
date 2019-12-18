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
struct cpuinfo_x86 {unsigned int apicid; int initial_apicid; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* fixup_cpu_id ) (struct cpuinfo_x86*,int) ;} ;

/* Variables and functions */
 int NUMA_NO_NODE ; 
 int* __apicid_to_node ; 
 int /*<<< orphan*/  cpu_llc_id ; 
 int nearby_node (unsigned int) ; 
 int /*<<< orphan*/  node_online (int) ; 
 int numa_cpu_node (int) ; 
 int /*<<< orphan*/  numa_set_node (int,int) ; 
 int per_cpu (int /*<<< orphan*/ ,int) ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  stub1 (struct cpuinfo_x86*,int) ; 
 TYPE_1__ x86_cpuinit ; 

__attribute__((used)) static void srat_detect_node(struct cpuinfo_x86 *c)
{
#ifdef CONFIG_NUMA
	int cpu = smp_processor_id();
	int node;
	unsigned apicid = c->apicid;

	node = numa_cpu_node(cpu);
	if (node == NUMA_NO_NODE)
		node = per_cpu(cpu_llc_id, cpu);

	/*
	 * On multi-fabric platform (e.g. Numascale NumaChip) a
	 * platform-specific handler needs to be called to fixup some
	 * IDs of the CPU.
	 */
	if (x86_cpuinit.fixup_cpu_id)
		x86_cpuinit.fixup_cpu_id(c, node);

	if (!node_online(node)) {
		/*
		 * Two possibilities here:
		 *
		 * - The CPU is missing memory and no node was created.  In
		 *   that case try picking one from a nearby CPU.
		 *
		 * - The APIC IDs differ from the HyperTransport node IDs
		 *   which the K8 northbridge parsing fills in.  Assume
		 *   they are all increased by a constant offset, but in
		 *   the same order as the HT nodeids.  If that doesn't
		 *   result in a usable node fall back to the path for the
		 *   previous case.
		 *
		 * This workaround operates directly on the mapping between
		 * APIC ID and NUMA node, assuming certain relationship
		 * between APIC ID, HT node ID and NUMA topology.  As going
		 * through CPU mapping may alter the outcome, directly
		 * access __apicid_to_node[].
		 */
		int ht_nodeid = c->initial_apicid;

		if (__apicid_to_node[ht_nodeid] != NUMA_NO_NODE)
			node = __apicid_to_node[ht_nodeid];
		/* Pick a nearby node */
		if (!node_online(node))
			node = nearby_node(apicid);
	}
	numa_set_node(cpu, node);
#endif
}