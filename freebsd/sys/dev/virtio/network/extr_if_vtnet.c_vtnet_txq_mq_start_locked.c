#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  vtxs_rescheduled; } ;
struct vtnet_txq {int /*<<< orphan*/  vtntx_intrtask; int /*<<< orphan*/  vtntx_tq; TYPE_1__ vtntx_stats; struct buf_ring* vtntx_br; struct virtqueue* vtntx_vq; struct vtnet_softc* vtntx_sc; } ;
struct vtnet_softc {scalar_t__ vtnet_link_active; struct ifnet* vtnet_ifp; } ;
struct virtqueue {int dummy; } ;
struct mbuf {int dummy; } ;
struct ifnet {int if_drv_flags; } ;
struct buf_ring {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHER_BPF_MTAP (struct ifnet*,struct mbuf*) ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  VTNET_NOTIFY_RETRIES ; 
 int /*<<< orphan*/  VTNET_TXQ_LOCK_ASSERT (struct vtnet_txq*) ; 
 int /*<<< orphan*/  drbr_advance (struct ifnet*,struct buf_ring*) ; 
 int drbr_enqueue (struct ifnet*,struct buf_ring*,struct mbuf*) ; 
 struct mbuf* drbr_peek (struct ifnet*,struct buf_ring*) ; 
 int /*<<< orphan*/  drbr_putback (struct ifnet*,struct buf_ring*,struct mbuf*) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ virtqueue_full (struct virtqueue*) ; 
 scalar_t__ vtnet_txq_encap (struct vtnet_txq*,struct mbuf**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtnet_txq_eof (struct vtnet_txq*) ; 
 scalar_t__ vtnet_txq_notify (struct vtnet_txq*) ; 

__attribute__((used)) static int
vtnet_txq_mq_start_locked(struct vtnet_txq *txq, struct mbuf *m)
{
	struct vtnet_softc *sc;
	struct virtqueue *vq;
	struct buf_ring *br;
	struct ifnet *ifp;
	int enq, tries, error;

	sc = txq->vtntx_sc;
	vq = txq->vtntx_vq;
	br = txq->vtntx_br;
	ifp = sc->vtnet_ifp;
	tries = 0;
	error = 0;

	VTNET_TXQ_LOCK_ASSERT(txq);

	if ((ifp->if_drv_flags & IFF_DRV_RUNNING) == 0 ||
	    sc->vtnet_link_active == 0) {
		if (m != NULL)
			error = drbr_enqueue(ifp, br, m);
		return (error);
	}

	if (m != NULL) {
		error = drbr_enqueue(ifp, br, m);
		if (error)
			return (error);
	}

	vtnet_txq_eof(txq);

again:
	enq = 0;

	while ((m = drbr_peek(ifp, br)) != NULL) {
		if (virtqueue_full(vq)) {
			drbr_putback(ifp, br, m);
			break;
		}

		if (vtnet_txq_encap(txq, &m, M_NOWAIT) != 0) {
			if (m != NULL)
				drbr_putback(ifp, br, m);
			else
				drbr_advance(ifp, br);
			break;
		}
		drbr_advance(ifp, br);

		enq++;
		ETHER_BPF_MTAP(ifp, m);
	}

	if (enq > 0 && vtnet_txq_notify(txq) != 0) {
		if (tries++ < VTNET_NOTIFY_RETRIES)
			goto again;

		txq->vtntx_stats.vtxs_rescheduled++;
		taskqueue_enqueue(txq->vtntx_tq, &txq->vtntx_intrtask);
	}

	return (0);
}