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
struct m_ext2fs {int dummy; } ;
struct inode {struct m_ext2fs* i_e2fs; } ;
struct ext2fs_direct_tail {scalar_t__ e2dt_reserved_zero1; int e2dt_rec_len; scalar_t__ e2dt_reserved_zero2; scalar_t__ e2dt_reserved_ft; } ;
struct ext2fs_direct_2 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2F_ROCOMPAT_METADATA_CKSUM ; 
 scalar_t__ EXT2_FT_DIR_CSUM ; 
 int /*<<< orphan*/  EXT2_HAS_RO_COMPAT_FEATURE (struct m_ext2fs*,int /*<<< orphan*/ ) ; 

int
ext2_is_dirent_tail(struct inode *ip, struct ext2fs_direct_2 *ep)
{
	struct m_ext2fs *fs;
	struct ext2fs_direct_tail *tp;

	fs = ip->i_e2fs;

	if (!EXT2_HAS_RO_COMPAT_FEATURE(fs, EXT2F_ROCOMPAT_METADATA_CKSUM))
		return (0);

	tp = (struct ext2fs_direct_tail *)ep;
	if (tp->e2dt_reserved_zero1 == 0 &&
	    tp->e2dt_rec_len == sizeof(struct ext2fs_direct_tail) &&
	    tp->e2dt_reserved_zero2 == 0 &&
	    tp->e2dt_reserved_ft == EXT2_FT_DIR_CSUM)
		return (1);

	return (0);
}