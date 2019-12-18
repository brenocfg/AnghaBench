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
struct pfs_node {int /*<<< orphan*/  pn_info; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  pfs_add_node (struct pfs_node*,struct pfs_node*) ; 
 struct pfs_node* pfs_alloc_node_flags (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pfs_destroy (struct pfs_node*) ; 
 int /*<<< orphan*/  pfstype_parent ; 
 int /*<<< orphan*/  pfstype_this ; 

__attribute__((used)) static int
pfs_fixup_dir_flags(struct pfs_node *parent, int flags)
{
	struct pfs_node *dot, *dotdot;

	dot = pfs_alloc_node_flags(parent->pn_info, ".", pfstype_this, flags);
	if (dot == NULL)
		return (ENOMEM);
	dotdot = pfs_alloc_node_flags(parent->pn_info, "..", pfstype_parent, flags);
	if (dotdot == NULL) {
		pfs_destroy(dot);
		return (ENOMEM);
	}
	pfs_add_node(parent, dot);
	pfs_add_node(parent, dotdot);
	return (0);
}