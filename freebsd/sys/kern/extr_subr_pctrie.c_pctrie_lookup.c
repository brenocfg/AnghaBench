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
typedef  int /*<<< orphan*/  uint64_t ;
struct pctrie_node {struct pctrie_node** pn_child; int /*<<< orphan*/  pn_clev; } ;
struct pctrie {int dummy; } ;

/* Variables and functions */
 struct pctrie_node* pctrie_getroot (struct pctrie*) ; 
 scalar_t__ pctrie_isleaf (struct pctrie_node*) ; 
 scalar_t__ pctrie_keybarr (struct pctrie_node*,int /*<<< orphan*/ ) ; 
 int pctrie_slot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pctrie_toval (struct pctrie_node*) ; 

uint64_t *
pctrie_lookup(struct pctrie *ptree, uint64_t index)
{
	struct pctrie_node *node;
	uint64_t *m;
	int slot;

	node = pctrie_getroot(ptree);
	while (node != NULL) {
		if (pctrie_isleaf(node)) {
			m = pctrie_toval(node);
			if (*m == index)
				return (m);
			else
				break;
		} else if (pctrie_keybarr(node, index))
			break;
		slot = pctrie_slot(index, node->pn_clev);
		node = node->pn_child[slot];
	}
	return (NULL);
}