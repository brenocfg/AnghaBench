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
struct m_ext2fs {int e2fs_bsize; } ;
struct inode {struct m_ext2fs* i_e2fs; } ;
struct ext4_extent_header {int dummy; } ;
struct ext4_extent {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int
ext4_ext_space_block(struct inode *ip)
{
	struct m_ext2fs *fs;
	int size;

	fs = ip->i_e2fs;

	size = (fs->e2fs_bsize - sizeof(struct ext4_extent_header)) /
	    sizeof(struct ext4_extent);

	return (size);
}