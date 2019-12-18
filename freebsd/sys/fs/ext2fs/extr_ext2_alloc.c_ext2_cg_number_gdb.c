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
typedef  int /*<<< orphan*/  uint64_t ;
struct m_ext2fs {TYPE_1__* e2fs; } ;
struct TYPE_2__ {unsigned long e3fs_first_meta_bg; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2F_INCOMPAT_META_BG ; 
 int EXT2_DESCS_PER_BLOCK (struct m_ext2fs*) ; 
 int /*<<< orphan*/  EXT2_HAS_INCOMPAT_FEATURE (struct m_ext2fs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2_cg_number_gdb_meta (struct m_ext2fs*,int) ; 
 int /*<<< orphan*/  ext2_cg_number_gdb_nometa (struct m_ext2fs*,int) ; 

uint64_t
ext2_cg_number_gdb(struct m_ext2fs *fs, int cg)
{
	unsigned long first_meta_bg, metagroup;

	first_meta_bg = fs->e2fs->e3fs_first_meta_bg;
	metagroup = cg / EXT2_DESCS_PER_BLOCK(fs);

	if (!EXT2_HAS_INCOMPAT_FEATURE(fs, EXT2F_INCOMPAT_META_BG) ||
	    metagroup < first_meta_bg)
		return (ext2_cg_number_gdb_nometa(fs, cg));

	return ext2_cg_number_gdb_meta(fs, cg);
}