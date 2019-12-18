#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * zv_objset; } ;
typedef  TYPE_1__ zvol_state_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_7__ {int /*<<< orphan*/  doi_data_block_size; } ;
typedef  TYPE_2__ dmu_object_info_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int /*<<< orphan*/  DMU_OST_ZVOL ; 
 int /*<<< orphan*/  EROFS ; 
 int /*<<< orphan*/  FTAG ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZFS_PROP_READONLY ; 
 int /*<<< orphan*/  ZVOL_OBJ ; 
 int dmu_object_info (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  dmu_objset_disown (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dmu_objset_own (char const*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int dsl_prop_get_integer (char const*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_prop_to_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfsdev_state_lock ; 
 int zvol_check_volsize (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* zvol_minor_lookup (char const*) ; 
 int zvol_update_live_volsize (TYPE_1__*,scalar_t__) ; 
 int zvol_update_volsize (int /*<<< orphan*/ *,scalar_t__) ; 

int
zvol_set_volsize(const char *name, uint64_t volsize)
{
	zvol_state_t *zv = NULL;
	objset_t *os;
	int error;
	dmu_object_info_t doi;
	uint64_t readonly;
	boolean_t owned = B_FALSE;

	error = dsl_prop_get_integer(name,
	    zfs_prop_to_name(ZFS_PROP_READONLY), &readonly, NULL);
	if (error != 0)
		return (error);
	if (readonly)
		return (SET_ERROR(EROFS));

	mutex_enter(&zfsdev_state_lock);
	zv = zvol_minor_lookup(name);

	if (zv == NULL || zv->zv_objset == NULL) {
		if ((error = dmu_objset_own(name, DMU_OST_ZVOL, B_FALSE,
		    FTAG, &os)) != 0) {
			mutex_exit(&zfsdev_state_lock);
			return (error);
		}
		owned = B_TRUE;
		if (zv != NULL)
			zv->zv_objset = os;
	} else {
		os = zv->zv_objset;
	}

	if ((error = dmu_object_info(os, ZVOL_OBJ, &doi)) != 0 ||
	    (error = zvol_check_volsize(volsize, doi.doi_data_block_size)) != 0)
		goto out;

	error = zvol_update_volsize(os, volsize);

	if (error == 0 && zv != NULL)
		error = zvol_update_live_volsize(zv, volsize);
out:
	if (owned) {
		dmu_objset_disown(os, FTAG);
		if (zv != NULL)
			zv->zv_objset = NULL;
	}
	mutex_exit(&zfsdev_state_lock);
	return (error);
}