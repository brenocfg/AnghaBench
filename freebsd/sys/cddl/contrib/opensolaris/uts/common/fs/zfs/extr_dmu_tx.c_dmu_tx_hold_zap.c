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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {int /*<<< orphan*/  tx_objset; int /*<<< orphan*/  tx_txg; } ;
typedef  TYPE_1__ dmu_tx_t ;
typedef  int /*<<< orphan*/  dmu_tx_hold_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THT_ZAP ; 
 int /*<<< orphan*/ * dmu_tx_hold_object_impl (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,uintptr_t) ; 
 int /*<<< orphan*/  dmu_tx_hold_zap_impl (int /*<<< orphan*/ *,char const*) ; 

void
dmu_tx_hold_zap(dmu_tx_t *tx, uint64_t object, int add, const char *name)
{
	dmu_tx_hold_t *txh;

	ASSERT0(tx->tx_txg);

	txh = dmu_tx_hold_object_impl(tx, tx->tx_objset,
	    object, THT_ZAP, add, (uintptr_t)name);
	if (txh != NULL)
		dmu_tx_hold_zap_impl(txh, name);
}