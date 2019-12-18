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
struct vop_mknod_args {TYPE_1__* a_dvp; int /*<<< orphan*/  a_cnp; struct vnode** a_vpp; struct vattr* a_vap; } ;
struct vnode {int /*<<< orphan*/  v_type; } ;
struct vattr {scalar_t__ va_rdev; int /*<<< orphan*/  va_mode; int /*<<< orphan*/  va_type; } ;
struct inode {int i_flag; scalar_t__ i_rdev; int /*<<< orphan*/  i_number; } ;
typedef  int /*<<< orphan*/  ino_t ;
struct TYPE_2__ {int /*<<< orphan*/  v_mount; } ;

/* Variables and functions */
 int IN_ACCESS ; 
 int IN_CHANGE ; 
 int IN_E4EXTENTS ; 
 int IN_UPDATE ; 
 int /*<<< orphan*/  LK_EXCLUSIVE ; 
 int /*<<< orphan*/  MAKEIMODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int VFS_VGET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vnode**) ; 
 int /*<<< orphan*/  VNON ; 
 scalar_t__ VNOVAL ; 
 struct inode* VTOI (struct vnode*) ; 
 int ext2_makeinode (int /*<<< orphan*/ ,TYPE_1__*,struct vnode**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vgone (struct vnode*) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 

__attribute__((used)) static int
ext2_mknod(struct vop_mknod_args *ap)
{
	struct vattr *vap = ap->a_vap;
	struct vnode **vpp = ap->a_vpp;
	struct inode *ip;
	ino_t ino;
	int error;

	error = ext2_makeinode(MAKEIMODE(vap->va_type, vap->va_mode),
	    ap->a_dvp, vpp, ap->a_cnp);
	if (error)
		return (error);
	ip = VTOI(*vpp);
	ip->i_flag |= IN_ACCESS | IN_CHANGE | IN_UPDATE;
	if (vap->va_rdev != VNOVAL) {
		/*
		 * Want to be able to use this to make badblock
		 * inodes, so don't truncate the dev number.
		 */
		if (!(ip->i_flag & IN_E4EXTENTS))
			ip->i_rdev = vap->va_rdev;
	}
	/*
	 * Remove inode, then reload it through VFS_VGET so it is
	 * checked to see if it is an alias of an existing entry in
	 * the inode cache.	 XXX I don't believe this is necessary now.
	 */
	(*vpp)->v_type = VNON;
	ino = ip->i_number;	/* Save this before vgone() invalidates ip. */
	vgone(*vpp);
	vput(*vpp);
	error = VFS_VGET(ap->a_dvp->v_mount, ino, LK_EXCLUSIVE, vpp);
	if (error) {
		*vpp = NULL;
		return (error);
	}
	return (0);
}