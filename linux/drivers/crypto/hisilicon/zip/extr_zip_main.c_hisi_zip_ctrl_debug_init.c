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
struct hisi_zip_ctrl {TYPE_1__* files; int /*<<< orphan*/  debug_root; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {int index; struct hisi_zip_ctrl* ctrl; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENOENT ; 
 int HZIP_CURRENT_QM ; 
 int HZIP_DEBUG_FILE_NUM ; 
 int /*<<< orphan*/ * ctrl_debug_file_name ; 
 int /*<<< orphan*/  ctrl_debug_fops ; 
 struct dentry* debugfs_create_file (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int hisi_zip_core_debug_init (struct hisi_zip_ctrl*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hisi_zip_ctrl_debug_init(struct hisi_zip_ctrl *ctrl)
{
	struct dentry *tmp;
	int i;

	for (i = HZIP_CURRENT_QM; i < HZIP_DEBUG_FILE_NUM; i++) {
		spin_lock_init(&ctrl->files[i].lock);
		ctrl->files[i].ctrl = ctrl;
		ctrl->files[i].index = i;

		tmp = debugfs_create_file(ctrl_debug_file_name[i], 0600,
					  ctrl->debug_root, ctrl->files + i,
					  &ctrl_debug_fops);
		if (!tmp)
			return -ENOENT;
	}

	return hisi_zip_core_debug_init(ctrl);
}