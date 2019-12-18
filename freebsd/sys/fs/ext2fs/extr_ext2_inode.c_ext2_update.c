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
struct m_ext2fs {scalar_t__ e2fs_bsize; scalar_t__ e2fs_ronly; } ;
struct inode {int i_flag; int /*<<< orphan*/  i_number; int /*<<< orphan*/  i_devvp; struct m_ext2fs* i_e2fs; } ;
struct ext2fs_dinode {int dummy; } ;
struct buf {scalar_t__ b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_VOP_ELOCKED (struct vnode*,char*) ; 
 int /*<<< orphan*/  DOINGASYNC (struct vnode*) ; 
 int EXT2_INODE_SIZE (struct m_ext2fs*) ; 
 int IN_LAZYACCESS ; 
 int IN_LAZYMOD ; 
 int IN_MODIFIED ; 
 int /*<<< orphan*/  NOCRED ; 
 struct inode* VTOI (struct vnode*) ; 
 int /*<<< orphan*/  bdwrite (struct buf*) ; 
 int bread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct buf**) ; 
 int /*<<< orphan*/  brelse (struct buf*) ; 
 int bwrite (struct buf*) ; 
 int ext2_i2ei (struct inode*,struct ext2fs_dinode*) ; 
 int /*<<< orphan*/  ext2_itimes (struct vnode*) ; 
 int /*<<< orphan*/  fsbtodb (struct m_ext2fs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ino_to_fsba (struct m_ext2fs*,int /*<<< orphan*/ ) ; 
 int ino_to_fsbo (struct m_ext2fs*,int /*<<< orphan*/ ) ; 

int
ext2_update(struct vnode *vp, int waitfor)
{
	struct m_ext2fs *fs;
	struct buf *bp;
	struct inode *ip;
	int error;

	ASSERT_VOP_ELOCKED(vp, "ext2_update");
	ext2_itimes(vp);
	ip = VTOI(vp);
	if ((ip->i_flag & IN_MODIFIED) == 0 && waitfor == 0)
		return (0);
	ip->i_flag &= ~(IN_LAZYACCESS | IN_LAZYMOD | IN_MODIFIED);
	fs = ip->i_e2fs;
	if (fs->e2fs_ronly)
		return (0);
	if ((error = bread(ip->i_devvp,
	    fsbtodb(fs, ino_to_fsba(fs, ip->i_number)),
	    (int)fs->e2fs_bsize, NOCRED, &bp)) != 0) {
		brelse(bp);
		return (error);
	}
	error = ext2_i2ei(ip, (struct ext2fs_dinode *)((char *)bp->b_data +
	    EXT2_INODE_SIZE(fs) * ino_to_fsbo(fs, ip->i_number)));
	if (error) {
		brelse(bp);
		return (error);
	}
	if (waitfor && !DOINGASYNC(vp))
		return (bwrite(bp));
	else {
		bdwrite(bp);
		return (0);
	}
}