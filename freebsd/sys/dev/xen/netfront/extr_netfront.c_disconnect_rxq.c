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
struct netfront_rxq {scalar_t__ xen_intr_handle; int /*<<< orphan*/  ring_ref; int /*<<< orphan*/  gref_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  gnttab_end_foreign_access (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gnttab_free_grant_references (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xn_release_rx_bufs (struct netfront_rxq*) ; 

__attribute__((used)) static void
disconnect_rxq(struct netfront_rxq *rxq)
{

	xn_release_rx_bufs(rxq);
	gnttab_free_grant_references(rxq->gref_head);
	gnttab_end_foreign_access(rxq->ring_ref, NULL);
	/*
	 * No split event channel support at the moment, handle will
	 * be unbound in tx. So no need to call xen_intr_unbind here,
	 * but we do want to reset the handler to 0.
	 */
	rxq->xen_intr_handle = 0;
}