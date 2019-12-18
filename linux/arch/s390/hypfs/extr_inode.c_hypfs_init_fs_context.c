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
struct hypfs_sb_info {int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  lock; } ;
struct fs_context {int /*<<< orphan*/ * ops; struct hypfs_sb_info* s_fs_info; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  current_gid () ; 
 int /*<<< orphan*/  current_uid () ; 
 int /*<<< orphan*/  hypfs_context_ops ; 
 struct hypfs_sb_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hypfs_init_fs_context(struct fs_context *fc)
{
	struct hypfs_sb_info *sbi;

	sbi = kzalloc(sizeof(struct hypfs_sb_info), GFP_KERNEL);
	if (!sbi)
		return -ENOMEM;

	mutex_init(&sbi->lock);
	sbi->uid = current_uid();
	sbi->gid = current_gid();

	fc->s_fs_info = sbi;
	fc->ops = &hypfs_context_ops;
	return 0;
}