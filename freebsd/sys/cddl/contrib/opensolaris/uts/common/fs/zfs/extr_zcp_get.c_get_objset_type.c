#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_type_t ;
struct TYPE_8__ {TYPE_1__* os_phys; } ;
typedef  TYPE_2__ objset_t ;
struct TYPE_9__ {scalar_t__ ds_is_snapshot; } ;
typedef  TYPE_3__ dsl_dataset_t ;
struct TYPE_7__ {int os_type; } ;

/* Variables and functions */
#define  DMU_OST_ZFS 129 
#define  DMU_OST_ZVOL 128 
 int EINVAL ; 
 int /*<<< orphan*/  ZFS_TYPE_FILESYSTEM ; 
 int /*<<< orphan*/  ZFS_TYPE_SNAPSHOT ; 
 int /*<<< orphan*/  ZFS_TYPE_VOLUME ; 
 int dmu_objset_from_ds (TYPE_3__*,TYPE_2__**) ; 

__attribute__((used)) static int
get_objset_type(dsl_dataset_t *ds, zfs_type_t *type)
{
	int error;
	objset_t *os;
	error = dmu_objset_from_ds(ds, &os);
	if (error != 0)
		return (error);
	if (ds->ds_is_snapshot) {
		*type = ZFS_TYPE_SNAPSHOT;
	} else {
		switch (os->os_phys->os_type) {
		case DMU_OST_ZFS:
			*type = ZFS_TYPE_FILESYSTEM;
			break;
		case DMU_OST_ZVOL:
			*type = ZFS_TYPE_VOLUME;
			break;
		default:
			return (EINVAL);
		}
	}
	return (0);
}