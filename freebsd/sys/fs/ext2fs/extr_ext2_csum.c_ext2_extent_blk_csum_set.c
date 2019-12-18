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
struct ext4_extent_tail {int /*<<< orphan*/  et_checksum; } ;
struct ext4_extent_header {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2F_ROCOMPAT_METADATA_CKSUM ; 
 int /*<<< orphan*/  EXT2_HAS_RO_COMPAT_FEATURE (struct m_ext2fs*,int /*<<< orphan*/ ) ; 
 int EXT4_EXTENT_TAIL_OFFSET (struct ext4_extent_header*) ; 
 int /*<<< orphan*/  ext2_extent_blk_csum (struct inode*,struct ext4_extent_header*) ; 

void
ext2_extent_blk_csum_set(struct inode *ip, void *data)
{
	struct m_ext2fs *fs;
	struct ext4_extent_header *ehp;
	struct ext4_extent_tail *etp;

	fs = ip->i_e2fs;

	if (!EXT2_HAS_RO_COMPAT_FEATURE(fs, EXT2F_ROCOMPAT_METADATA_CKSUM))
		return;

	ehp = (struct ext4_extent_header *)data;
	etp = (struct ext4_extent_tail *)(((char *)data) +
	    EXT4_EXTENT_TAIL_OFFSET(ehp));

	etp->et_checksum = ext2_extent_blk_csum(ip,
	    (struct ext4_extent_header *)data);
}