#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int zv_flags; int /*<<< orphan*/ * zv_objset; int /*<<< orphan*/ * zv_dn; int /*<<< orphan*/ * zv_zilog; } ;
typedef  TYPE_1__ zvol_state_t ;

/* Variables and functions */
 int ZVOL_RDONLY ; 
 int /*<<< orphan*/  dmu_objset_disown (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_objset_ds (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_objset_evict_dbufs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_objset_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dnode_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ dsl_dataset_is_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txg_wait_synced (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zil_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zvol_tag ; 

void
zvol_last_close(zvol_state_t *zv)
{
	zil_close(zv->zv_zilog);
	zv->zv_zilog = NULL;

	dnode_rele(zv->zv_dn, zvol_tag);
	zv->zv_dn = NULL;

	/*
	 * Evict cached data
	 */
	if (dsl_dataset_is_dirty(dmu_objset_ds(zv->zv_objset)) &&
	    !(zv->zv_flags & ZVOL_RDONLY))
		txg_wait_synced(dmu_objset_pool(zv->zv_objset), 0);
	dmu_objset_evict_dbufs(zv->zv_objset);

	dmu_objset_disown(zv->zv_objset, zvol_tag);
	zv->zv_objset = NULL;
}