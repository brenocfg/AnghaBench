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
struct spufs_sb_info {int dummy; } ;
struct spufs_fs_context {int mode; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
struct fs_context {int /*<<< orphan*/ * ops; struct spufs_sb_info* s_fs_info; struct spufs_fs_context* fs_private; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  current_gid () ; 
 int /*<<< orphan*/  current_uid () ; 
 int /*<<< orphan*/  kfree (struct spufs_fs_context*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spufs_context_ops ; 

__attribute__((used)) static int spufs_init_fs_context(struct fs_context *fc)
{
	struct spufs_fs_context *ctx;
	struct spufs_sb_info *sbi;

	ctx = kzalloc(sizeof(struct spufs_fs_context), GFP_KERNEL);
	if (!ctx)
		goto nomem;

	sbi = kzalloc(sizeof(struct spufs_sb_info), GFP_KERNEL);
	if (!sbi)
		goto nomem_ctx;

	ctx->uid = current_uid();
	ctx->gid = current_gid();
	ctx->mode = 0755;

	fc->fs_private = ctx;
	fc->s_fs_info = sbi;
	fc->ops = &spufs_context_ops;
	return 0;

nomem_ctx:
	kfree(ctx);
nomem:
	return -ENOMEM;
}