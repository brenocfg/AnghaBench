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
struct TYPE_2__ {struct debugfs_file* files; struct dentry* qm_d; } ;
struct hisi_qm {TYPE_1__ debug; } ;
struct dentry {int dummy; } ;
struct debugfs_file {int index; TYPE_1__* debug; int /*<<< orphan*/  lock; } ;
typedef  enum qm_debug_file { ____Placeholder_qm_debug_file } qm_debug_file ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 struct dentry* debugfs_create_file (int /*<<< orphan*/ ,int,struct dentry*,struct debugfs_file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * qm_debug_file_name ; 
 int /*<<< orphan*/  qm_debug_fops ; 

__attribute__((used)) static int qm_create_debugfs_file(struct hisi_qm *qm, enum qm_debug_file index)
{
	struct dentry *qm_d = qm->debug.qm_d, *tmp;
	struct debugfs_file *file = qm->debug.files + index;

	tmp = debugfs_create_file(qm_debug_file_name[index], 0600, qm_d, file,
				  &qm_debug_fops);
	if (IS_ERR(tmp))
		return -ENOENT;

	file->index = index;
	mutex_init(&file->lock);
	file->debug = &qm->debug;

	return 0;
}