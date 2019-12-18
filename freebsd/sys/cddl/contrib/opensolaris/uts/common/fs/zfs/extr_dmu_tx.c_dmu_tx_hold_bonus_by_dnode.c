#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dnode_t ;
struct TYPE_4__ {int /*<<< orphan*/  tx_txg; } ;
typedef  TYPE_1__ dmu_tx_t ;
typedef  int /*<<< orphan*/  dmu_tx_hold_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THT_BONUS ; 
 int /*<<< orphan*/  dmu_tx_count_dnode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dmu_tx_hold_dnode_impl (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
dmu_tx_hold_bonus_by_dnode(dmu_tx_t *tx, dnode_t *dn)
{
	dmu_tx_hold_t *txh;

	ASSERT0(tx->tx_txg);

	txh = dmu_tx_hold_dnode_impl(tx, dn, THT_BONUS, 0, 0);
	if (txh)
		dmu_tx_count_dnode(txh);
}