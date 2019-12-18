#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dsl_pool_t ;
struct TYPE_11__ {TYPE_7__* ds_dir; scalar_t__ ds_is_snapshot; } ;
typedef  TYPE_1__ dsl_dataset_t ;
struct TYPE_12__ {char* dds_origin; scalar_t__ dds_num_clones; int /*<<< orphan*/  dds_is_snapshot; int /*<<< orphan*/  dds_guid; int /*<<< orphan*/  dds_inconsistent; int /*<<< orphan*/  dds_creation_txg; } ;
typedef  TYPE_2__ dmu_objset_stats_t ;
struct TYPE_13__ {int /*<<< orphan*/ * dd_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  dsl_dir_get_origin (TYPE_7__*,char*) ; 
 scalar_t__ dsl_dir_is_clone (TYPE_7__*) ; 
 int /*<<< orphan*/  dsl_get_creationtxg (TYPE_1__*) ; 
 int /*<<< orphan*/  dsl_get_guid (TYPE_1__*) ; 
 int /*<<< orphan*/  dsl_get_inconsistent (TYPE_1__*) ; 
 scalar_t__ dsl_get_numclones (TYPE_1__*) ; 
 int /*<<< orphan*/  dsl_pool_config_held (int /*<<< orphan*/ *) ; 

void
dsl_dataset_fast_stat(dsl_dataset_t *ds, dmu_objset_stats_t *stat)
{
	dsl_pool_t *dp = ds->ds_dir->dd_pool;
	ASSERT(dsl_pool_config_held(dp));

	stat->dds_creation_txg = dsl_get_creationtxg(ds);
	stat->dds_inconsistent = dsl_get_inconsistent(ds);
	stat->dds_guid = dsl_get_guid(ds);
	stat->dds_origin[0] = '\0';
	if (ds->ds_is_snapshot) {
		stat->dds_is_snapshot = B_TRUE;
		stat->dds_num_clones = dsl_get_numclones(ds);
	} else {
		stat->dds_is_snapshot = B_FALSE;
		stat->dds_num_clones = 0;

		if (dsl_dir_is_clone(ds->ds_dir)) {
			dsl_dir_get_origin(ds->ds_dir, stat->dds_origin);
		}
	}
}