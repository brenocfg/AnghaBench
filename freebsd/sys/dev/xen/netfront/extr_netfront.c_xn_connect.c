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
typedef  scalar_t__ u_int ;
struct netfront_txq {int dummy; } ;
struct netfront_rxq {int dummy; } ;
struct netfront_info {int num_queues; struct netfront_rxq* rxq; struct netfront_txq* txq; int /*<<< orphan*/  xbdev; } ;

/* Variables and functions */
 int EPROTONOSUPPORT ; 
 int /*<<< orphan*/  XST_NIL ; 
 int /*<<< orphan*/  netfront_carrier_on (struct netfront_info*) ; 
 int talk_to_backend (int /*<<< orphan*/ ,struct netfront_info*) ; 
 int /*<<< orphan*/  wakeup (struct netfront_info*) ; 
 int /*<<< orphan*/  xenbus_get_otherend_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xn_configure_features (struct netfront_info*) ; 
 int /*<<< orphan*/  xn_query_features (struct netfront_info*) ; 
 int /*<<< orphan*/  xn_rebuild_rx_bufs (struct netfront_rxq*) ; 
 int /*<<< orphan*/  xn_release_tx_bufs (struct netfront_txq*) ; 
 int xs_scanf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,char*,scalar_t__*) ; 

__attribute__((used)) static int
xn_connect(struct netfront_info *np)
{
	int i, error;
	u_int feature_rx_copy;
	struct netfront_rxq *rxq;
	struct netfront_txq *txq;

	error = xs_scanf(XST_NIL, xenbus_get_otherend_path(np->xbdev),
	    "feature-rx-copy", NULL, "%u", &feature_rx_copy);
	if (error != 0)
		feature_rx_copy = 0;

	/* We only support rx copy. */
	if (!feature_rx_copy)
		return (EPROTONOSUPPORT);

	/* Recovery procedure: */
	error = talk_to_backend(np->xbdev, np);
	if (error != 0)
		return (error);

	/* Step 1: Reinitialise variables. */
	xn_query_features(np);
	xn_configure_features(np);

	/* Step 2: Release TX buffer */
	for (i = 0; i < np->num_queues; i++) {
		txq = &np->txq[i];
		xn_release_tx_bufs(txq);
	}

	/* Step 3: Rebuild the RX buffer freelist and the RX ring itself. */
	for (i = 0; i < np->num_queues; i++) {
		rxq = &np->rxq[i];
		xn_rebuild_rx_bufs(rxq);
	}

	/* Step 4: All public and private state should now be sane.  Get
	 * ready to start sending and receiving packets and give the driver
	 * domain a kick because we've probably just requeued some
	 * packets.
	 */
	netfront_carrier_on(np);
	wakeup(np);

	return (0);
}