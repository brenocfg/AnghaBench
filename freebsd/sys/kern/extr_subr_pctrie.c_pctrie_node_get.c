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
typedef  void* uint16_t ;
struct pctrie_node {void* pn_clev; void* pn_count; int /*<<< orphan*/  pn_owner; } ;
struct pctrie {int dummy; } ;
typedef  struct pctrie_node* (* pctrie_alloc_t ) (struct pctrie*) ;

/* Variables and functions */

__attribute__((used)) static __inline struct pctrie_node *
pctrie_node_get(struct pctrie *ptree, pctrie_alloc_t allocfn, uint64_t owner,
    uint16_t count, uint16_t clevel)
{
	struct pctrie_node *node;

	node = allocfn(ptree);
	if (node == NULL)
		return (NULL);
	node->pn_owner = owner;
	node->pn_count = count;
	node->pn_clev = clevel;

	return (node);
}