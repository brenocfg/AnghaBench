#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_8__ {scalar_t__ pkt_done; int done; int mask; int req; int* send_stop; int /*<<< orphan*/  mtx; int /*<<< orphan*/  deactivate; scalar_t__ queue_active; int /*<<< orphan*/  wake; TYPE_2__* info; int /*<<< orphan*/  dmat; } ;
struct mxge_slice_state {int if_drv_flags; TYPE_4__ tx; TYPE_3__* sc; int /*<<< orphan*/  opackets; int /*<<< orphan*/  omcasts; int /*<<< orphan*/  obytes; } ;
struct TYPE_5__ {scalar_t__ len; } ;
struct mbuf {int m_flags; TYPE_1__ m_pkthdr; } ;
struct ifnet {int if_drv_flags; } ;
typedef  TYPE_4__ mxge_tx_ring_t ;
typedef  int /*<<< orphan*/  bus_dmamap_t ;
struct TYPE_7__ {int num_slices; struct ifnet* ifp; } ;
struct TYPE_6__ {scalar_t__ flag; int /*<<< orphan*/  map; struct mbuf* m; } ;

/* Variables and functions */
 int IFF_DRV_OACTIVE ; 
 int M_MCAST ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mxge_start_locked (struct mxge_slice_state*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline void
mxge_tx_done(struct mxge_slice_state *ss, uint32_t mcp_idx)
{
	struct ifnet *ifp;
	mxge_tx_ring_t *tx;
	struct mbuf *m;
	bus_dmamap_t map;
	int idx;
	int *flags;

	tx = &ss->tx;
	ifp = ss->sc->ifp;
	while (tx->pkt_done != mcp_idx) {
		idx = tx->done & tx->mask;
		tx->done++;
		m = tx->info[idx].m;
		/* mbuf and DMA map only attached to the first
		   segment per-mbuf */
		if (m != NULL) {
			ss->obytes += m->m_pkthdr.len;
			if (m->m_flags & M_MCAST)
				ss->omcasts++;
			ss->opackets++;
			tx->info[idx].m = NULL;
			map = tx->info[idx].map;
			bus_dmamap_unload(tx->dmat, map);
			m_freem(m);
		}
		if (tx->info[idx].flag) {
			tx->info[idx].flag = 0;
			tx->pkt_done++;
		}
	}
	
	/* If we have space, clear IFF_OACTIVE to tell the stack that
	   its OK to send packets */
#ifdef IFNET_BUF_RING
	flags = &ss->if_drv_flags;
#else
	flags = &ifp->if_drv_flags;
#endif
	mtx_lock(&ss->tx.mtx);
	if ((*flags) & IFF_DRV_OACTIVE &&
	    tx->req - tx->done < (tx->mask + 1)/4) {
		*(flags) &= ~IFF_DRV_OACTIVE;
		ss->tx.wake++;
		mxge_start_locked(ss);
	}
#ifdef IFNET_BUF_RING
	if ((ss->sc->num_slices > 1) && (tx->req == tx->done)) {
		/* let the NIC stop polling this queue, since there
		 * are no more transmits pending */
		if (tx->req == tx->done) {
			*tx->send_stop = 1;
			tx->queue_active = 0;
			tx->deactivate++;
			wmb();
		}
	}
#endif
	mtx_unlock(&ss->tx.mtx);

}