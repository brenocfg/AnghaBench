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
struct m_ext2fs {int e2fs_bsize; TYPE_1__* e2fs; } ;
struct ext2_gd {int dummy; } ;
typedef  int e4fs_daddr_t ;
struct TYPE_2__ {int e3fs_first_meta_bg; int e2fs_first_dblock; } ;

/* Variables and functions */
 int E2FS_REV0_GD_SIZE ; 
 int /*<<< orphan*/  EXT2F_INCOMPAT_64BIT ; 
 int /*<<< orphan*/  EXT2F_INCOMPAT_META_BG ; 
 scalar_t__ EXT2_BLOCKS_PER_GROUP (struct m_ext2fs*) ; 
 scalar_t__ EXT2_HAS_INCOMPAT_FEATURE (struct m_ext2fs*,int /*<<< orphan*/ ) ; 
 int SBSIZE ; 
 scalar_t__ ext2_cg_has_sb (struct m_ext2fs*,int) ; 

__attribute__((used)) static e4fs_daddr_t
ext2_cg_location(struct m_ext2fs *fs, int number)
{
	int cg, descpb, logical_sb, has_super = 0;

	/*
	 * Adjust logical superblock block number.
	 * Godmar thinks: if the blocksize is greater than 1024, then
	 * the superblock is logically part of block zero.
	 */
	logical_sb = fs->e2fs_bsize > SBSIZE ? 0 : 1;

	if (!EXT2_HAS_INCOMPAT_FEATURE(fs, EXT2F_INCOMPAT_META_BG) ||
	    number < fs->e2fs->e3fs_first_meta_bg)
		return (logical_sb + number + 1);

	if (EXT2_HAS_INCOMPAT_FEATURE(fs, EXT2F_INCOMPAT_64BIT))
		descpb = fs->e2fs_bsize / sizeof(struct ext2_gd);
	else
		descpb = fs->e2fs_bsize / E2FS_REV0_GD_SIZE;

	cg = descpb * number;

	if (ext2_cg_has_sb(fs, cg))
		has_super = 1;

	return (has_super + cg * (e4fs_daddr_t)EXT2_BLOCKS_PER_GROUP(fs) +
	    fs->e2fs->e2fs_first_dblock);
}