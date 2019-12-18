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
struct dentry {int dummy; } ;
struct blk_mq_debugfs_attr {int /*<<< orphan*/  mode; scalar_t__ name; } ;
struct TYPE_2__ {void* i_private; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct dentry*) ; 
 int /*<<< orphan*/  blk_mq_debugfs_fops ; 
 TYPE_1__* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  debugfs_create_file (scalar_t__,int /*<<< orphan*/ ,struct dentry*,void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void debugfs_create_files(struct dentry *parent, void *data,
				 const struct blk_mq_debugfs_attr *attr)
{
	if (IS_ERR_OR_NULL(parent))
		return;

	d_inode(parent)->i_private = data;

	for (; attr->name; attr++)
		debugfs_create_file(attr->name, attr->mode, parent,
				    (void *)attr, &blk_mq_debugfs_fops);
}