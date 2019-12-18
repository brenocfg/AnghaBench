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
struct ext4_extent_path {TYPE_1__* ep_index; struct ext4_extent_header* ep_header; struct ext4_extent* ep_ext; } ;
struct ext4_extent_header {int dummy; } ;
struct ext4_extent {void* e_blk; } ;
typedef  void* int32_t ;
struct TYPE_2__ {void* ei_blk; } ;

/* Variables and functions */
 int EIO ; 
 struct ext4_extent* EXT_FIRST_EXTENT (struct ext4_extent_header*) ; 
 TYPE_1__* EXT_FIRST_INDEX (struct ext4_extent_header*) ; 
 int /*<<< orphan*/  ext4_ext_dirty (struct inode*,struct ext4_extent_path*) ; 
 int ext4_ext_inode_depth (struct inode*) ; 

__attribute__((used)) static int
ext4_ext_correct_indexes(struct inode *ip, struct ext4_extent_path *path)
{
	struct ext4_extent_header *eh;
	struct ext4_extent *ex;
	int32_t border;
	int depth, k;

	depth = ext4_ext_inode_depth(ip);
	eh = path[depth].ep_header;
	ex = path[depth].ep_ext;

	if (ex == NULL || eh == NULL)
		return (EIO);

	if (!depth)
		return (0);

	/* We will correct tree if first leaf got modified only. */
	if (ex != EXT_FIRST_EXTENT(eh))
		return (0);

	k = depth - 1;
	border = path[depth].ep_ext->e_blk;
	path[k].ep_index->ei_blk = border;
	ext4_ext_dirty(ip, path + k);
	while (k--) {
		/* Change all left-side indexes. */
		if (path[k+1].ep_index != EXT_FIRST_INDEX(path[k+1].ep_header))
			break;

		path[k].ep_index->ei_blk = border;
		ext4_ext_dirty(ip, path + k);
	}

	return (0);
}