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
struct m_ext2fs {int /*<<< orphan*/  e2fs_bsize; } ;
struct inode {int /*<<< orphan*/  i_vnode; int /*<<< orphan*/  i_facl; struct m_ext2fs* i_e2fs; int /*<<< orphan*/  i_blocks; int /*<<< orphan*/  i_devvp; } ;
struct ext2fs_extattr_header {scalar_t__ h_magic; int h_blocks; int h_refcount; } ;
struct buf {scalar_t__ b_bufsize; scalar_t__ b_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  EXT2_FIRST_ENTRY (struct buf*) ; 
 struct ext2fs_extattr_header* EXT2_HDR (struct buf*) ; 
 scalar_t__ EXTATTR_MAGIC ; 
 int /*<<< orphan*/  NOCRED ; 
 int bread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct buf**) ; 
 int /*<<< orphan*/  brelse (struct buf*) ; 
 scalar_t__ btodb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwrite (struct buf*) ; 
 int /*<<< orphan*/  ext2_blkfree (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ext2_extattr_check (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ext2_update (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fsbtodb (struct m_ext2fs*,int /*<<< orphan*/ ) ; 

int ext2_extattr_free(struct inode *ip)
{
	struct m_ext2fs *fs;
	struct buf *bp;
	struct ext2fs_extattr_header *header;
	int error;

	fs = ip->i_e2fs;

	if (!ip->i_facl)
		return (0);

	error = bread(ip->i_devvp, fsbtodb(fs, ip->i_facl),
	    fs->e2fs_bsize, NOCRED, &bp);
	if (error) {
		return (error);
	}

	/* Check attributes magic value */
	header = EXT2_HDR(bp);
	if (header->h_magic != EXTATTR_MAGIC || header->h_blocks != 1) {
		brelse(bp);
		return (EINVAL);
	}

	error = ext2_extattr_check(EXT2_FIRST_ENTRY(bp),
	    bp->b_data + bp->b_bufsize);
	if (error) {
		brelse(bp);
		return (error);
	}

	if (header->h_refcount > 1) {
		header->h_refcount--;
		bwrite(bp);
	} else {
		ext2_blkfree(ip, ip->i_facl, ip->i_e2fs->e2fs_bsize);
		brelse(bp);
	}

	ip->i_blocks -= btodb(ip->i_e2fs->e2fs_bsize);
	ip->i_facl = 0;
	ext2_update(ip->i_vnode, 1);

	return (0);
}