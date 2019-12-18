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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct vnode {int dummy; } ;
struct m_ext2fs {scalar_t__ e2fs_uhash; int e2fs_bsize; struct ext2fs* e2fs; } ;
struct inode {struct m_ext2fs* i_e2fs; } ;
struct TYPE_2__ {scalar_t__ h_hash_version; int h_ind_levels; int h_info_len; } ;
struct ext2fs_htree_root {TYPE_1__ h_info; } ;
struct ext2fs_htree_node {struct ext2fs_htree_entry* h_entries; } ;
struct ext2fs_htree_lookup_level {struct buf* h_bp; struct ext2fs_htree_entry* h_entry; struct ext2fs_htree_entry* h_entries; } ;
struct ext2fs_htree_lookup_info {int h_levels_num; struct ext2fs_htree_lookup_level* h_levels; } ;
struct ext2fs_htree_entry {int dummy; } ;
struct ext2fs {int /*<<< orphan*/  e3fs_hash_seed; } ;
struct buf {scalar_t__ b_data; } ;

/* Variables and functions */
 scalar_t__ EXT2_HTREE_HALF_MD4 ; 
 scalar_t__ EXT2_HTREE_LEGACY ; 
 scalar_t__ EXT2_HTREE_TEA ; 
 struct vnode* ITOV (struct inode*) ; 
 scalar_t__ ext2_blkatoff (struct vnode*,int,int /*<<< orphan*/ *,struct buf**) ; 
 int ext2_htree_get_block (struct ext2fs_htree_entry*) ; 
 int ext2_htree_get_count (struct ext2fs_htree_entry*) ; 
 int ext2_htree_get_hash (struct ext2fs_htree_entry*) ; 
 int ext2_htree_get_limit (struct ext2fs_htree_entry*) ; 
 int /*<<< orphan*/  ext2_htree_hash (char const*,int,int /*<<< orphan*/ ,scalar_t__,int*,int*) ; 
 int /*<<< orphan*/  ext2_htree_release (struct ext2fs_htree_lookup_info*) ; 
 scalar_t__ ext2_htree_root_limit (struct inode*,int) ; 

__attribute__((used)) static int
ext2_htree_find_leaf(struct inode *ip, const char *name, int namelen,
    uint32_t *hash, uint8_t *hash_ver,
    struct ext2fs_htree_lookup_info *info)
{
	struct vnode *vp;
	struct ext2fs *fs;
	struct m_ext2fs *m_fs;
	struct buf *bp = NULL;
	struct ext2fs_htree_root *rootp;
	struct ext2fs_htree_entry *entp, *start, *end, *middle, *found;
	struct ext2fs_htree_lookup_level *level_info;
	uint32_t hash_major = 0, hash_minor = 0;
	uint32_t levels, cnt;
	uint8_t hash_version;

	if (name == NULL || info == NULL)
		return (-1);

	vp = ITOV(ip);
	fs = ip->i_e2fs->e2fs;
	m_fs = ip->i_e2fs;

	if (ext2_blkatoff(vp, 0, NULL, &bp) != 0)
		return (-1);

	info->h_levels_num = 1;
	info->h_levels[0].h_bp = bp;
	rootp = (struct ext2fs_htree_root *)bp->b_data;
	if (rootp->h_info.h_hash_version != EXT2_HTREE_LEGACY &&
	    rootp->h_info.h_hash_version != EXT2_HTREE_HALF_MD4 &&
	    rootp->h_info.h_hash_version != EXT2_HTREE_TEA)
		goto error;

	hash_version = rootp->h_info.h_hash_version;
	if (hash_version <= EXT2_HTREE_TEA)
		hash_version += m_fs->e2fs_uhash;
	*hash_ver = hash_version;

	ext2_htree_hash(name, namelen, fs->e3fs_hash_seed,
	    hash_version, &hash_major, &hash_minor);
	*hash = hash_major;

	if ((levels = rootp->h_info.h_ind_levels) > 1)
		goto error;

	entp = (struct ext2fs_htree_entry *)(((char *)&rootp->h_info) +
	    rootp->h_info.h_info_len);

	if (ext2_htree_get_limit(entp) !=
	    ext2_htree_root_limit(ip, rootp->h_info.h_info_len))
		goto error;

	while (1) {
		cnt = ext2_htree_get_count(entp);
		if (cnt == 0 || cnt > ext2_htree_get_limit(entp))
			goto error;

		start = entp + 1;
		end = entp + cnt - 1;
		while (start <= end) {
			middle = start + (end - start) / 2;
			if (ext2_htree_get_hash(middle) > hash_major)
				end = middle - 1;
			else
				start = middle + 1;
		}
		found = start - 1;

		level_info = &(info->h_levels[info->h_levels_num - 1]);
		level_info->h_bp = bp;
		level_info->h_entries = entp;
		level_info->h_entry = found;
		if (levels == 0)
			return (0);
		levels--;
		if (ext2_blkatoff(vp,
		    ext2_htree_get_block(found) * m_fs->e2fs_bsize,
		    NULL, &bp) != 0)
			goto error;
		entp = ((struct ext2fs_htree_node *)bp->b_data)->h_entries;
		info->h_levels_num++;
		info->h_levels[info->h_levels_num - 1].h_bp = bp;
	}

error:
	ext2_htree_release(info);
	return (-1);
}