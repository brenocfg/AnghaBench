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
 int /*<<< orphan*/  WARN (int,char*,int,int) ; 
 int cpu_first_thread_sibling (int) ; 
 scalar_t__ cpu_is_offline (int) ; 
 int cpu_to_node (int) ; 
 int threads_per_core ; 

__attribute__((used)) static void verify_cpu_node_mapping(int cpu, int node)
{
	int base, sibling, i;

	/* Verify that all the threads in the core belong to the same node */
	base = cpu_first_thread_sibling(cpu);

	for (i = 0; i < threads_per_core; i++) {
		sibling = base + i;

		if (sibling == cpu || cpu_is_offline(sibling))
			continue;

		if (cpu_to_node(sibling) != node) {
			WARN(1, "CPU thread siblings %d and %d don't belong"
				" to the same node!\n", cpu, sibling);
			break;
		}
	}
}