#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * z_vfs; } ;
typedef  TYPE_1__ zfsvfs_t ;
typedef  int /*<<< orphan*/  vfs_t ;
struct TYPE_8__ {int /*<<< orphan*/  os_user_ptr_lock; } ;
typedef  TYPE_2__ objset_t ;

/* Variables and functions */
 scalar_t__ DMU_OST_ZFS ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ESRCH ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 TYPE_1__* dmu_objset_get_user (TYPE_2__*) ; 
 scalar_t__ dmu_objset_type (TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfs_ref (int /*<<< orphan*/ *) ; 

int
getzfsvfs_impl(objset_t *os, vfs_t **vfsp)
{
	zfsvfs_t *zfvp;
	int error = 0;

	if (dmu_objset_type(os) != DMU_OST_ZFS) {
		return (SET_ERROR(EINVAL));
	}

	mutex_enter(&os->os_user_ptr_lock);
	zfvp = dmu_objset_get_user(os);
	if (zfvp) {
		*vfsp = zfvp->z_vfs;
		vfs_ref(zfvp->z_vfs);
	} else {
		error = SET_ERROR(ESRCH);
	}
	mutex_exit(&os->os_user_ptr_lock);
	return (error);
}