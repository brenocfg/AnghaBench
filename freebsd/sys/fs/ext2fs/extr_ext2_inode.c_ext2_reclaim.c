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
struct vop_reclaim_args {struct vnode* a_vp; } ;
struct vnode {scalar_t__ v_data; } ;
struct inode {int i_flag; } ;

/* Variables and functions */
 int IN_LAZYMOD ; 
 int IN_MODIFIED ; 
 int /*<<< orphan*/  M_EXT2NODE ; 
 struct inode* VTOI (struct vnode*) ; 
 int /*<<< orphan*/  ext2_update (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_hash_remove (struct vnode*) ; 

int
ext2_reclaim(struct vop_reclaim_args *ap)
{
	struct inode *ip;
	struct vnode *vp = ap->a_vp;

	ip = VTOI(vp);
	if (ip->i_flag & IN_LAZYMOD) {
		ip->i_flag |= IN_MODIFIED;
		ext2_update(vp, 0);
	}
	vfs_hash_remove(vp);
	free(vp->v_data, M_EXT2NODE);
	vp->v_data = 0;
	return (0);
}