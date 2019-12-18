#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int* dd_space_towrite; int /*<<< orphan*/  dd_dbuf; int /*<<< orphan*/  dd_lock; int /*<<< orphan*/ * dd_tempreserved; } ;
typedef  TYPE_1__ dsl_dir_t ;
struct TYPE_9__ {size_t tx_txg; } ;
typedef  TYPE_2__ dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSERT0 (int /*<<< orphan*/ ) ; 
 size_t TXG_MASK ; 
 int /*<<< orphan*/  dmu_buf_rele (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  dmu_tx_is_syncing (TYPE_2__*) ; 
 int /*<<< orphan*/  dprintf_dd (TYPE_1__*,char*,size_t,int) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

void
dsl_dir_sync(dsl_dir_t *dd, dmu_tx_t *tx)
{
	ASSERT(dmu_tx_is_syncing(tx));

	mutex_enter(&dd->dd_lock);
	ASSERT0(dd->dd_tempreserved[tx->tx_txg&TXG_MASK]);
	dprintf_dd(dd, "txg=%llu towrite=%lluK\n", tx->tx_txg,
	    dd->dd_space_towrite[tx->tx_txg&TXG_MASK] / 1024);
	dd->dd_space_towrite[tx->tx_txg&TXG_MASK] = 0;
	mutex_exit(&dd->dd_lock);

	/* release the hold from dsl_dir_dirty */
	dmu_buf_rele(dd->dd_dbuf, dd);
}