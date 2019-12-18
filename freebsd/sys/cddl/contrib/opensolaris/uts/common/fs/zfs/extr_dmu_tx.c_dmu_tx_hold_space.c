#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_6__ {scalar_t__ tx_txg; int /*<<< orphan*/  tx_objset; } ;
typedef  TYPE_1__ dmu_tx_t ;
struct TYPE_7__ {int /*<<< orphan*/  txh_space_towrite; } ;
typedef  TYPE_2__ dmu_tx_hold_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DMU_NEW_OBJECT ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  THT_SPACE ; 
 TYPE_2__* dmu_tx_hold_object_impl (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_refcount_add_many (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
dmu_tx_hold_space(dmu_tx_t *tx, uint64_t space)
{
	dmu_tx_hold_t *txh;
	ASSERT(tx->tx_txg == 0);

	txh = dmu_tx_hold_object_impl(tx, tx->tx_objset,
	    DMU_NEW_OBJECT, THT_SPACE, space, 0);

	(void) zfs_refcount_add_many(&txh->txh_space_towrite, space, FTAG);
}