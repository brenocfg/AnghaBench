#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  zl_dirty_max_txg; int /*<<< orphan*/  zl_spa; int /*<<< orphan*/  zl_os; TYPE_2__* zl_dmu_pool; } ;
typedef  TYPE_1__ zilog_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_9__ {int /*<<< orphan*/  dp_dirty_zilogs; } ;
typedef  TYPE_2__ dsl_pool_t ;
struct TYPE_10__ {int /*<<< orphan*/  ds_dbuf; scalar_t__ ds_is_snapshot; } ;
typedef  TYPE_3__ dsl_dataset_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_buf_add_ref (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_3__* dmu_objset_ds (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  spa_writeable (int /*<<< orphan*/ ) ; 
 scalar_t__ txg_list_add (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 

void
zilog_dirty(zilog_t *zilog, uint64_t txg)
{
	dsl_pool_t *dp = zilog->zl_dmu_pool;
	dsl_dataset_t *ds = dmu_objset_ds(zilog->zl_os);

	ASSERT(spa_writeable(zilog->zl_spa));

	if (ds->ds_is_snapshot)
		panic("dirtying snapshot!");

	if (txg_list_add(&dp->dp_dirty_zilogs, zilog, txg)) {
		/* up the hold count until we can be written out */
		dmu_buf_add_ref(ds->ds_dbuf, zilog);

		zilog->zl_dirty_max_txg = MAX(txg, zilog->zl_dirty_max_txg);
	}
}