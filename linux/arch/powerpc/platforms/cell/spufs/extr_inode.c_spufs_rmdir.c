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
struct dentry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_ctx; } ;

/* Variables and functions */
 TYPE_1__* SPUFS_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_drop (struct dentry*) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int simple_rmdir (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  spu_forget (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spufs_prune_dir (struct dentry*) ; 

__attribute__((used)) static int spufs_rmdir(struct inode *parent, struct dentry *dir)
{
	/* remove all entries */
	int res;
	spufs_prune_dir(dir);
	d_drop(dir);
	res = simple_rmdir(parent, dir);
	/* We have to give up the mm_struct */
	spu_forget(SPUFS_I(d_inode(dir))->i_ctx);
	return res;
}