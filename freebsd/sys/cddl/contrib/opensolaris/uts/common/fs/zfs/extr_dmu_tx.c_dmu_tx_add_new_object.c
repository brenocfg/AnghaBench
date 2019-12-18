#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  dnode_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  THT_NEWOBJECT ; 
 int /*<<< orphan*/  dmu_tx_hold_dnode_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_tx_is_syncing (int /*<<< orphan*/ *) ; 

void
dmu_tx_add_new_object(dmu_tx_t *tx, dnode_t *dn)
{
	/*
	 * If we're syncing, they can manipulate any object anyhow, and
	 * the hold on the dnode_t can cause problems.
	 */
	if (!dmu_tx_is_syncing(tx))
		(void) dmu_tx_hold_dnode_impl(tx, dn, THT_NEWOBJECT, 0, 0);
}