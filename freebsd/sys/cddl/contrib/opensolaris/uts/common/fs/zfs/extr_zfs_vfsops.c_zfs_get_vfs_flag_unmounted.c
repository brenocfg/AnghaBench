#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* z_vfs; } ;
typedef  TYPE_2__ zfsvfs_t ;
struct TYPE_10__ {int /*<<< orphan*/  os_user_ptr_lock; } ;
typedef  TYPE_3__ objset_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_8__ {int mnt_kern_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 scalar_t__ DMU_OST_ZFS ; 
 int MNTK_UNMOUNT ; 
 TYPE_2__* dmu_objset_get_user (TYPE_3__*) ; 
 scalar_t__ dmu_objset_type (TYPE_3__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

boolean_t
zfs_get_vfs_flag_unmounted(objset_t *os)
{
	zfsvfs_t *zfvp;
	boolean_t unmounted = B_FALSE;

	ASSERT(dmu_objset_type(os) == DMU_OST_ZFS);

	mutex_enter(&os->os_user_ptr_lock);
	zfvp = dmu_objset_get_user(os);
	if (zfvp != NULL && zfvp->z_vfs != NULL &&
	    (zfvp->z_vfs->mnt_kern_flag & MNTK_UNMOUNT))
		unmounted = B_TRUE;
	mutex_exit(&os->os_user_ptr_lock);

	return (unmounted);
}