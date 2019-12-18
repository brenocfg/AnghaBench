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
struct netfront_txq {int full; int /*<<< orphan*/  ring; int /*<<< orphan*/  xen_intr_handle; struct buf_ring* br; struct netfront_info* info; } ;
struct netfront_info {struct ifnet* xn_ifp; } ;
struct mbuf {int dummy; } ;
struct ifnet {int if_drv_flags; } ;
struct buf_ring {int dummy; } ;

/* Variables and functions */
 int IFF_DRV_RUNNING ; 
 scalar_t__ RING_FULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RING_PUSH_REQUESTS_AND_CHECK_NOTIFY (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  XN_TX_LOCK_ASSERT (struct netfront_txq*) ; 
 int /*<<< orphan*/  drbr_advance (struct ifnet*,struct buf_ring*) ; 
 int drbr_enqueue (struct ifnet*,struct buf_ring*,struct mbuf*) ; 
 struct mbuf* drbr_peek (struct ifnet*,struct buf_ring*) ; 
 int /*<<< orphan*/  drbr_putback (struct ifnet*,struct buf_ring*,struct mbuf*) ; 
 int /*<<< orphan*/  netfront_carrier_ok (struct netfront_info*) ; 
 int /*<<< orphan*/  xen_intr_signal (int /*<<< orphan*/ ) ; 
 int xn_assemble_tx_request (struct netfront_txq*,struct mbuf*) ; 
 int /*<<< orphan*/  xn_tx_slot_available (struct netfront_txq*) ; 

__attribute__((used)) static int
xn_txq_mq_start_locked(struct netfront_txq *txq, struct mbuf *m)
{
	struct netfront_info *np;
	struct ifnet *ifp;
	struct buf_ring *br;
	int error, notify;

	np = txq->info;
	br = txq->br;
	ifp = np->xn_ifp;
	error = 0;

	XN_TX_LOCK_ASSERT(txq);

	if ((ifp->if_drv_flags & IFF_DRV_RUNNING) == 0 ||
	    !netfront_carrier_ok(np)) {
		if (m != NULL)
			error = drbr_enqueue(ifp, br, m);
		return (error);
	}

	if (m != NULL) {
		error = drbr_enqueue(ifp, br, m);
		if (error != 0)
			return (error);
	}

	while ((m = drbr_peek(ifp, br)) != NULL) {
		if (!xn_tx_slot_available(txq)) {
			drbr_putback(ifp, br, m);
			break;
		}

		error = xn_assemble_tx_request(txq, m);
		/* xn_assemble_tx_request always consumes the mbuf*/
		if (error != 0) {
			drbr_advance(ifp, br);
			break;
		}

		RING_PUSH_REQUESTS_AND_CHECK_NOTIFY(&txq->ring, notify);
		if (notify)
			xen_intr_signal(txq->xen_intr_handle);

		drbr_advance(ifp, br);
	}

	if (RING_FULL(&txq->ring))
		txq->full = true;

	return (0);
}