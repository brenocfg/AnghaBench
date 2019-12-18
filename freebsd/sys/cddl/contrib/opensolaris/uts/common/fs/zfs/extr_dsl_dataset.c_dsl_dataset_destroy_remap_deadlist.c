#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
struct TYPE_11__ {int /*<<< orphan*/  dl_object; } ;
struct TYPE_10__ {TYPE_4__ ds_remap_deadlist; TYPE_2__* ds_dir; } ;
typedef  TYPE_3__ dsl_dataset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_9__ {TYPE_1__* dd_pool; } ;
struct TYPE_8__ {int /*<<< orphan*/ * dp_spa; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPA_FEATURE_OBSOLETE_COUNTS ; 
 int /*<<< orphan*/  dmu_tx_is_syncing (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dataset_remap_deadlist_exists (TYPE_3__*) ; 
 int /*<<< orphan*/  dsl_dataset_unset_remap_deadlist_object (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_deadlist_close (TYPE_4__*) ; 
 int /*<<< orphan*/  dsl_deadlist_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_feature_decr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_meta_objset (int /*<<< orphan*/ *) ; 

void
dsl_dataset_destroy_remap_deadlist(dsl_dataset_t *ds, dmu_tx_t *tx)
{
	uint64_t remap_deadlist_object;
	spa_t *spa = ds->ds_dir->dd_pool->dp_spa;

	ASSERT(dmu_tx_is_syncing(tx));
	ASSERT(dsl_dataset_remap_deadlist_exists(ds));

	remap_deadlist_object = ds->ds_remap_deadlist.dl_object;
	dsl_deadlist_close(&ds->ds_remap_deadlist);
	dsl_deadlist_free(spa_meta_objset(spa), remap_deadlist_object, tx);
	dsl_dataset_unset_remap_deadlist_object(ds, tx);
	spa_feature_decr(spa, SPA_FEATURE_OBSOLETE_COUNTS, tx);
}