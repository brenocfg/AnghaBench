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
struct TYPE_2__ {struct dentry* qm_d; int /*<<< orphan*/  debug_root; } ;
struct hisi_qm {scalar_t__ fun_type; TYPE_1__ debug; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int CURRENT_Q ; 
 int DEBUG_FILE_NUM ; 
 int ENOENT ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 scalar_t__ QM_HW_PF ; 
 struct dentry* debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 struct dentry* debugfs_create_file (char*,int,struct dentry*,struct hisi_qm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (struct dentry*) ; 
 scalar_t__ qm_create_debugfs_file (struct hisi_qm*,int) ; 
 int /*<<< orphan*/  qm_regs_fops ; 

int hisi_qm_debug_init(struct hisi_qm *qm)
{
	struct dentry *qm_d, *qm_regs;
	int i, ret;

	qm_d = debugfs_create_dir("qm", qm->debug.debug_root);
	if (IS_ERR(qm_d))
		return -ENOENT;
	qm->debug.qm_d = qm_d;

	/* only show this in PF */
	if (qm->fun_type == QM_HW_PF)
		for (i = CURRENT_Q; i < DEBUG_FILE_NUM; i++)
			if (qm_create_debugfs_file(qm, i)) {
				ret = -ENOENT;
				goto failed_to_create;
			}

	qm_regs = debugfs_create_file("qm_regs", 0444, qm->debug.qm_d, qm,
				      &qm_regs_fops);
	if (IS_ERR(qm_regs)) {
		ret = -ENOENT;
		goto failed_to_create;
	}

	return 0;

failed_to_create:
	debugfs_remove_recursive(qm_d);
	return ret;
}