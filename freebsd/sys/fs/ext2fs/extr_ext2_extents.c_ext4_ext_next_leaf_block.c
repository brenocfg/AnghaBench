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
struct ext4_extent_path {int ep_depth; TYPE_1__* ep_index; int /*<<< orphan*/  ep_header; } ;
struct TYPE_2__ {int ei_blk; } ;

/* Variables and functions */
 int EXT4_MAX_BLOCKS ; 
 TYPE_1__* EXT_LAST_INDEX (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned
ext4_ext_next_leaf_block(struct inode *ip, struct ext4_extent_path *path)
{
	int depth = path->ep_depth;

	/* Empty tree */
	if (depth == 0)
		return (EXT4_MAX_BLOCKS);

	/* Go to indexes. */
	depth--;

	while (depth >= 0) {
		if (path[depth].ep_index !=
		    EXT_LAST_INDEX(path[depth].ep_header))
			return (path[depth].ep_index[1].ei_blk);

		depth--;
	}

	return (EXT4_MAX_BLOCKS);
}