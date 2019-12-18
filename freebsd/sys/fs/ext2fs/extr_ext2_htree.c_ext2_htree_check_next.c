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
typedef  int uint32_t ;
struct vnode {int dummy; } ;
struct inode {TYPE_1__* i_e2fs; } ;
struct ext2fs_htree_node {scalar_t__ h_entries; } ;
struct ext2fs_htree_lookup_level {scalar_t__ h_entry; scalar_t__ h_entries; struct buf* h_bp; } ;
struct ext2fs_htree_lookup_info {int h_levels_num; struct ext2fs_htree_lookup_level* h_levels; } ;
struct buf {scalar_t__ b_data; } ;
struct TYPE_2__ {int e2fs_bsize; } ;

/* Variables and functions */
 struct vnode* ITOV (struct inode*) ; 
 int /*<<< orphan*/  brelse (struct buf*) ; 
 scalar_t__ ext2_blkatoff (struct vnode*,int,int /*<<< orphan*/ *,struct buf**) ; 
 int ext2_htree_get_block (scalar_t__) ; 
 scalar_t__ ext2_htree_get_count (scalar_t__) ; 
 int ext2_htree_get_hash (scalar_t__) ; 

__attribute__((used)) static int
ext2_htree_check_next(struct inode *ip, uint32_t hash, const char *name,
    struct ext2fs_htree_lookup_info *info)
{
	struct vnode *vp = ITOV(ip);
	struct ext2fs_htree_lookup_level *level;
	struct buf *bp;
	uint32_t next_hash;
	int idx = info->h_levels_num - 1;
	int levels = 0;

	do {
		level = &info->h_levels[idx];
		level->h_entry++;
		if (level->h_entry < level->h_entries +
		    ext2_htree_get_count(level->h_entries))
			break;
		if (idx == 0)
			return (0);
		idx--;
		levels++;
	} while (1);

	next_hash = ext2_htree_get_hash(level->h_entry);
	if ((hash & 1) == 0) {
		if (hash != (next_hash & ~1))
			return (0);
	}

	while (levels > 0) {
		levels--;
		if (ext2_blkatoff(vp, ext2_htree_get_block(level->h_entry) *
		    ip->i_e2fs->e2fs_bsize, NULL, &bp) != 0)
			return (0);
		level = &info->h_levels[idx + 1];
		brelse(level->h_bp);
		level->h_bp = bp;
		level->h_entry = level->h_entries =
		    ((struct ext2fs_htree_node *)bp->b_data)->h_entries;
	}

	return (1);
}