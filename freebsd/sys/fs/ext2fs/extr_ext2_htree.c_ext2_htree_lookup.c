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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct vnode {int dummy; } ;
struct m_ext2fs {int e2fs_bsize; } ;
struct inode {struct m_ext2fs* i_e2fs; } ;
struct ext2fs_searchslot {scalar_t__ slotstatus; int slotoffset; scalar_t__ slotfreespace; } ;
struct ext2fs_htree_lookup_info {int h_levels_num; TYPE_1__* h_levels; } ;
struct ext2fs_htree_entry {int dummy; } ;
struct buf {int /*<<< orphan*/  b_data; } ;
typedef  int /*<<< orphan*/  info ;
typedef  int doff_t ;
struct TYPE_2__ {struct ext2fs_htree_entry* h_entry; } ;

/* Variables and functions */
 int ENOENT ; 
 struct vnode* ITOV (struct inode*) ; 
 scalar_t__ NONE ; 
 int /*<<< orphan*/  brelse (struct buf*) ; 
 scalar_t__ ext2_blkatoff (struct vnode*,int,int /*<<< orphan*/ *,struct buf**) ; 
 int ext2_htree_check_next (struct inode*,int,char const*,struct ext2fs_htree_lookup_info*) ; 
 scalar_t__ ext2_htree_find_leaf (struct inode*,char const*,int,int*,int /*<<< orphan*/ *,struct ext2fs_htree_lookup_info*) ; 
 int ext2_htree_get_block (struct ext2fs_htree_entry*) ; 
 int /*<<< orphan*/  ext2_htree_release (struct ext2fs_htree_lookup_info*) ; 
 scalar_t__ ext2_search_dirblock (struct inode*,int /*<<< orphan*/ ,int*,char const*,int,int*,int*,int*,int*,struct ext2fs_searchslot*) ; 
 int /*<<< orphan*/  memset (struct ext2fs_htree_lookup_info*,int /*<<< orphan*/ ,int) ; 

int
ext2_htree_lookup(struct inode *ip, const char *name, int namelen,
    struct buf **bpp, int *entryoffp, doff_t *offp,
    doff_t *prevoffp, doff_t *endusefulp,
    struct ext2fs_searchslot *ss)
{
	struct vnode *vp;
	struct ext2fs_htree_lookup_info info;
	struct ext2fs_htree_entry *leaf_node;
	struct m_ext2fs *m_fs;
	struct buf *bp;
	uint32_t blk;
	uint32_t dirhash;
	uint32_t bsize;
	uint8_t hash_version;
	int search_next;
	int found = 0;

	m_fs = ip->i_e2fs;
	bsize = m_fs->e2fs_bsize;
	vp = ITOV(ip);

	/* TODO: print error msg because we don't lookup '.' and '..' */

	memset(&info, 0, sizeof(info));
	if (ext2_htree_find_leaf(ip, name, namelen, &dirhash,
	    &hash_version, &info))
		return (-1);

	do {
		leaf_node = info.h_levels[info.h_levels_num - 1].h_entry;
		blk = ext2_htree_get_block(leaf_node);
		if (ext2_blkatoff(vp, blk * bsize, NULL, &bp) != 0) {
			ext2_htree_release(&info);
			return (-1);
		}

		*offp = blk * bsize;
		*entryoffp = 0;
		*prevoffp = blk * bsize;
		*endusefulp = blk * bsize;

		if (ss->slotstatus == NONE) {
			ss->slotoffset = -1;
			ss->slotfreespace = 0;
		}

		if (ext2_search_dirblock(ip, bp->b_data, &found,
		    name, namelen, entryoffp, offp, prevoffp,
		    endusefulp, ss) != 0) {
			brelse(bp);
			ext2_htree_release(&info);
			return (-1);
		}

		if (found) {
			*bpp = bp;
			ext2_htree_release(&info);
			return (0);
		}

		brelse(bp);
		search_next = ext2_htree_check_next(ip, dirhash, name, &info);
	} while (search_next);

	ext2_htree_release(&info);
	return (ENOENT);
}