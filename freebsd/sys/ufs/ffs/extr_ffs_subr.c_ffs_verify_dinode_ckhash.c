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
typedef  scalar_t__ uint32_t ;
struct ufs2_dinode {scalar_t__ di_mode; scalar_t__ di_ckhash; } ;
struct fs {int fs_metackhash; } ;

/* Variables and functions */
 int CK_INODE ; 
 int EINVAL ; 
 scalar_t__ calculate_crc32c (long,void*,int) ; 

int
ffs_verify_dinode_ckhash(struct fs *fs, struct ufs2_dinode *dip)
{
	uint32_t ckhash, save_ckhash;

	/*
	 * Return success if unallocated or we are not doing inode check-hash.
	 */
	if (dip->di_mode == 0 || (fs->fs_metackhash & CK_INODE) == 0)
		return (0);
	/*
	 * Exclude di_ckhash from the crc32 calculation, e.g., always use
	 * a check-hash value of zero when calculating the check-hash.
	 */
	save_ckhash = dip->di_ckhash;
	dip->di_ckhash = 0;
	ckhash = calculate_crc32c(~0L, (void *)dip, sizeof(*dip));
	dip->di_ckhash = save_ckhash;
	if (save_ckhash == ckhash)
		return (0);
	return (EINVAL);
}