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
struct ext4_extent_path {TYPE_1__* ep_header; int /*<<< orphan*/  ep_index; } ;
typedef  int /*<<< orphan*/  e4fs_daddr_t ;
struct TYPE_2__ {scalar_t__ eh_ecount; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  ext4_ext_blkfree (struct inode*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_ext_dirty (struct inode*,struct ext4_extent_path*) ; 
 int /*<<< orphan*/  ext4_ext_index_pblock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ext4_ext_rm_index(struct inode *ip, struct ext4_extent_path *path)
{
	e4fs_daddr_t leaf;

	/* Free index block. */
	path--;
	leaf = ext4_ext_index_pblock(path->ep_index);
	KASSERT(path->ep_header->eh_ecount != 0,
	    ("ext4_ext_rm_index: bad ecount"));
	path->ep_header->eh_ecount--;
	ext4_ext_dirty(ip, path);
	ext4_ext_blkfree(ip, leaf, 1, 0);
	return (0);
}