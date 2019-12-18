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
struct topo_node {scalar_t__ type; int cpu_count; scalar_t__ subtype; int /*<<< orphan*/  cpuset; } ;
struct cpu_group {int cg_count; scalar_t__ cg_level; int cg_children; struct cpu_group* cg_child; struct cpu_group* cg_parent; int /*<<< orphan*/  cg_flags; int /*<<< orphan*/  cg_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_FLAG_SMT ; 
 scalar_t__ CG_SHARE_NONE ; 
 scalar_t__ CPU_CMP (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ TOPO_TYPE_CACHE ; 
 scalar_t__ TOPO_TYPE_CORE ; 
 scalar_t__ TOPO_TYPE_GROUP ; 
 scalar_t__ TOPO_TYPE_SYSTEM ; 
 struct cpu_group* smp_topo_alloc (int) ; 
 struct topo_node* topo_next_node (struct topo_node*,struct topo_node*) ; 
 struct topo_node* topo_next_nonchild_node (struct topo_node*,struct topo_node*) ; 

__attribute__((used)) static void
x86topo_add_sched_group(struct topo_node *root, struct cpu_group *cg_root)
{
	struct topo_node *node;
	int nchildren;
	int ncores;
	int i;

	KASSERT(root->type == TOPO_TYPE_SYSTEM || root->type == TOPO_TYPE_CACHE ||
	    root->type == TOPO_TYPE_GROUP,
	    ("x86topo_add_sched_group: bad type: %u", root->type));
	CPU_COPY(&root->cpuset, &cg_root->cg_mask);
	cg_root->cg_count = root->cpu_count;
	if (root->type == TOPO_TYPE_SYSTEM)
		cg_root->cg_level = CG_SHARE_NONE;
	else
		cg_root->cg_level = root->subtype;

	/*
	 * Check how many core nodes we have under the given root node.
	 * If we have multiple logical processors, but not multiple
	 * cores, then those processors must be hardware threads.
	 */
	ncores = 0;
	node = root;
	while (node != NULL) {
		if (node->type != TOPO_TYPE_CORE) {
			node = topo_next_node(root, node);
			continue;
		}

		ncores++;
		node = topo_next_nonchild_node(root, node);
	}

	if (cg_root->cg_level != CG_SHARE_NONE &&
	    root->cpu_count > 1 && ncores < 2)
		cg_root->cg_flags = CG_FLAG_SMT;

	/*
	 * Find out how many cache nodes we have under the given root node.
	 * We ignore cache nodes that cover all the same processors as the
	 * root node.  Also, we do not descend below found cache nodes.
	 * That is, we count top-level "non-redundant" caches under the root
	 * node.
	 */
	nchildren = 0;
	node = root;
	while (node != NULL) {
		if ((node->type != TOPO_TYPE_GROUP &&
		    node->type != TOPO_TYPE_CACHE) ||
		    (root->type != TOPO_TYPE_SYSTEM &&
		    CPU_CMP(&node->cpuset, &root->cpuset) == 0)) {
			node = topo_next_node(root, node);
			continue;
		}
		nchildren++;
		node = topo_next_nonchild_node(root, node);
	}

	cg_root->cg_child = smp_topo_alloc(nchildren);
	cg_root->cg_children = nchildren;

	/*
	 * Now find again the same cache nodes as above and recursively
	 * build scheduling topologies for them.
	 */
	node = root;
	i = 0;
	while (node != NULL) {
		if ((node->type != TOPO_TYPE_GROUP &&
		    node->type != TOPO_TYPE_CACHE) ||
		    (root->type != TOPO_TYPE_SYSTEM &&
		    CPU_CMP(&node->cpuset, &root->cpuset) == 0)) {
			node = topo_next_node(root, node);
			continue;
		}
		cg_root->cg_child[i].cg_parent = cg_root;
		x86topo_add_sched_group(node, &cg_root->cg_child[i]);
		i++;
		node = topo_next_nonchild_node(root, node);
	}
}