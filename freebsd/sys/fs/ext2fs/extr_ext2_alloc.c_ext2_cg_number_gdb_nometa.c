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
typedef  int uint64_t ;
struct m_ext2fs {int e2fs_gcount; TYPE_1__* e2fs; } ;
struct TYPE_2__ {int e3fs_first_meta_bg; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2F_INCOMPAT_META_BG ; 
 int EXT2_DESCS_PER_BLOCK (struct m_ext2fs*) ; 
 scalar_t__ EXT2_HAS_INCOMPAT_FEATURE (struct m_ext2fs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2_cg_has_sb (struct m_ext2fs*,int) ; 

__attribute__((used)) static uint64_t
ext2_cg_number_gdb_nometa(struct m_ext2fs *fs, int cg)
{

	if (!ext2_cg_has_sb(fs, cg))
		return (0);

	if (EXT2_HAS_INCOMPAT_FEATURE(fs, EXT2F_INCOMPAT_META_BG))
		return (fs->e2fs->e3fs_first_meta_bg);

	return ((fs->e2fs_gcount + EXT2_DESCS_PER_BLOCK(fs) - 1) /
	    EXT2_DESCS_PER_BLOCK(fs));
}