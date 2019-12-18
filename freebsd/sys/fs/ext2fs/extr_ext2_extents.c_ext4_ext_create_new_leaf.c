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
struct ext4_extent_path {TYPE_1__* ep_header; } ;
struct ext4_extent {int /*<<< orphan*/  e_blk; } ;
struct TYPE_2__ {scalar_t__ eh_ecount; scalar_t__ eh_max; } ;

/* Variables and functions */
 scalar_t__ EXT_HAS_FREE_INDEX (struct ext4_extent_path*) ; 
 int /*<<< orphan*/  ext4_ext_drop_refs (struct ext4_extent_path*) ; 
 int ext4_ext_find_extent (struct inode*,int /*<<< orphan*/ ,struct ext4_extent_path**) ; 
 int ext4_ext_grow_indepth (struct inode*,struct ext4_extent_path*,struct ext4_extent*) ; 
 int ext4_ext_inode_depth (struct inode*) ; 
 int ext4_ext_split (struct inode*,struct ext4_extent_path*,struct ext4_extent*,int) ; 

__attribute__((used)) static int
ext4_ext_create_new_leaf(struct inode *ip, struct ext4_extent_path *path,
    struct ext4_extent *newext)
{
	struct ext4_extent_path *curpath;
	int depth, i, error;

repeat:
	i = depth = ext4_ext_inode_depth(ip);

	/* Look for free index entry int the tree */
	curpath = path + depth;
	while (i > 0 && !EXT_HAS_FREE_INDEX(curpath)) {
		i--;
		curpath--;
	}

	/*
	 * We use already allocated block for index block,
	 * so subsequent data blocks should be contiguous.
	 */
	if (EXT_HAS_FREE_INDEX(curpath)) {
		error = ext4_ext_split(ip, path, newext, i);
		if (error)
			goto out;

		/* Refill path. */
		ext4_ext_drop_refs(path);
		error = ext4_ext_find_extent(ip, newext->e_blk, &path);
		if (error)
			goto out;
	} else {
		/* Tree is full, do grow in depth. */
		error = ext4_ext_grow_indepth(ip, path, newext);
		if (error)
			goto out;

		/* Refill path. */
		ext4_ext_drop_refs(path);
		error = ext4_ext_find_extent(ip, newext->e_blk, &path);
		if (error)
			goto out;

		/* Check and split tree if required. */
		depth = ext4_ext_inode_depth(ip);
		if (path[depth].ep_header->eh_ecount ==
		    path[depth].ep_header->eh_max)
			goto repeat;
	}

out:
	return (error);
}