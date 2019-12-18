#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct m_ext2fs {int e2fs_bsize; TYPE_2__* e2fs_gd; TYPE_1__* e2fs; } ;
struct inode {int /*<<< orphan*/  i_devvp; struct m_ext2fs* i_e2fs; } ;
struct buf {int dummy; } ;
struct TYPE_5__ {int ext4bgd_flags; } ;
struct TYPE_4__ {int e2fs_inode_size; int e2fs_ipg; } ;

/* Variables and functions */
 int EIO ; 
 int EXT2_BG_INODE_ZEROED ; 
 int EXT2_INODE_SIZE (struct m_ext2fs*) ; 
 int /*<<< orphan*/  bawrite (struct buf*) ; 
 scalar_t__ e2fs_gd_get_i_tables (TYPE_2__*) ; 
 scalar_t__ e2fs_gd_get_i_unused (TYPE_2__*) ; 
 int /*<<< orphan*/  fsbtodb (struct m_ext2fs*,scalar_t__) ; 
 struct buf* getblk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int howmany (scalar_t__,int) ; 
 int /*<<< orphan*/  vfs_bio_bzero_buf (struct buf*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ext2_zero_inode_table(struct inode *ip, int cg)
{
	struct m_ext2fs *fs;
	struct buf *bp;
	int i, all_blks, used_blks;

	fs = ip->i_e2fs;

	if (fs->e2fs_gd[cg].ext4bgd_flags & EXT2_BG_INODE_ZEROED)
		return (0);

	all_blks = fs->e2fs->e2fs_inode_size * fs->e2fs->e2fs_ipg /
	    fs->e2fs_bsize;

	used_blks = howmany(fs->e2fs->e2fs_ipg -
	    e2fs_gd_get_i_unused(&fs->e2fs_gd[cg]),
	    fs->e2fs_bsize / EXT2_INODE_SIZE(fs));

	for (i = 0; i < all_blks - used_blks; i++) {
		bp = getblk(ip->i_devvp, fsbtodb(fs,
		    e2fs_gd_get_i_tables(&fs->e2fs_gd[cg]) + used_blks + i),
		    fs->e2fs_bsize, 0, 0, 0);
		if (!bp)
			return (EIO);

		vfs_bio_bzero_buf(bp, 0, fs->e2fs_bsize);
		bawrite(bp);
	}

	fs->e2fs_gd[cg].ext4bgd_flags |= EXT2_BG_INODE_ZEROED;

	return (0);
}