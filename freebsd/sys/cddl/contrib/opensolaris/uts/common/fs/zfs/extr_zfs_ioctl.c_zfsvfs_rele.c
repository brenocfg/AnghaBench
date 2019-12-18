#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  z_os; scalar_t__ z_vfs; int /*<<< orphan*/  z_teardown_lock; } ;
typedef  TYPE_1__ zfsvfs_t ;

/* Variables and functions */
 int /*<<< orphan*/  VFS_RELE (scalar_t__) ; 
 int /*<<< orphan*/  dmu_objset_disown (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  rrm_exit (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  vfs_unbusy (scalar_t__) ; 
 int /*<<< orphan*/  zfsvfs_free (TYPE_1__*) ; 

__attribute__((used)) static void
zfsvfs_rele(zfsvfs_t *zfsvfs, void *tag)
{
	rrm_exit(&zfsvfs->z_teardown_lock, tag);

	if (zfsvfs->z_vfs) {
#ifdef illumos
		VFS_RELE(zfsvfs->z_vfs);
#else
		vfs_unbusy(zfsvfs->z_vfs);
#endif
	} else {
		dmu_objset_disown(zfsvfs->z_os, zfsvfs);
		zfsvfs_free(zfsvfs);
	}
}