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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  dsl_pool_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;
typedef  int /*<<< orphan*/  dmu_objset_type_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int dmu_objset_own_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ **) ; 
 int dsl_dataset_own_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ **) ; 

int
dmu_objset_own_obj(dsl_pool_t *dp, uint64_t obj, dmu_objset_type_t type,
    boolean_t readonly, void *tag, objset_t **osp)
{
	dsl_dataset_t *ds;
	int err;

	err = dsl_dataset_own_obj(dp, obj, tag, &ds);
	if (err != 0)
		return (err);

	return (dmu_objset_own_impl(ds, type, readonly, tag, osp));
}