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
struct pfs_node {int /*<<< orphan*/  pn_name; struct pfs_node* pn_next; struct pfs_node* pn_nodes; } ;

/* Variables and functions */
 int /*<<< orphan*/  pfs_lock (struct pfs_node*) ; 
 int /*<<< orphan*/  pfs_unlock (struct pfs_node*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

struct pfs_node *
pfs_find_node(struct pfs_node *parent, const char *name)
{
	struct pfs_node *pn;

	pfs_lock(parent);
	for (pn = parent->pn_nodes; pn != NULL; pn = pn->pn_next)
		if (strcmp(pn->pn_name, name) == 0)
			break;
	pfs_unlock(parent);
	return (pn);
}