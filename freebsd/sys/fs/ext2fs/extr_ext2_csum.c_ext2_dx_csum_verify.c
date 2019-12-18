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
typedef  scalar_t__ uint32_t ;
struct inode {TYPE_1__* i_e2fs; } ;
struct ext2fs_htree_tail {scalar_t__ ht_checksum; } ;
struct ext2fs_htree_entry {int dummy; } ;
struct ext2fs_htree_count {int h_entries_max; int h_entries_num; } ;
struct ext2fs_direct_2 {int dummy; } ;
struct TYPE_2__ {int e2fs_bsize; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ ext2_dx_csum (struct inode*,struct ext2fs_direct_2*,int,int,struct ext2fs_htree_tail*) ; 
 struct ext2fs_htree_count* ext2_get_dx_count (struct inode*,struct ext2fs_direct_2*,int*) ; 

int
ext2_dx_csum_verify(struct inode *ip, struct ext2fs_direct_2 *ep)
{
	uint32_t calculated;
	struct ext2fs_htree_count *cp;
	struct ext2fs_htree_tail *tp;
	int count_offset, limit, count;

	cp = ext2_get_dx_count(ip, ep, &count_offset);
	if (cp == NULL)
		return (0);

	limit = cp->h_entries_max;
	count = cp->h_entries_num;
	if (count_offset + (limit * sizeof(struct ext2fs_htree_entry)) >
	    ip->i_e2fs->e2fs_bsize - sizeof(struct ext2fs_htree_tail))
		return (EIO);

	tp = (struct ext2fs_htree_tail *)(((struct ext2fs_htree_entry *)cp) + limit);
	calculated = ext2_dx_csum(ip, ep,  count_offset, count, tp);

	if (tp->ht_checksum != calculated)
		return (EIO);

	return (0);
}