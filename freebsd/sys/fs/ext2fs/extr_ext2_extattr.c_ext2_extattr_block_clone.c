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
typedef  scalar_t__ uint64_t ;
struct m_ext2fs {int /*<<< orphan*/  e2fs_bsize; } ;
struct inode {int /*<<< orphan*/  i_vnode; scalar_t__ i_facl; int /*<<< orphan*/  i_devvp; struct m_ext2fs* i_e2fs; } ;
struct ext2fs_extattr_header {scalar_t__ h_magic; int h_refcount; } ;
struct buf {int /*<<< orphan*/  b_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOSPC ; 
 struct ext2fs_extattr_header* EXT2_HDR (struct buf*) ; 
 scalar_t__ EXTATTR_MAGIC ; 
 int /*<<< orphan*/  bwrite (struct buf*) ; 
 scalar_t__ ext2_alloc_meta (struct inode*) ; 
 int /*<<< orphan*/  ext2_blkfree (struct inode*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2_update (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fsbtodb (struct m_ext2fs*,scalar_t__) ; 
 struct buf* getblk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ext2_extattr_block_clone(struct inode *ip, struct buf **bpp)
{
	struct m_ext2fs *fs;
	struct buf *sbp;
	struct buf *cbp;
	struct ext2fs_extattr_header *header;
	uint64_t facl;

	fs = ip->i_e2fs;
	sbp = *bpp;

	header = EXT2_HDR(sbp);
	if (header->h_magic != EXTATTR_MAGIC || header->h_refcount == 1)
		return (EINVAL);

	facl = ext2_alloc_meta(ip);
	if (!facl)
		return (ENOSPC);

	cbp = getblk(ip->i_devvp, fsbtodb(fs, facl), fs->e2fs_bsize, 0, 0, 0);
	if (!cbp) {
		ext2_blkfree(ip, facl, fs->e2fs_bsize);
		return (EIO);
	}

	memcpy(cbp->b_data, sbp->b_data, fs->e2fs_bsize);
	header->h_refcount--;
	bwrite(sbp);

	ip->i_facl = facl;
	ext2_update(ip->i_vnode, 1);

	header = EXT2_HDR(cbp);
	header->h_refcount = 1;

	*bpp = cbp;

	return (0);
}