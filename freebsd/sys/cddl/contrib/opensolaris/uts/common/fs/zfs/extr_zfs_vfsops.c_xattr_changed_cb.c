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
 int /*<<< orphan*/  MNTOPT_NOXATTR ; 
 int /*<<< orphan*/  MNTOPT_XATTR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  VFS_XATTR ; 
 int /*<<< orphan*/  vfs_clearmntopt (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_setmntopt (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xattr_changed_cb(void *arg, uint64_t newval)
{
	zfsvfs_t *zfsvfs = arg;

	if (newval == TRUE) {
		/* XXX locking on vfs_flag? */
#ifdef TODO
		zfsvfs->z_vfs->vfs_flag |= VFS_XATTR;
#endif
		vfs_clearmntopt(zfsvfs->z_vfs, MNTOPT_NOXATTR);
		vfs_setmntopt(zfsvfs->z_vfs, MNTOPT_XATTR, NULL, 0);
	} else {
		/* XXX locking on vfs_flag? */
#ifdef TODO
		zfsvfs->z_vfs->vfs_flag &= ~VFS_XATTR;
#endif
		vfs_clearmntopt(zfsvfs->z_vfs, MNTOPT_XATTR);
		vfs_setmntopt(zfsvfs->z_vfs, MNTOPT_NOXATTR, NULL, 0);
	}
}