#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  dp_dirty_dirs; } ;
typedef  TYPE_1__ dsl_pool_t ;
struct TYPE_10__ {int /*<<< orphan*/  dd_dbuf; TYPE_1__* dd_pool; } ;
typedef  TYPE_2__ dsl_dir_t ;
struct TYPE_11__ {int /*<<< orphan*/  tx_txg; } ;
typedef  TYPE_3__ dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_buf_add_ref (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  dsl_dir_phys (TYPE_2__*) ; 
 scalar_t__ txg_list_add (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 

void
dsl_dir_dirty(dsl_dir_t *dd, dmu_tx_t *tx)
{
	dsl_pool_t *dp = dd->dd_pool;

	ASSERT(dsl_dir_phys(dd));

	if (txg_list_add(&dp->dp_dirty_dirs, dd, tx->tx_txg)) {
		/* up the hold count until we can be written out */
		dmu_buf_add_ref(dd->dd_dbuf, dd);
	}
}