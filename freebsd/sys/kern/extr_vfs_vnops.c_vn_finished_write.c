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
struct mount {int mnt_writeopcount; scalar_t__ mnt_vfs_ops; int mnt_kern_flag; } ;

/* Variables and functions */
 int MNTK_SUSPEND ; 
 int /*<<< orphan*/  MNT_ILOCK (struct mount*) ; 
 int /*<<< orphan*/  MNT_IUNLOCK (struct mount*) ; 
 int /*<<< orphan*/  MNT_REL (struct mount*) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  ref ; 
 int /*<<< orphan*/  vfs_assert_mount_counters (struct mount*) ; 
 int /*<<< orphan*/  vfs_dump_mount_counters (struct mount*) ; 
 int /*<<< orphan*/  vfs_mp_count_sub_pcpu (struct mount*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ vfs_op_thread_enter (struct mount*) ; 
 int /*<<< orphan*/  vfs_op_thread_exit (struct mount*) ; 
 int /*<<< orphan*/  vn_suspendable (struct mount*) ; 
 int /*<<< orphan*/  wakeup (int*) ; 
 int /*<<< orphan*/  writeopcount ; 

void
vn_finished_write(struct mount *mp)
{
	int c;

	if (mp == NULL || !vn_suspendable(mp))
		return;

	if (vfs_op_thread_enter(mp)) {
		vfs_mp_count_sub_pcpu(mp, writeopcount, 1);
		vfs_mp_count_sub_pcpu(mp, ref, 1);
		vfs_op_thread_exit(mp);
		return;
	}

	MNT_ILOCK(mp);
	vfs_assert_mount_counters(mp);
	MNT_REL(mp);
	c = --mp->mnt_writeopcount;
	if (mp->mnt_vfs_ops == 0) {
		MPASS((mp->mnt_kern_flag & MNTK_SUSPEND) == 0);
		MNT_IUNLOCK(mp);
		return;
	}
	if (c < 0)
		vfs_dump_mount_counters(mp);
	if ((mp->mnt_kern_flag & MNTK_SUSPEND) != 0 && c == 0)
		wakeup(&mp->mnt_writeopcount);
	MNT_IUNLOCK(mp);
}