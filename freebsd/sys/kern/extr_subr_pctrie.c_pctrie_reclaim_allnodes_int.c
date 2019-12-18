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
struct pctrie_node {scalar_t__ pn_count; struct pctrie_node** pn_child; } ;
struct pctrie {int dummy; } ;
typedef  int /*<<< orphan*/  pctrie_free_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ PCTRIE_COUNT ; 
 int /*<<< orphan*/  pctrie_isleaf (struct pctrie_node*) ; 
 int /*<<< orphan*/  pctrie_node_put (struct pctrie*,struct pctrie_node*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pctrie_reclaim_allnodes_int(struct pctrie *ptree, struct pctrie_node *node,
    pctrie_free_t freefn)
{
	int slot;

	KASSERT(node->pn_count <= PCTRIE_COUNT,
	    ("pctrie_reclaim_allnodes_int: bad count in node %p", node));
	for (slot = 0; node->pn_count != 0; slot++) {
		if (node->pn_child[slot] == NULL)
			continue;
		if (!pctrie_isleaf(node->pn_child[slot]))
			pctrie_reclaim_allnodes_int(ptree,
			    node->pn_child[slot], freefn);
		node->pn_child[slot] = NULL;
		node->pn_count--;
	}
	pctrie_node_put(ptree, node, freefn);
}