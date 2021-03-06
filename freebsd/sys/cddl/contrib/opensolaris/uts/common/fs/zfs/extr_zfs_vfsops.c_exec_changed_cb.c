#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* z_vfs; } ;
typedef  TYPE_1__ zfsvfs_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_5__ {int /*<<< orphan*/  vfs_flag; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  MNTOPT_EXEC ; 
 int /*<<< orphan*/  MNTOPT_NOEXEC ; 
 int /*<<< orphan*/  VFS_NOEXEC ; 
 int /*<<< orphan*/  vfs_clearmntopt (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_setmntopt (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
exec_changed_cb(void *arg, uint64_t newval)
{
	zfsvfs_t *zfsvfs = arg;

	if (newval == FALSE) {
		zfsvfs->z_vfs->vfs_flag |= VFS_NOEXEC;
		vfs_clearmntopt(zfsvfs->z_vfs, MNTOPT_EXEC);
		vfs_setmntopt(zfsvfs->z_vfs, MNTOPT_NOEXEC, NULL, 0);
	} else {
		zfsvfs->z_vfs->vfs_flag &= ~VFS_NOEXEC;
		vfs_clearmntopt(zfsvfs->z_vfs, MNTOPT_NOEXEC);
		vfs_setmntopt(zfsvfs->z_vfs, MNTOPT_EXEC, NULL, 0);
	}
}