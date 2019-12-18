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
struct cpuinfo_level {int start_index; int end_index; int num_nodes; } ;

/* Variables and functions */
 size_t CPUINFO_LVL_CORE ; 
 int CPUINFO_LVL_MAX ; 
 size_t CPUINFO_LVL_NODE ; 
 size_t CPUINFO_LVL_PROC ; 
 size_t CPUINFO_LVL_ROOT ; 
 int /*<<< orphan*/  cpu_online (int) ; 
 int cpuinfo_id (int,size_t) ; 
 int num_possible_cpus () ; 

__attribute__((used)) static int enumerate_cpuinfo_nodes(struct cpuinfo_level *tree_level)
{
	int prev_id[CPUINFO_LVL_MAX];
	int i, n, num_nodes;

	for (i = CPUINFO_LVL_ROOT; i < CPUINFO_LVL_MAX; i++) {
		struct cpuinfo_level *lv = &tree_level[i];

		prev_id[i] = -1;
		lv->start_index = lv->end_index = lv->num_nodes = 0;
	}

	num_nodes = 1; /* Include the root node */

	for (i = 0; i < num_possible_cpus(); i++) {
		if (!cpu_online(i))
			continue;

		n = cpuinfo_id(i, CPUINFO_LVL_NODE);
		if (n > prev_id[CPUINFO_LVL_NODE]) {
			tree_level[CPUINFO_LVL_NODE].num_nodes++;
			prev_id[CPUINFO_LVL_NODE] = n;
			num_nodes++;
		}
		n = cpuinfo_id(i, CPUINFO_LVL_CORE);
		if (n > prev_id[CPUINFO_LVL_CORE]) {
			tree_level[CPUINFO_LVL_CORE].num_nodes++;
			prev_id[CPUINFO_LVL_CORE] = n;
			num_nodes++;
		}
		n = cpuinfo_id(i, CPUINFO_LVL_PROC);
		if (n > prev_id[CPUINFO_LVL_PROC]) {
			tree_level[CPUINFO_LVL_PROC].num_nodes++;
			prev_id[CPUINFO_LVL_PROC] = n;
			num_nodes++;
		}
	}

	tree_level[CPUINFO_LVL_ROOT].num_nodes = 1;

	n = tree_level[CPUINFO_LVL_NODE].num_nodes;
	tree_level[CPUINFO_LVL_NODE].start_index = 1;
	tree_level[CPUINFO_LVL_NODE].end_index   = n;

	n++;
	tree_level[CPUINFO_LVL_CORE].start_index = n;
	n += tree_level[CPUINFO_LVL_CORE].num_nodes;
	tree_level[CPUINFO_LVL_CORE].end_index   = n - 1;

	tree_level[CPUINFO_LVL_PROC].start_index = n;
	n += tree_level[CPUINFO_LVL_PROC].num_nodes;
	tree_level[CPUINFO_LVL_PROC].end_index   = n - 1;

	return num_nodes;
}