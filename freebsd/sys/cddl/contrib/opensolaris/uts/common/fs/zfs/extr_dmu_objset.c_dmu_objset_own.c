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
typedef  int /*<<< orphan*/  dmu_objset_type_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 int dmu_objset_own_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ **) ; 
 int dsl_dataset_own (int /*<<< orphan*/ *,char const*,void*,int /*<<< orphan*/ **) ; 
 int dsl_pool_hold (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_pool_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
dmu_objset_own(const char *name, dmu_objset_type_t type,
    boolean_t readonly, void *tag, objset_t **osp)
{
	dsl_pool_t *dp;
	dsl_dataset_t *ds;
	int err;

	err = dsl_pool_hold(name, FTAG, &dp);
	if (err != 0)
		return (err);
	err = dsl_dataset_own(dp, name, tag, &ds);
	if (err != 0) {
		dsl_pool_rele(dp, FTAG);
		return (err);
	}
	err = dmu_objset_own_impl(ds, type, readonly, tag, osp);
	dsl_pool_rele(dp, FTAG);

	return (err);
}