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
struct TYPE_2__ {int nr_nodes; int /*<<< orphan*/  nr_cpus; } ;

/* Variables and functions */
 int /*<<< orphan*/  N_POSSIBLE ; 
 TYPE_1__ loongson_sysconf ; 
 int /*<<< orphan*/  node_online_map ; 
 int /*<<< orphan*/  node_possible_map ; 
 int /*<<< orphan*/  node_set_online (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  node_set_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nodes_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  num_online_nodes () ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cpu_node_probe(void)
{
	int i;

	nodes_clear(node_possible_map);
	nodes_clear(node_online_map);
	for (i = 0; i < loongson_sysconf.nr_nodes; i++) {
		node_set_state(num_online_nodes(), N_POSSIBLE);
		node_set_online(num_online_nodes());
	}

	pr_info("NUMA: Discovered %d cpus on %d nodes\n",
		loongson_sysconf.nr_cpus, num_online_nodes());
}