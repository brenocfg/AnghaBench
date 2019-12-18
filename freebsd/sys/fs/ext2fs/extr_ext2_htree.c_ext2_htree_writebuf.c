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
struct inode {int dummy; } ;
struct ext2fs_htree_lookup_info {int h_levels_num; TYPE_1__* h_levels; } ;
struct ext2fs_direct_2 {int dummy; } ;
struct buf {scalar_t__ b_data; } ;
struct TYPE_2__ {struct buf* h_bp; } ;

/* Variables and functions */
 int bwrite (struct buf*) ; 
 int /*<<< orphan*/  ext2_dx_csum_set (struct inode*,struct ext2fs_direct_2*) ; 

__attribute__((used)) static int
ext2_htree_writebuf(struct inode* ip, struct ext2fs_htree_lookup_info *info)
{
	int i, error;

	for (i = 0; i < info->h_levels_num; i++) {
		struct buf *bp = info->h_levels[i].h_bp;
		ext2_dx_csum_set(ip, (struct ext2fs_direct_2 *)bp->b_data);
		error = bwrite(bp);
		if (error)
			return (error);
	}

	return (0);
}