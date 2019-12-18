#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct m_ext2fs {int e2fs_bsize; TYPE_2__* e2fs_gd; TYPE_1__* e2fs; } ;
struct buf {int /*<<< orphan*/  b_data; } ;
struct TYPE_6__ {int ext4bgd_flags; } ;
struct TYPE_5__ {scalar_t__ e2fs_bpg; scalar_t__ e2fs_first_dblock; int e2fs_ipg; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  EXT2F_INCOMPAT_FLEX_BG ; 
 int EXT2_BG_BLOCK_UNINIT ; 
 int /*<<< orphan*/  EXT2_HAS_INCOMPAT_FEATURE (struct m_ext2fs*,int /*<<< orphan*/ ) ; 
 int EXT2_INODE_SIZE (struct m_ext2fs*) ; 
 scalar_t__ e2fs_gd_get_b_bitmap (TYPE_2__*) ; 
 scalar_t__ e2fs_gd_get_i_bitmap (TYPE_2__*) ; 
 scalar_t__ e2fs_gd_get_i_tables (TYPE_2__*) ; 
 scalar_t__ ext2_block_in_group (struct m_ext2fs*,scalar_t__,int) ; 
 int /*<<< orphan*/  ext2_mark_bitmap_end (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int ext2_number_base_meta_blocks (struct m_ext2fs*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setbit (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
ext2_cg_block_bitmap_init(struct m_ext2fs *fs, int cg, struct buf *bp)
{
	int bit, bit_max, inodes_per_block;
	uint64_t start, tmp;

	if (!(fs->e2fs_gd[cg].ext4bgd_flags & EXT2_BG_BLOCK_UNINIT))
		return (0);

	memset(bp->b_data, 0, fs->e2fs_bsize);

	bit_max = ext2_number_base_meta_blocks(fs, cg);
	if ((bit_max >> 3) >= fs->e2fs_bsize)
		return (EINVAL);

	for (bit = 0; bit < bit_max; bit++)
		setbit(bp->b_data, bit);

	start = (uint64_t)cg * fs->e2fs->e2fs_bpg + fs->e2fs->e2fs_first_dblock;

	/* Set bits for block and inode bitmaps, and inode table. */
	tmp = e2fs_gd_get_b_bitmap(&fs->e2fs_gd[cg]);
	if (!EXT2_HAS_INCOMPAT_FEATURE(fs, EXT2F_INCOMPAT_FLEX_BG) ||
	    ext2_block_in_group(fs, tmp, cg))
		setbit(bp->b_data, tmp - start);

	tmp = e2fs_gd_get_i_bitmap(&fs->e2fs_gd[cg]);
	if (!EXT2_HAS_INCOMPAT_FEATURE(fs, EXT2F_INCOMPAT_FLEX_BG) ||
	    ext2_block_in_group(fs, tmp, cg))
		setbit(bp->b_data, tmp - start);

	tmp = e2fs_gd_get_i_tables(&fs->e2fs_gd[cg]);
	inodes_per_block = fs->e2fs_bsize/EXT2_INODE_SIZE(fs);
	while( tmp < e2fs_gd_get_i_tables(&fs->e2fs_gd[cg]) +
	    fs->e2fs->e2fs_ipg / inodes_per_block ) {
		if (!EXT2_HAS_INCOMPAT_FEATURE(fs, EXT2F_INCOMPAT_FLEX_BG) ||
		    ext2_block_in_group(fs, tmp, cg))
			setbit(bp->b_data, tmp - start);
		tmp++;
	}

	/*
	 * Also if the number of blocks within the group is less than
	 * the blocksize * 8 ( which is the size of bitmap ), set rest
	 * of the block bitmap to 1
	 */
	ext2_mark_bitmap_end(fs->e2fs->e2fs_bpg, fs->e2fs_bsize * 8,
	    bp->b_data);

	/* Clean the flag */
	fs->e2fs_gd[cg].ext4bgd_flags &= ~EXT2_BG_BLOCK_UNINIT;

	return (0);
}