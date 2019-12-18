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
struct super_block {int /*<<< orphan*/  s_root; } ;
struct spufs_fs_context {int mode; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
struct inode {int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;
struct fs_context {struct spufs_fs_context* fs_private; } ;
struct TYPE_2__ {int /*<<< orphan*/ * i_ctx; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 TYPE_1__* SPUFS_I (struct inode*) ; 
 int S_IFDIR ; 
 int /*<<< orphan*/  d_make_root (struct inode*) ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 int /*<<< orphan*/  simple_dir_inode_operations ; 
 int /*<<< orphan*/  simple_dir_operations ; 
 int /*<<< orphan*/  spu_management_ops ; 
 struct inode* spufs_new_inode (struct super_block*,int) ; 

__attribute__((used)) static int spufs_create_root(struct super_block *sb, struct fs_context *fc)
{
	struct spufs_fs_context *ctx = fc->fs_private;
	struct inode *inode;

	if (!spu_management_ops)
		return -ENODEV;

	inode = spufs_new_inode(sb, S_IFDIR | ctx->mode);
	if (!inode)
		return -ENOMEM;

	inode->i_uid = ctx->uid;
	inode->i_gid = ctx->gid;
	inode->i_op = &simple_dir_inode_operations;
	inode->i_fop = &simple_dir_operations;
	SPUFS_I(inode)->i_ctx = NULL;
	inc_nlink(inode);

	sb->s_root = d_make_root(inode);
	if (!sb->s_root)
		return -ENOMEM;
	return 0;
}