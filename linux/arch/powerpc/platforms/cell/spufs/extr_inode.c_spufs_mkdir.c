#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int umode_t ;
struct spu_context {unsigned int flags; } ;
struct inode {int i_mode; int /*<<< orphan*/  i_sb; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; int /*<<< orphan*/  i_gid; } ;
struct dentry {int dummy; } ;
struct TYPE_4__ {struct spu_context* i_ctx; int /*<<< orphan*/  i_gang; } ;
struct TYPE_3__ {scalar_t__ debug; } ;

/* Variables and functions */
 int ENOSPC ; 
 TYPE_2__* SPUFS_I (struct inode*) ; 
 unsigned int SPU_CREATE_NOSCHED ; 
 int S_IFDIR ; 
 int S_ISGID ; 
 struct spu_context* alloc_spu_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  dget (struct dentry*) ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  simple_dir_inode_operations ; 
 int /*<<< orphan*/  simple_dir_operations ; 
 int /*<<< orphan*/  spufs_dir_contents ; 
 int /*<<< orphan*/  spufs_dir_debug_contents ; 
 int /*<<< orphan*/  spufs_dir_nosched_contents ; 
 int spufs_fill_dir (struct dentry*,int /*<<< orphan*/ ,int,struct spu_context*) ; 
 TYPE_1__* spufs_get_sb_info (int /*<<< orphan*/ ) ; 
 struct inode* spufs_new_inode (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spufs_rmdir (struct inode*,struct dentry*) ; 

__attribute__((used)) static int
spufs_mkdir(struct inode *dir, struct dentry *dentry, unsigned int flags,
		umode_t mode)
{
	int ret;
	struct inode *inode;
	struct spu_context *ctx;

	inode = spufs_new_inode(dir->i_sb, mode | S_IFDIR);
	if (!inode)
		return -ENOSPC;

	if (dir->i_mode & S_ISGID) {
		inode->i_gid = dir->i_gid;
		inode->i_mode &= S_ISGID;
	}
	ctx = alloc_spu_context(SPUFS_I(dir)->i_gang); /* XXX gang */
	SPUFS_I(inode)->i_ctx = ctx;
	if (!ctx) {
		iput(inode);
		return -ENOSPC;
	}

	ctx->flags = flags;
	inode->i_op = &simple_dir_inode_operations;
	inode->i_fop = &simple_dir_operations;

	inode_lock(inode);

	dget(dentry);
	inc_nlink(dir);
	inc_nlink(inode);

	d_instantiate(dentry, inode);

	if (flags & SPU_CREATE_NOSCHED)
		ret = spufs_fill_dir(dentry, spufs_dir_nosched_contents,
					 mode, ctx);
	else
		ret = spufs_fill_dir(dentry, spufs_dir_contents, mode, ctx);

	if (!ret && spufs_get_sb_info(dir->i_sb)->debug)
		ret = spufs_fill_dir(dentry, spufs_dir_debug_contents,
				mode, ctx);

	if (ret)
		spufs_rmdir(dir, dentry);

	inode_unlock(inode);

	return ret;
}