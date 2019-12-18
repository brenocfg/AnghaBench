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
typedef  int uint32_t ;
struct mbuf {int dummy; } ;
struct ifnet {int if_drv_flags; int /*<<< orphan*/  if_snd; struct et_softc* if_softc; } ;
struct et_txdesc_ring {int tr_ready_index; scalar_t__ tr_ready_wrap; int /*<<< orphan*/  tr_dmap; int /*<<< orphan*/  tr_dtag; } ;
struct et_txbuf_data {int tbd_used; } ;
struct et_softc {int sc_flags; int watchdog_timer; struct et_txdesc_ring sc_tx_ring; struct et_txbuf_data sc_tx_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct et_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ETHER_BPF_MTAP (struct ifnet*,struct mbuf*) ; 
 int ET_FLAG_LINK ; 
 int ET_FLAG_TXRX_ENABLED ; 
 int /*<<< orphan*/  ET_LOCK_ASSERT (struct et_softc*) ; 
 int ET_NSEG_SPARE ; 
 int ET_TX_NDESC ; 
 int /*<<< orphan*/  ET_TX_READY_POS ; 
 int ET_TX_READY_POS_INDEX_MASK ; 
 int ET_TX_READY_POS_WRAP ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFQ_DRV_DEQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFQ_DRV_PREPEND (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ et_encap (struct et_softc*,struct mbuf**) ; 
 int /*<<< orphan*/  et_txeof (struct et_softc*) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
et_start_locked(struct ifnet *ifp)
{
	struct et_softc *sc;
	struct mbuf *m_head = NULL;
	struct et_txdesc_ring *tx_ring;
	struct et_txbuf_data *tbd;
	uint32_t tx_ready_pos;
	int enq;

	sc = ifp->if_softc;
	ET_LOCK_ASSERT(sc);

	if ((ifp->if_drv_flags & (IFF_DRV_RUNNING | IFF_DRV_OACTIVE)) !=
	    IFF_DRV_RUNNING ||
	    (sc->sc_flags & (ET_FLAG_LINK | ET_FLAG_TXRX_ENABLED)) !=
	    (ET_FLAG_LINK | ET_FLAG_TXRX_ENABLED))
		return;

	/*
	 * Driver does not request TX completion interrupt for every
	 * queued frames to prevent generating excessive interrupts.
	 * This means driver may wait for TX completion interrupt even
	 * though some frames were successfully transmitted.  Reclaiming
	 * transmitted frames will ensure driver see all available
	 * descriptors.
	 */
	tbd = &sc->sc_tx_data;
	if (tbd->tbd_used > (ET_TX_NDESC * 2) / 3)
		et_txeof(sc);

	for (enq = 0; !IFQ_DRV_IS_EMPTY(&ifp->if_snd); ) {
		if (tbd->tbd_used + ET_NSEG_SPARE >= ET_TX_NDESC) {
			ifp->if_drv_flags |= IFF_DRV_OACTIVE;
			break;
		}

		IFQ_DRV_DEQUEUE(&ifp->if_snd, m_head);
		if (m_head == NULL)
			break;

		if (et_encap(sc, &m_head)) {
			if (m_head == NULL) {
				if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
				break;
			}
			IFQ_DRV_PREPEND(&ifp->if_snd, m_head);
			if (tbd->tbd_used > 0)
				ifp->if_drv_flags |= IFF_DRV_OACTIVE;
			break;
		}
		enq++;
		ETHER_BPF_MTAP(ifp, m_head);
	}

	if (enq > 0) {
		tx_ring = &sc->sc_tx_ring;
		bus_dmamap_sync(tx_ring->tr_dtag, tx_ring->tr_dmap,
		    BUS_DMASYNC_PREWRITE);
		tx_ready_pos = tx_ring->tr_ready_index &
		    ET_TX_READY_POS_INDEX_MASK;
		if (tx_ring->tr_ready_wrap)
			tx_ready_pos |= ET_TX_READY_POS_WRAP;
		CSR_WRITE_4(sc, ET_TX_READY_POS, tx_ready_pos);
		sc->watchdog_timer = 5;
	}
}