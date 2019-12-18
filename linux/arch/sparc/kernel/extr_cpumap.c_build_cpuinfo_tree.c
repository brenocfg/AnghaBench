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
typedef  int /*<<< orphan*/  tmp_level ;
struct cpuinfo_tree {int total_nodes; struct cpuinfo_node* nodes; TYPE_1__* level; } ;
struct cpuinfo_node {int id; int level; int num_cpus; int parent_index; int child_start; int child_end; int rover; } ;
struct cpuinfo_level {int dummy; } ;
struct TYPE_2__ {int start_index; int end_index; } ;

/* Variables and functions */
 int CPUINFO_LVL_MAX ; 
 int CPUINFO_LVL_PROC ; 
 int CPUINFO_LVL_ROOT ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ cpu_online (int) ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 int cpuinfo_id (int,int) ; 
 int cpumask_first (int /*<<< orphan*/ ) ; 
 int enumerate_cpuinfo_nodes (struct cpuinfo_level*) ; 
 int /*<<< orphan*/  kfree (struct cpuinfo_tree*) ; 
 struct cpuinfo_tree* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__**,struct cpuinfo_level*,int) ; 
 int /*<<< orphan*/  nodes ; 
 int num_possible_cpus () ; 
 int /*<<< orphan*/  struct_size (struct cpuinfo_tree*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct cpuinfo_tree *build_cpuinfo_tree(void)
{
	struct cpuinfo_tree *new_tree;
	struct cpuinfo_node *node;
	struct cpuinfo_level tmp_level[CPUINFO_LVL_MAX];
	int num_cpus[CPUINFO_LVL_MAX];
	int level_rover[CPUINFO_LVL_MAX];
	int prev_id[CPUINFO_LVL_MAX];
	int n, id, cpu, prev_cpu, last_cpu, level;

	n = enumerate_cpuinfo_nodes(tmp_level);

	new_tree = kzalloc(struct_size(new_tree, nodes, n), GFP_ATOMIC);
	if (!new_tree)
		return NULL;

	new_tree->total_nodes = n;
	memcpy(&new_tree->level, tmp_level, sizeof(tmp_level));

	prev_cpu = cpu = cpumask_first(cpu_online_mask);

	/* Initialize all levels in the tree with the first CPU */
	for (level = CPUINFO_LVL_PROC; level >= CPUINFO_LVL_ROOT; level--) {
		n = new_tree->level[level].start_index;

		level_rover[level] = n;
		node = &new_tree->nodes[n];

		id = cpuinfo_id(cpu, level);
		if (unlikely(id < 0)) {
			kfree(new_tree);
			return NULL;
		}
		node->id = id;
		node->level = level;
		node->num_cpus = 1;

		node->parent_index = (level > CPUINFO_LVL_ROOT)
		    ? new_tree->level[level - 1].start_index : -1;

		node->child_start = node->child_end = node->rover =
		    (level == CPUINFO_LVL_PROC)
		    ? cpu : new_tree->level[level + 1].start_index;

		prev_id[level] = node->id;
		num_cpus[level] = 1;
	}

	for (last_cpu = (num_possible_cpus() - 1); last_cpu >= 0; last_cpu--) {
		if (cpu_online(last_cpu))
			break;
	}

	while (++cpu <= last_cpu) {
		if (!cpu_online(cpu))
			continue;

		for (level = CPUINFO_LVL_PROC; level >= CPUINFO_LVL_ROOT;
		     level--) {
			id = cpuinfo_id(cpu, level);
			if (unlikely(id < 0)) {
				kfree(new_tree);
				return NULL;
			}

			if ((id != prev_id[level]) || (cpu == last_cpu)) {
				prev_id[level] = id;
				node = &new_tree->nodes[level_rover[level]];
				node->num_cpus = num_cpus[level];
				num_cpus[level] = 1;

				if (cpu == last_cpu)
					node->num_cpus++;

				/* Connect tree node to parent */
				if (level == CPUINFO_LVL_ROOT)
					node->parent_index = -1;
				else
					node->parent_index =
					    level_rover[level - 1];

				if (level == CPUINFO_LVL_PROC) {
					node->child_end =
					    (cpu == last_cpu) ? cpu : prev_cpu;
				} else {
					node->child_end =
					    level_rover[level + 1] - 1;
				}

				/* Initialize the next node in the same level */
				n = ++level_rover[level];
				if (n <= new_tree->level[level].end_index) {
					node = &new_tree->nodes[n];
					node->id = id;
					node->level = level;

					/* Connect node to child */
					node->child_start = node->child_end =
					node->rover =
					    (level == CPUINFO_LVL_PROC)
					    ? cpu : level_rover[level + 1];
				}
			} else
				num_cpus[level]++;
		}
		prev_cpu = cpu;
	}

	return new_tree;
}