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
struct netfront_txq {int /*<<< orphan*/  xen_intr_handle; } ;
struct netfront_rxq {int dummy; } ;
struct netfront_info {int num_queues; struct netfront_rxq* rxq; struct netfront_txq* txq; } ;

/* Variables and functions */
 int /*<<< orphan*/  XN_RX_LOCK (struct netfront_rxq*) ; 
 int /*<<< orphan*/  XN_RX_UNLOCK (struct netfront_rxq*) ; 
 int /*<<< orphan*/  XN_TX_LOCK (struct netfront_txq*) ; 
 int /*<<< orphan*/  XN_TX_UNLOCK (struct netfront_txq*) ; 
 int /*<<< orphan*/  xen_intr_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xn_alloc_rx_buffers (struct netfront_rxq*) ; 
 int /*<<< orphan*/  xn_txeof (struct netfront_txq*) ; 

__attribute__((used)) static void
xn_kick_rings(struct netfront_info *np)
{
	struct netfront_rxq *rxq;
	struct netfront_txq *txq;
	int i;

	for (i = 0; i < np->num_queues; i++) {
		txq = &np->txq[i];
		rxq = &np->rxq[i];
		xen_intr_signal(txq->xen_intr_handle);
		XN_TX_LOCK(txq);
		xn_txeof(txq);
		XN_TX_UNLOCK(txq);
		XN_RX_LOCK(rxq);
		xn_alloc_rx_buffers(rxq);
		XN_RX_UNLOCK(rxq);
	}
}