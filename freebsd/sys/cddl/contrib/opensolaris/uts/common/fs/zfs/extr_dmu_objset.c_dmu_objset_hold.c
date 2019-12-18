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
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  dsl_pool_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;

/* Variables and functions */
 int dmu_objset_from_ds (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int dsl_dataset_hold (int /*<<< orphan*/ *,char const*,void*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_dataset_rele (int /*<<< orphan*/ *,void*) ; 
 int dsl_pool_hold (char const*,void*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_pool_rele (int /*<<< orphan*/ *,void*) ; 

int
dmu_objset_hold(const char *name, void *tag, objset_t **osp)
{
	dsl_pool_t *dp;
	dsl_dataset_t *ds;
	int err;

	err = dsl_pool_hold(name, tag, &dp);
	if (err != 0)
		return (err);
	err = dsl_dataset_hold(dp, name, tag, &ds);
	if (err != 0) {
		dsl_pool_rele(dp, tag);
		return (err);
	}

	err = dmu_objset_from_ds(ds, osp);
	if (err != 0) {
		dsl_dataset_rele(ds, tag);
		dsl_pool_rele(dp, tag);
	}

	return (err);
}