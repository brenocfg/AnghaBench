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
struct TYPE_2__ {int /*<<< orphan*/  ec_type; } ;
struct inode {TYPE_1__ i_ext_cache; } ;
struct ext4_extent_path {scalar_t__ ep_depth; struct ext4_extent* ep_ext; struct ext4_extent_header* ep_header; } ;
struct ext4_extent_header {scalar_t__ eh_ecount; scalar_t__ eh_max; } ;
struct ext4_extent {scalar_t__ e_len; scalar_t__ e_blk; int /*<<< orphan*/  e_start_hi; int /*<<< orphan*/  e_start_lo; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  EXT4_EXT_CACHE_NO ; 
 int EXT4_MAX_BLOCKS ; 
 struct ext4_extent* EXT_FIRST_EXTENT (struct ext4_extent_header*) ; 
 struct ext4_extent* EXT_LAST_EXTENT (struct ext4_extent_header*) ; 
 struct ext4_extent* EXT_MAX_EXTENT (struct ext4_extent_header*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_EXT2EXTENTS ; 
 scalar_t__ ext4_can_extents_be_merged (struct ext4_extent*,struct ext4_extent*) ; 
 int ext4_ext_correct_indexes (struct inode*,struct ext4_extent_path*) ; 
 int ext4_ext_create_new_leaf (struct inode*,struct ext4_extent_path*,struct ext4_extent*) ; 
 int /*<<< orphan*/  ext4_ext_dirty (struct inode*,struct ext4_extent_path*) ; 
 int /*<<< orphan*/  ext4_ext_drop_refs (struct ext4_extent_path*) ; 
 int ext4_ext_find_extent (struct inode*,int,struct ext4_extent_path**) ; 
 int ext4_ext_inode_depth (struct inode*) ; 
 int ext4_ext_next_leaf_block (struct inode*,struct ext4_extent_path*) ; 
 int /*<<< orphan*/  free (struct ext4_extent_path*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (struct ext4_extent*,struct ext4_extent*,int) ; 

__attribute__((used)) static int
ext4_ext_insert_extent(struct inode *ip, struct ext4_extent_path *path,
    struct ext4_extent *newext)
{
	struct ext4_extent_header * eh;
	struct ext4_extent *ex, *nex, *nearex;
	struct ext4_extent_path *npath;
	int depth, len, error, next;

	depth = ext4_ext_inode_depth(ip);
	ex = path[depth].ep_ext;
	npath = NULL;

	if (newext->e_len == 0 || path[depth].ep_header == NULL)
		return (EINVAL);

	/* Insert block into found extent. */
	if (ex && ext4_can_extents_be_merged(ex, newext)) {
		ex->e_len = ex->e_len + newext->e_len;
		eh = path[depth].ep_header;
		nearex = ex;
		goto merge;
	}

repeat:
	depth = ext4_ext_inode_depth(ip);
	eh = path[depth].ep_header;
	if (eh->eh_ecount < eh->eh_max)
		goto has_space;

	/* Try next leaf */
	nex = EXT_LAST_EXTENT(eh);
	next = ext4_ext_next_leaf_block(ip, path);
	if (newext->e_blk > nex->e_blk && next != EXT4_MAX_BLOCKS) {
		KASSERT(npath == NULL,
		    ("ext4_ext_insert_extent: bad path"));

		error = ext4_ext_find_extent(ip, next, &npath);
		if (error)
			goto cleanup;

		if (npath->ep_depth != path->ep_depth) {
			error = EIO;
			goto cleanup;
		}

		eh = npath[depth].ep_header;
		if (eh->eh_ecount < eh->eh_max) {
			path = npath;
			goto repeat;
		}
	}

	/*
	 * There is no free space in the found leaf,
	 * try to add a new leaf to the tree.
	 */
	error = ext4_ext_create_new_leaf(ip, path, newext);
	if (error)
		goto cleanup;

	depth = ext4_ext_inode_depth(ip);
	eh = path[depth].ep_header;

has_space:
	nearex = path[depth].ep_ext;
	if (!nearex) {
		/* Create new extent in the leaf. */
		path[depth].ep_ext = EXT_FIRST_EXTENT(eh);
	} else if (newext->e_blk > nearex->e_blk) {
		if (nearex != EXT_LAST_EXTENT(eh)) {
			len = EXT_MAX_EXTENT(eh) - nearex;
			len = (len - 1) * sizeof(struct ext4_extent);
			len = len < 0 ? 0 : len;
			memmove(nearex + 2, nearex + 1, len);
		}
		path[depth].ep_ext = nearex + 1;
	} else {
		len = (EXT_MAX_EXTENT(eh) - nearex) * sizeof(struct ext4_extent);
		len = len < 0 ? 0 : len;
		memmove(nearex + 1, nearex, len);
		path[depth].ep_ext = nearex;
	}

	eh->eh_ecount = eh->eh_ecount + 1;
	nearex = path[depth].ep_ext;
	nearex->e_blk = newext->e_blk;
	nearex->e_start_lo = newext->e_start_lo;
	nearex->e_start_hi = newext->e_start_hi;
	nearex->e_len = newext->e_len;

merge:
	/* Try to merge extents to the right. */
	while (nearex < EXT_LAST_EXTENT(eh)) {
		if (!ext4_can_extents_be_merged(nearex, nearex + 1))
			break;

		/* Merge with next extent. */
		nearex->e_len = nearex->e_len + nearex[1].e_len;
		if (nearex + 1 < EXT_LAST_EXTENT(eh)) {
			len = (EXT_LAST_EXTENT(eh) - nearex - 1) *
			    sizeof(struct ext4_extent);
			memmove(nearex + 1, nearex + 2, len);
		}

		eh->eh_ecount = eh->eh_ecount - 1;
		KASSERT(eh->eh_ecount != 0,
		    ("ext4_ext_insert_extent: bad ecount"));
	}

	/*
	 * Try to merge extents to the left,
	 * start from inexes correction.
	 */
	error = ext4_ext_correct_indexes(ip, path);
	if (error)
		goto cleanup;

	ext4_ext_dirty(ip, path + depth);

cleanup:
	if (npath) {
		ext4_ext_drop_refs(npath);
		free(npath, M_EXT2EXTENTS);
	}

	ip->i_ext_cache.ec_type = EXT4_EXT_CACHE_NO;
	return (error);
}