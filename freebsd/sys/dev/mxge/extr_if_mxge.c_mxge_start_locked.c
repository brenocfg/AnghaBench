#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ mask; scalar_t__ req; scalar_t__ done; scalar_t__ max_desc; int /*<<< orphan*/  stall; } ;
struct mxge_slice_state {TYPE_1__ tx; TYPE_2__* sc; } ;
struct mbuf {int dummy; } ;
struct ifnet {int if_drv_flags; int /*<<< orphan*/  if_snd; } ;
typedef  TYPE_1__ mxge_tx_ring_t ;
struct TYPE_4__ {struct ifnet* ifp; } ;
typedef  TYPE_2__ mxge_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_MTAP (struct ifnet*,struct mbuf*) ; 
 int IFF_DRV_OACTIVE ; 
 int /*<<< orphan*/  IFQ_DRV_DEQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  mxge_encap (struct mxge_slice_state*,struct mbuf*) ; 

__attribute__((used)) static inline void
mxge_start_locked(struct mxge_slice_state *ss)
{
	mxge_softc_t *sc;
	struct mbuf *m;
	struct ifnet *ifp;
	mxge_tx_ring_t *tx;

	sc = ss->sc;
	ifp = sc->ifp;
	tx = &ss->tx;
	while ((tx->mask - (tx->req - tx->done)) > tx->max_desc) {
		IFQ_DRV_DEQUEUE(&ifp->if_snd, m);
		if (m == NULL) {
			return;
		}
		/* let BPF see it */
		BPF_MTAP(ifp, m);

		/* give it to the nic */
		mxge_encap(ss, m);
	}
	/* ran out of transmit slots */
	if ((sc->ifp->if_drv_flags & IFF_DRV_OACTIVE) == 0) {
		sc->ifp->if_drv_flags |= IFF_DRV_OACTIVE;
		tx->stall++;
	}
}