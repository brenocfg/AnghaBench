#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zap_cursor_t ;
struct TYPE_11__ {int /*<<< orphan*/  za_first_integer; } ;
typedef  TYPE_1__ zap_attribute_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_12__ {int /*<<< orphan*/  ds_remap_deadlist; int /*<<< orphan*/  ds_deadlist; TYPE_5__* ds_dir; } ;
typedef  TYPE_2__ dsl_dataset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_15__ {int /*<<< orphan*/ * dp_meta_objset; } ;
struct TYPE_14__ {int /*<<< orphan*/  dd_origin_txg; TYPE_9__* dd_pool; } ;
struct TYPE_13__ {scalar_t__ dd_clones; } ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_dataset_hold_obj (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  dsl_dataset_rele (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ dsl_dataset_remap_deadlist_exists (TYPE_2__*) ; 
 int /*<<< orphan*/  dsl_deadlist_remove_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_4__* dsl_dir_phys (TYPE_5__*) ; 
 int /*<<< orphan*/  zap_cursor_advance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ zap_cursor_retrieve (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void
dsl_dataset_remove_clones_key(dsl_dataset_t *ds, uint64_t mintxg, dmu_tx_t *tx)
{
	objset_t *mos = ds->ds_dir->dd_pool->dp_meta_objset;
	zap_cursor_t zc;
	zap_attribute_t za;

	/*
	 * If it is the old version, dd_clones doesn't exist so we can't
	 * find the clones, but dsl_deadlist_remove_key() is a no-op so it
	 * doesn't matter.
	 */
	if (dsl_dir_phys(ds->ds_dir)->dd_clones == 0)
		return;

	for (zap_cursor_init(&zc, mos, dsl_dir_phys(ds->ds_dir)->dd_clones);
	    zap_cursor_retrieve(&zc, &za) == 0;
	    zap_cursor_advance(&zc)) {
		dsl_dataset_t *clone;

		VERIFY0(dsl_dataset_hold_obj(ds->ds_dir->dd_pool,
		    za.za_first_integer, FTAG, &clone));
		if (clone->ds_dir->dd_origin_txg > mintxg) {
			dsl_deadlist_remove_key(&clone->ds_deadlist,
			    mintxg, tx);
			if (dsl_dataset_remap_deadlist_exists(clone)) {
				dsl_deadlist_remove_key(
				    &clone->ds_remap_deadlist, mintxg, tx);
			}
			dsl_dataset_remove_clones_key(clone, mintxg, tx);
		}
		dsl_dataset_rele(clone, FTAG);
	}
	zap_cursor_fini(&zc);
}