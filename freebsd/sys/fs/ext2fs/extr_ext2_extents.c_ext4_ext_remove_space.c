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
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct inode {scalar_t__ i_db; } ;
struct ext4_extent_path {int ep_depth; scalar_t__ index_count; struct ext4_extent_header* ep_header; struct ext4_extent_path* ep_data; scalar_t__ ep_index; } ;
struct ext4_extent_header {scalar_t__ eh_ecount; } ;
struct buf {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_2__ {int /*<<< orphan*/  eh_max; scalar_t__ eh_depth; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 scalar_t__ EXT_LAST_INDEX (struct ext4_extent_header*) ; 
 int /*<<< orphan*/  M_EXT2EXTENTS ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  brelse (struct buf*) ; 
 int ext4_ext_check_header (struct inode*,struct ext4_extent_header*) ; 
 int /*<<< orphan*/  ext4_ext_dirty (struct inode*,struct ext4_extent_path*) ; 
 int /*<<< orphan*/  ext4_ext_drop_refs (struct ext4_extent_path*) ; 
 int /*<<< orphan*/  ext4_ext_fill_path_bdata (struct ext4_extent_path*,struct buf*,int /*<<< orphan*/ ) ; 
 TYPE_1__* ext4_ext_header (struct inode*) ; 
 int /*<<< orphan*/  ext4_ext_index_pblock (scalar_t__) ; 
 int ext4_ext_inode_depth (struct inode*) ; 
 scalar_t__ ext4_ext_more_to_rm (struct ext4_extent_path*) ; 
 int ext4_ext_rm_index (struct inode*,struct ext4_extent_path*) ; 
 int ext4_ext_rm_leaf (struct inode*,struct ext4_extent_path*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_ext_space_root (struct inode*) ; 
 struct buf* ext4_read_extent_tree_block (struct inode*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct ext4_extent_path*,int /*<<< orphan*/ ) ; 
 struct ext4_extent_path* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct ext4_extent_path*,int /*<<< orphan*/ ,int) ; 

int
ext4_ext_remove_space(struct inode *ip, off_t length, int flags,
    struct ucred *cred, struct thread *td)
{
	struct buf *bp;
	struct ext4_extent_header *ehp;
	struct ext4_extent_path *path;
	int depth;
	int i, error;

	ehp = (struct ext4_extent_header *)ip->i_db;
	depth = ext4_ext_inode_depth(ip);

	error = ext4_ext_check_header(ip, ehp);
	if(error)
		return (error);

	path = malloc(sizeof(struct ext4_extent_path) * (depth + 1),
	    M_EXT2EXTENTS, M_WAITOK | M_ZERO);
	if (!path)
		return (ENOMEM);

	path[0].ep_header = ehp;
	path[0].ep_depth = depth;
	i = 0;
	while (error == 0 && i >= 0) {
		if (i == depth) {
			/* This is leaf. */
			error = ext4_ext_rm_leaf(ip, path, length);
			if (error)
				break;
			free(path[i].ep_data, M_EXT2EXTENTS);
			path[i].ep_data = NULL;
			i--;
			continue;
		}

		/* This is index. */
		if (!path[i].ep_header)
			path[i].ep_header =
			    (struct ext4_extent_header *)path[i].ep_data;

		if (!path[i].ep_index) {
			/* This level hasn't touched yet. */
			path[i].ep_index = EXT_LAST_INDEX(path[i].ep_header);
			path[i].index_count = path[i].ep_header->eh_ecount + 1;
		} else {
			/* We've already was here, see at next index. */
			path[i].ep_index--;
		}

		if (ext4_ext_more_to_rm(path + i)) {
			memset(path + i + 1, 0, sizeof(*path));
			bp = ext4_read_extent_tree_block(ip,
			    ext4_ext_index_pblock(path[i].ep_index),
			    path[0].ep_depth - (i + 1), 0);
			if (!bp) {
				error = EIO;
				break;
			}

			ext4_ext_fill_path_bdata(&path[i+1], bp,
			    ext4_ext_index_pblock(path[i].ep_index));
			brelse(bp);
			path[i].index_count = path[i].ep_header->eh_ecount;
			i++;
		} else {
			if (path[i].ep_header->eh_ecount == 0 && i > 0) {
				/* Index is empty, remove it. */
				error = ext4_ext_rm_index(ip, path + i);
			}
			free(path[i].ep_data, M_EXT2EXTENTS);
			path[i].ep_data = NULL;
			i--;
		}
	}

	if (path->ep_header->eh_ecount == 0) {
		/*
		 * Truncate the tree to zero.
		 */
		 ext4_ext_header(ip)->eh_depth = 0;
		 ext4_ext_header(ip)->eh_max = ext4_ext_space_root(ip);
		 ext4_ext_dirty(ip, path);
	}

	ext4_ext_drop_refs(path);
	free(path, M_EXT2EXTENTS);

	return (error);
}