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
struct pctrie_node {scalar_t__ pn_count; int /*<<< orphan*/ ** pn_child; } ;
struct pctrie {int dummy; } ;
typedef  int /*<<< orphan*/  (* pctrie_free_t ) (struct pctrie*,struct pctrie_node*) ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PCTRIE_COUNT ; 

__attribute__((used)) static __inline void
pctrie_node_put(struct pctrie *ptree, struct pctrie_node *node,
    pctrie_free_t freefn)
{
#ifdef INVARIANTS
	int slot;

	KASSERT(node->pn_count == 0,
	    ("pctrie_node_put: node %p has %d children", node,
	    node->pn_count));
	for (slot = 0; slot < PCTRIE_COUNT; slot++)
		KASSERT(node->pn_child[slot] == NULL,
		    ("pctrie_node_put: node %p has a child", node));
#endif
	freefn(ptree, node);
}