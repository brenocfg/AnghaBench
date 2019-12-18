#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct m_ext2fs {int e2fs_fpg; TYPE_2__* e2fs_gd; TYPE_1__* e2fs; int /*<<< orphan*/  e2fs_csum_seed; } ;
struct buf {int /*<<< orphan*/  b_data; } ;
struct TYPE_4__ {int ext4bgd_b_bmap_csum; int ext4bgd_b_bmap_csum_hi; } ;
struct TYPE_3__ {scalar_t__ e3fs_desc_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2F_ROCOMPAT_METADATA_CKSUM ; 
 scalar_t__ EXT2_BG_BLOCK_BITMAP_CSUM_HI_LOCATION ; 
 int /*<<< orphan*/  EXT2_HAS_RO_COMPAT_FEATURE (struct m_ext2fs*,int /*<<< orphan*/ ) ; 
 int calculate_crc32c (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
ext2_gd_b_bitmap_csum_set(struct m_ext2fs *fs, int cg, struct buf *bp)
{
	uint32_t csum, size;

	if (!EXT2_HAS_RO_COMPAT_FEATURE(fs, EXT2F_ROCOMPAT_METADATA_CKSUM))
		return;

	size = fs->e2fs_fpg / 8;
	csum = calculate_crc32c(fs->e2fs_csum_seed, bp->b_data, size);
	fs->e2fs_gd[cg].ext4bgd_b_bmap_csum = csum & 0xFFFF;
	if (fs->e2fs->e3fs_desc_size >= EXT2_BG_BLOCK_BITMAP_CSUM_HI_LOCATION)
		fs->e2fs_gd[cg].ext4bgd_b_bmap_csum_hi = csum >> 16;
}