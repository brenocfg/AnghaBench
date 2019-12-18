#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* os_phys; } ;
typedef  TYPE_2__ objset_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;
typedef  scalar_t__ dmu_objset_type_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_5__ {scalar_t__ os_type; } ;

/* Variables and functions */
 scalar_t__ DMU_OST_ANY ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EROFS ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int dmu_objset_from_ds (int /*<<< orphan*/ *,TYPE_2__**) ; 
 int /*<<< orphan*/  dsl_dataset_disown (int /*<<< orphan*/ *,void*) ; 
 scalar_t__ dsl_dataset_is_snapshot (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dmu_objset_own_impl(dsl_dataset_t *ds, dmu_objset_type_t type,
    boolean_t readonly, void *tag, objset_t **osp)
{
	int err;

	err = dmu_objset_from_ds(ds, osp);
	if (err != 0) {
		dsl_dataset_disown(ds, tag);
	} else if (type != DMU_OST_ANY && type != (*osp)->os_phys->os_type) {
		dsl_dataset_disown(ds, tag);
		return (SET_ERROR(EINVAL));
	} else if (!readonly && dsl_dataset_is_snapshot(ds)) {
		dsl_dataset_disown(ds, tag);
		return (SET_ERROR(EROFS));
	}
	return (err);
}