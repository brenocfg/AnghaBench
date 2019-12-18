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
struct vop_ioctl_args {int /*<<< orphan*/  a_td; int /*<<< orphan*/  a_cred; int /*<<< orphan*/  a_fflag; int /*<<< orphan*/  a_data; int /*<<< orphan*/  a_command; int /*<<< orphan*/  a_vp; } ;
struct vnode {int dummy; } ;
struct unionfs_node_status {scalar_t__ uns_upper_opencnt; } ;
struct unionfs_node {struct vnode* un_lowervp; struct vnode* un_uppervp; } ;

/* Variables and functions */
 int EBADF ; 
 int /*<<< orphan*/  KASSERT_UNIONFS_VNODE (int /*<<< orphan*/ ) ; 
 int LK_EXCLUSIVE ; 
 int /*<<< orphan*/  LK_RELEASE ; 
 int LK_RETRY ; 
 struct vnode* NULLVP ; 
 int /*<<< orphan*/  UNIONFS_INTERNAL_DEBUG (char*,...) ; 
 int VOP_IOCTL (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOP_UNLOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct unionfs_node* VTOUNIONFS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unionfs_get_node_status (struct unionfs_node*,int /*<<< orphan*/ ,struct unionfs_node_status**) ; 
 int /*<<< orphan*/  unionfs_tryrem_node_status (struct unionfs_node*,struct unionfs_node_status*) ; 
 int /*<<< orphan*/  vn_lock (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
unionfs_ioctl(struct vop_ioctl_args *ap)
{
	int error;
	struct unionfs_node *unp;
	struct unionfs_node_status *unsp;
	struct vnode   *ovp;

	UNIONFS_INTERNAL_DEBUG("unionfs_ioctl: enter\n");

	KASSERT_UNIONFS_VNODE(ap->a_vp);

 	vn_lock(ap->a_vp, LK_EXCLUSIVE | LK_RETRY);
	unp = VTOUNIONFS(ap->a_vp);
	unionfs_get_node_status(unp, ap->a_td, &unsp);
	ovp = (unsp->uns_upper_opencnt ? unp->un_uppervp : unp->un_lowervp);
	unionfs_tryrem_node_status(unp, unsp);
	VOP_UNLOCK(ap->a_vp, LK_RELEASE);

	if (ovp == NULLVP)
		return (EBADF);

	error = VOP_IOCTL(ovp, ap->a_command, ap->a_data, ap->a_fflag,
	    ap->a_cred, ap->a_td);

	UNIONFS_INTERNAL_DEBUG("unionfs_ioctl: leave (%d)\n", error);

	return (error);
}