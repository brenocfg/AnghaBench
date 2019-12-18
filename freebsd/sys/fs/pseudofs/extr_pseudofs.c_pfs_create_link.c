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
struct pfs_node {int pn_flags; int /*<<< orphan*/  pn_destroy; int /*<<< orphan*/  pn_vis; int /*<<< orphan*/  pn_attr; int /*<<< orphan*/  pn_fill; int /*<<< orphan*/  pn_info; } ;
typedef  int /*<<< orphan*/  pfs_vis_t ;
typedef  int /*<<< orphan*/  pfs_fill_t ;
typedef  int /*<<< orphan*/  pfs_destroy_t ;
typedef  int /*<<< orphan*/  pfs_attr_t ;

/* Variables and functions */
 int /*<<< orphan*/  pfs_add_node (struct pfs_node*,struct pfs_node*) ; 
 struct pfs_node* pfs_alloc_node_flags (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pfstype_symlink ; 

struct pfs_node	*
pfs_create_link(struct pfs_node *parent, const char *name, pfs_fill_t fill,
		pfs_attr_t attr, pfs_vis_t vis, pfs_destroy_t destroy,
		int flags)
{
	struct pfs_node *pn;

	pn = pfs_alloc_node_flags(parent->pn_info, name, pfstype_symlink, flags);
	if (pn == NULL)
		return (NULL);
	pn->pn_fill = fill;
	pn->pn_attr = attr;
	pn->pn_vis = vis;
	pn->pn_destroy = destroy;
	pn->pn_flags = flags;
	pfs_add_node(parent, pn);

	return (pn);
}