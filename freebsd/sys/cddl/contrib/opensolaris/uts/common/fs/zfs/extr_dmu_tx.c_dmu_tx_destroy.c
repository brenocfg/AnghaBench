#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dnode_t ;
struct TYPE_8__ {int /*<<< orphan*/  tx_holds; int /*<<< orphan*/  tx_callbacks; int /*<<< orphan*/  txh_memory_tohold; int /*<<< orphan*/  txh_space_towrite; int /*<<< orphan*/ * txh_dnode; } ;
typedef  TYPE_1__ dmu_tx_t ;
typedef  TYPE_1__ dmu_tx_hold_t ;

/* Variables and functions */
 int /*<<< orphan*/  dnode_rele (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  list_destroy (int /*<<< orphan*/ *) ; 
 TYPE_1__* list_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  zfs_refcount_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_refcount_destroy_many (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dmu_tx_destroy(dmu_tx_t *tx)
{
	dmu_tx_hold_t *txh;

	while ((txh = list_head(&tx->tx_holds)) != NULL) {
		dnode_t *dn = txh->txh_dnode;

		list_remove(&tx->tx_holds, txh);
		zfs_refcount_destroy_many(&txh->txh_space_towrite,
		    zfs_refcount_count(&txh->txh_space_towrite));
		zfs_refcount_destroy_many(&txh->txh_memory_tohold,
		    zfs_refcount_count(&txh->txh_memory_tohold));
		kmem_free(txh, sizeof (dmu_tx_hold_t));
		if (dn != NULL)
			dnode_rele(dn, tx);
	}

	list_destroy(&tx->tx_callbacks);
	list_destroy(&tx->tx_holds);
	kmem_free(tx, sizeof (dmu_tx_t));
}