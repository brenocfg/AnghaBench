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
struct vop_access_args {int /*<<< orphan*/  a_cred; int /*<<< orphan*/  a_accmode; struct vnode* a_vp; } ;
struct vnode {int /*<<< orphan*/  v_type; } ;
struct vattr {int /*<<< orphan*/  va_gid; int /*<<< orphan*/  va_uid; int /*<<< orphan*/  va_mode; } ;

/* Variables and functions */
 int VOP_GETATTR (struct vnode*,struct vattr*,int /*<<< orphan*/ ) ; 
 int vaccess (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mqfs_access(struct vop_access_args *ap)
{
	struct vnode *vp = ap->a_vp;
	struct vattr vattr;
	int error;

	error = VOP_GETATTR(vp, &vattr, ap->a_cred);
	if (error)
		return (error);
	error = vaccess(vp->v_type, vattr.va_mode, vattr.va_uid,
	    vattr.va_gid, ap->a_accmode, ap->a_cred, NULL);
	return (error);
}