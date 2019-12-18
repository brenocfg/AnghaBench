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
struct addrtree {scalar_t__ max_node_count; scalar_t__ node_count; struct addrnode* first; } ;
struct addrnode {TYPE_1__* parent_edge; int /*<<< orphan*/  elem; int /*<<< orphan*/ ** edge; } ;
struct TYPE_2__ {struct addrnode* parent_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  lru_update (struct addrtree*,struct addrnode*) ; 
 int /*<<< orphan*/  purge_node (struct addrtree*,struct addrnode*) ; 

__attribute__((used)) static void
lru_cleanup(struct addrtree *tree)
{
	struct addrnode *n, *p;
	int children;
	if (tree->max_node_count == 0) return;
	while (tree->node_count > tree->max_node_count) {
		n = tree->first;
		if (!n) break;
		children = (n->edge[0] != NULL) + (n->edge[1] != NULL);
		/** Don't remove this node, it is either the root or we can't
		 * do without it because it has 2 children */
		if (children == 2 || !n->parent_edge) {
			lru_update(tree, n);
			continue;
		}
		p = n->parent_edge->parent_node;
		purge_node(tree, n);
		/** Since we removed n, n's parent p is eligible for deletion
		 * if it is not the root node, caries no data and has only 1
		 * child */
		children = (p->edge[0] != NULL) + (p->edge[1] != NULL);
		if (!p->elem && children == 1 && p->parent_edge) {
			purge_node(tree, p);
		}
	}
}