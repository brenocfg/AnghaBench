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
struct spufs_inode_info {scalar_t__ i_gang; scalar_t__ i_ctx; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 struct spufs_inode_info* SPUFS_I (struct inode*) ; 
 int /*<<< orphan*/  clear_inode (struct inode*) ; 
 int /*<<< orphan*/  put_spu_context (scalar_t__) ; 
 int /*<<< orphan*/  put_spu_gang (scalar_t__) ; 

__attribute__((used)) static void
spufs_evict_inode(struct inode *inode)
{
	struct spufs_inode_info *ei = SPUFS_I(inode);
	clear_inode(inode);
	if (ei->i_ctx)
		put_spu_context(ei->i_ctx);
	if (ei->i_gang)
		put_spu_gang(ei->i_gang);
}