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
struct vop_access_args {int /*<<< orphan*/  a_cred; int /*<<< orphan*/  a_accmode; struct vnode* a_vp; } ;
struct vnode {int /*<<< orphan*/  v_type; struct pfs_vdata* v_data; } ;
struct vattr {int /*<<< orphan*/  va_gid; int /*<<< orphan*/  va_uid; int /*<<< orphan*/  va_mode; } ;
struct pfs_vdata {TYPE_1__* pvd_pn; } ;
struct TYPE_2__ {int /*<<< orphan*/  pn_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  PFS_RETURN (int) ; 
 int /*<<< orphan*/  PFS_TRACE (char*) ; 
 int VOP_GETATTR (struct vnode*,struct vattr*,int /*<<< orphan*/ ) ; 
 int vaccess (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
pfs_access(struct vop_access_args *va)
{
	struct vnode *vn = va->a_vp;
	struct pfs_vdata *pvd = vn->v_data;
	struct vattr vattr;
	int error;

	PFS_TRACE(("%s", pvd->pvd_pn->pn_name));
	(void)pvd;

	error = VOP_GETATTR(vn, &vattr, va->a_cred);
	if (error)
		PFS_RETURN (error);
	error = vaccess(vn->v_type, vattr.va_mode, vattr.va_uid,
	    vattr.va_gid, va->a_accmode, va->a_cred, NULL);
	PFS_RETURN (error);
}