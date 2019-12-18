#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct super_block {int dummy; } ;
struct inode {int dummy; } ;
struct spufs_inode_info {struct inode vfs_inode; scalar_t__ i_openers; int /*<<< orphan*/ * i_ctx; int /*<<< orphan*/ * i_gang; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct spufs_inode_info* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spufs_inode_cache ; 

__attribute__((used)) static struct inode *
spufs_alloc_inode(struct super_block *sb)
{
	struct spufs_inode_info *ei;

	ei = kmem_cache_alloc(spufs_inode_cache, GFP_KERNEL);
	if (!ei)
		return NULL;

	ei->i_gang = NULL;
	ei->i_ctx = NULL;
	ei->i_openers = 0;

	return &ei->vfs_inode;
}