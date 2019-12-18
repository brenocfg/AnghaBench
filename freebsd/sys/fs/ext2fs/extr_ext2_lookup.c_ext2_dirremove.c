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
struct inode {scalar_t__ i_count; scalar_t__ i_offset; int i_flag; } ;
struct ext2fs_direct_2 {int e2d_reclen; scalar_t__ e2d_ino; } ;
struct componentname {int dummy; } ;
struct buf {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 scalar_t__ DOINGASYNC (struct vnode*) ; 
 int IN_CHANGE ; 
 int IN_UPDATE ; 
 struct inode* VTOI (struct vnode*) ; 
 int /*<<< orphan*/  bdwrite (struct buf*) ; 
 int bwrite (struct buf*) ; 
 int ext2_blkatoff (struct vnode*,int /*<<< orphan*/ ,char**,struct buf**) ; 
 int /*<<< orphan*/  ext2_dirent_csum_set (struct inode*,struct ext2fs_direct_2*) ; 

int
ext2_dirremove(struct vnode *dvp, struct componentname *cnp)
{
	struct inode *dp;
	struct ext2fs_direct_2 *ep, *rep;
	struct buf *bp;
	int error;

	dp = VTOI(dvp);
	if (dp->i_count == 0) {
		/*
		 * First entry in block: set d_ino to zero.
		 */
		if ((error =
		    ext2_blkatoff(dvp, (off_t)dp->i_offset, (char **)&ep,
		    &bp)) != 0)
			return (error);
		ep->e2d_ino = 0;
		ext2_dirent_csum_set(dp, (struct ext2fs_direct_2 *)bp->b_data);
		error = bwrite(bp);
		dp->i_flag |= IN_CHANGE | IN_UPDATE;
		return (error);
	}
	/*
	 * Collapse new free space into previous entry.
	 */
	if ((error = ext2_blkatoff(dvp, (off_t)(dp->i_offset - dp->i_count),
	    (char **)&ep, &bp)) != 0)
		return (error);

	/* Set 'rep' to the entry being removed. */
	if (dp->i_count == 0)
		rep = ep;
	else
		rep = (struct ext2fs_direct_2 *)((char *)ep + ep->e2d_reclen);
	ep->e2d_reclen += rep->e2d_reclen;
	ext2_dirent_csum_set(dp, (struct ext2fs_direct_2 *)bp->b_data);
	if (DOINGASYNC(dvp) && dp->i_count != 0)
		bdwrite(bp);
	else
		error = bwrite(bp);
	dp->i_flag |= IN_CHANGE | IN_UPDATE;
	return (error);
}