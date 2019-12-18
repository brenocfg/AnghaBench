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
typedef  int umode_t ;
struct spufs_tree_descr {int mode; int /*<<< orphan*/  size; int /*<<< orphan*/  ops; scalar_t__* name; } ;
struct spu_context {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct dentry* d_alloc_name (struct dentry*,scalar_t__*) ; 
 int spufs_new_file (int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct spu_context*) ; 

__attribute__((used)) static int spufs_fill_dir(struct dentry *dir,
		const struct spufs_tree_descr *files, umode_t mode,
		struct spu_context *ctx)
{
	while (files->name && files->name[0]) {
		int ret;
		struct dentry *dentry = d_alloc_name(dir, files->name);
		if (!dentry)
			return -ENOMEM;
		ret = spufs_new_file(dir->d_sb, dentry, files->ops,
					files->mode & mode, files->size, ctx);
		if (ret)
			return ret;
		files++;
	}
	return 0;
}