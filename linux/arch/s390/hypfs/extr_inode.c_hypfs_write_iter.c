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
struct super_block {int /*<<< orphan*/  s_root; struct hypfs_sb_info* s_fs_info; } ;
struct kiocb {int /*<<< orphan*/  ki_filp; } ;
struct iov_iter {int dummy; } ;
struct hypfs_sb_info {scalar_t__ last_update; int /*<<< orphan*/  lock; } ;
typedef  int ssize_t ;
struct TYPE_2__ {struct super_block* i_sb; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ MACHINE_IS_VM ; 
 TYPE_1__* file_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hypfs_delete_tree (int /*<<< orphan*/ ) ; 
 int hypfs_diag_create_files (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hypfs_update_update (struct super_block*) ; 
 int hypfs_vm_create_files (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iov_iter_advance (struct iov_iter*,size_t) ; 
 size_t iov_iter_count (struct iov_iter*) ; 
 scalar_t__ ktime_get_seconds () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static ssize_t hypfs_write_iter(struct kiocb *iocb, struct iov_iter *from)
{
	int rc;
	struct super_block *sb = file_inode(iocb->ki_filp)->i_sb;
	struct hypfs_sb_info *fs_info = sb->s_fs_info;
	size_t count = iov_iter_count(from);

	/*
	 * Currently we only allow one update per second for two reasons:
	 * 1. diag 204 is VERY expensive
	 * 2. If several processes do updates in parallel and then read the
	 *    hypfs data, the likelihood of collisions is reduced, if we restrict
	 *    the minimum update interval. A collision occurs, if during the
	 *    data gathering of one process another process triggers an update
	 *    If the first process wants to ensure consistent data, it has
	 *    to restart data collection in this case.
	 */
	mutex_lock(&fs_info->lock);
	if (fs_info->last_update == ktime_get_seconds()) {
		rc = -EBUSY;
		goto out;
	}
	hypfs_delete_tree(sb->s_root);
	if (MACHINE_IS_VM)
		rc = hypfs_vm_create_files(sb->s_root);
	else
		rc = hypfs_diag_create_files(sb->s_root);
	if (rc) {
		pr_err("Updating the hypfs tree failed\n");
		hypfs_delete_tree(sb->s_root);
		goto out;
	}
	hypfs_update_update(sb);
	rc = count;
	iov_iter_advance(from, count);
out:
	mutex_unlock(&fs_info->lock);
	return rc;
}