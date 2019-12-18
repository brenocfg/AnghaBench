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
struct vnode {int dummy; } ;
struct unionfs_mount {struct vnode* um_rootvp; } ;
struct mount {int dummy; } ;

/* Variables and functions */
 int LK_TYPE_MASK ; 
 struct unionfs_mount* MOUNTTOUNIONFSMOUNT (struct mount*) ; 
 int /*<<< orphan*/  UNIONFSDEBUG (char*,struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOP_ISLOCKED (struct vnode*) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 
 int /*<<< orphan*/  vref (struct vnode*) ; 

__attribute__((used)) static int
unionfs_root(struct mount *mp, int flags, struct vnode **vpp)
{
	struct unionfs_mount *ump;
	struct vnode   *vp;

	ump = MOUNTTOUNIONFSMOUNT(mp);
	vp = ump->um_rootvp;

	UNIONFSDEBUG("unionfs_root: rootvp=%p locked=%x\n",
	    vp, VOP_ISLOCKED(vp));

	vref(vp);
	if (flags & LK_TYPE_MASK)
		vn_lock(vp, flags);

	*vpp = vp;

	return (0);
}