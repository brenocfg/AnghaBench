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
struct pctrie_node {int dummy; } ;
struct pctrie {int dummy; } ;
typedef  int /*<<< orphan*/  pctrie_free_t ;

/* Variables and functions */
 struct pctrie_node* pctrie_getroot (struct pctrie*) ; 
 int /*<<< orphan*/  pctrie_isleaf (struct pctrie_node*) ; 
 int /*<<< orphan*/  pctrie_reclaim_allnodes_int (struct pctrie*,struct pctrie_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pctrie_setroot (struct pctrie*,int /*<<< orphan*/ *) ; 

void
pctrie_reclaim_allnodes(struct pctrie *ptree, pctrie_free_t freefn)
{
	struct pctrie_node *root;

	root = pctrie_getroot(ptree);
	if (root == NULL)
		return;
	pctrie_setroot(ptree, NULL);
	if (!pctrie_isleaf(root))
		pctrie_reclaim_allnodes_int(ptree, root, freefn);
}