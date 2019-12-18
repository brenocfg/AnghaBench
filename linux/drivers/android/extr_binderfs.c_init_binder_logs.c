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
struct super_block {struct binderfs_info* s_fs_info; struct dentry* s_root; } ;
struct dentry {int dummy; } ;
struct binderfs_info {struct dentry* proc_log_dir; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dentry*) ; 
 int PTR_ERR (struct dentry*) ; 
 int /*<<< orphan*/  binder_state_fops ; 
 int /*<<< orphan*/  binder_stats_fops ; 
 int /*<<< orphan*/  binder_transaction_log ; 
 int /*<<< orphan*/  binder_transaction_log_failed ; 
 int /*<<< orphan*/  binder_transaction_log_fops ; 
 int /*<<< orphan*/  binder_transactions_fops ; 
 struct dentry* binderfs_create_dir (struct dentry*,char*) ; 
 struct dentry* binderfs_create_file (struct dentry*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int init_binder_logs(struct super_block *sb)
{
	struct dentry *binder_logs_root_dir, *dentry, *proc_log_dir;
	struct binderfs_info *info;
	int ret = 0;

	binder_logs_root_dir = binderfs_create_dir(sb->s_root,
						   "binder_logs");
	if (IS_ERR(binder_logs_root_dir)) {
		ret = PTR_ERR(binder_logs_root_dir);
		goto out;
	}

	dentry = binderfs_create_file(binder_logs_root_dir, "stats",
				      &binder_stats_fops, NULL);
	if (IS_ERR(dentry)) {
		ret = PTR_ERR(dentry);
		goto out;
	}

	dentry = binderfs_create_file(binder_logs_root_dir, "state",
				      &binder_state_fops, NULL);
	if (IS_ERR(dentry)) {
		ret = PTR_ERR(dentry);
		goto out;
	}

	dentry = binderfs_create_file(binder_logs_root_dir, "transactions",
				      &binder_transactions_fops, NULL);
	if (IS_ERR(dentry)) {
		ret = PTR_ERR(dentry);
		goto out;
	}

	dentry = binderfs_create_file(binder_logs_root_dir,
				      "transaction_log",
				      &binder_transaction_log_fops,
				      &binder_transaction_log);
	if (IS_ERR(dentry)) {
		ret = PTR_ERR(dentry);
		goto out;
	}

	dentry = binderfs_create_file(binder_logs_root_dir,
				      "failed_transaction_log",
				      &binder_transaction_log_fops,
				      &binder_transaction_log_failed);
	if (IS_ERR(dentry)) {
		ret = PTR_ERR(dentry);
		goto out;
	}

	proc_log_dir = binderfs_create_dir(binder_logs_root_dir, "proc");
	if (IS_ERR(proc_log_dir)) {
		ret = PTR_ERR(proc_log_dir);
		goto out;
	}
	info = sb->s_fs_info;
	info->proc_log_dir = proc_log_dir;

out:
	return ret;
}