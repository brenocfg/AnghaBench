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
struct vop_readlink_args {int /*<<< orphan*/  a_cred; int /*<<< orphan*/  a_uio; struct vnode* a_vp; } ;
struct vnode {TYPE_1__* v_mount; } ;
struct inode {int i_size; scalar_t__ i_shortlink; } ;
struct TYPE_2__ {int mnt_maxsymlinklen; } ;

/* Variables and functions */
 int VOP_READ (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct inode* VTOI (struct vnode*) ; 
 int /*<<< orphan*/  uiomove (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ext2_readlink(struct vop_readlink_args *ap)
{
	struct vnode *vp = ap->a_vp;
	struct inode *ip = VTOI(vp);
	int isize;

	isize = ip->i_size;
	if (isize < vp->v_mount->mnt_maxsymlinklen) {
		uiomove((char *)ip->i_shortlink, isize, ap->a_uio);
		return (0);
	}
	return (VOP_READ(vp, ap->a_uio, 0, ap->a_cred));
}