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
struct vop_setattr_args {struct vnode* a_vp; } ;
struct vnode {struct pfs_vdata* v_data; } ;
struct pfs_vdata {struct pfs_node* pvd_pn; } ;
struct pfs_node {int /*<<< orphan*/  pn_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  PFS_RETURN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PFS_TRACE (char*) ; 
 int /*<<< orphan*/  pfs_assert_not_owned (struct pfs_node*) ; 

__attribute__((used)) static int
pfs_setattr(struct vop_setattr_args *va)
{
	struct vnode *vn = va->a_vp;
	struct pfs_vdata *pvd = vn->v_data;
	struct pfs_node *pn = pvd->pvd_pn;

	PFS_TRACE(("%s", pn->pn_name));
	pfs_assert_not_owned(pn);

	/* Silently ignore unchangeable attributes. */
	PFS_RETURN (0);
}