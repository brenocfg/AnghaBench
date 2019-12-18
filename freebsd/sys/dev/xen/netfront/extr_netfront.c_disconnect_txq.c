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
struct netfront_txq {int /*<<< orphan*/  xen_intr_handle; int /*<<< orphan*/  ring_ref; int /*<<< orphan*/  gref_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  gnttab_end_foreign_access (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gnttab_free_grant_references (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_intr_unbind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xn_release_tx_bufs (struct netfront_txq*) ; 

__attribute__((used)) static void
disconnect_txq(struct netfront_txq *txq)
{

	xn_release_tx_bufs(txq);
	gnttab_free_grant_references(txq->gref_head);
	gnttab_end_foreign_access(txq->ring_ref, NULL);
	xen_intr_unbind(&txq->xen_intr_handle);
}