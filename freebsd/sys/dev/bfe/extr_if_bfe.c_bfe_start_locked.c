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
struct mbuf {int dummy; } ;
struct ifnet {int if_drv_flags; int /*<<< orphan*/  if_snd; struct bfe_softc* if_softc; } ;
struct bfe_softc {int bfe_flags; int bfe_tx_cnt; int bfe_tx_prod; int bfe_watchdog_timer; int /*<<< orphan*/  bfe_tx_map; int /*<<< orphan*/  bfe_tx_tag; } ;
struct bfe_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFE_DMATX_PTR ; 
 int BFE_FLAG_LINK ; 
 int /*<<< orphan*/  BFE_LOCK_ASSERT (struct bfe_softc*) ; 
 int BFE_TX_LIST_CNT ; 
 int /*<<< orphan*/  BPF_MTAP (struct ifnet*,struct mbuf*) ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct bfe_softc*,int /*<<< orphan*/ ,int) ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFQ_DRV_DEQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFQ_DRV_PREPEND (int /*<<< orphan*/ *,struct mbuf*) ; 
 scalar_t__ bfe_encap (struct bfe_softc*,struct mbuf**) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bfe_start_locked(struct ifnet *ifp)
{
	struct bfe_softc *sc;
	struct mbuf *m_head;
	int queued;

	sc = ifp->if_softc;

	BFE_LOCK_ASSERT(sc);

	/*
	 * Not much point trying to send if the link is down
	 * or we have nothing to send.
	 */
	if ((ifp->if_drv_flags & (IFF_DRV_RUNNING | IFF_DRV_OACTIVE)) !=
	    IFF_DRV_RUNNING || (sc->bfe_flags & BFE_FLAG_LINK) == 0)
		return;

	for (queued = 0; !IFQ_DRV_IS_EMPTY(&ifp->if_snd) &&
	    sc->bfe_tx_cnt < BFE_TX_LIST_CNT - 1;) {
		IFQ_DRV_DEQUEUE(&ifp->if_snd, m_head);
		if (m_head == NULL)
			break;

		/*
		 * Pack the data into the tx ring.  If we dont have
		 * enough room, let the chip drain the ring.
		 */
		if (bfe_encap(sc, &m_head)) {
			if (m_head == NULL)
				break;
			IFQ_DRV_PREPEND(&ifp->if_snd, m_head);
			ifp->if_drv_flags |= IFF_DRV_OACTIVE;
			break;
		}

		queued++;

		/*
		 * If there's a BPF listener, bounce a copy of this frame
		 * to him.
		 */
		BPF_MTAP(ifp, m_head);
	}

	if (queued) {
		bus_dmamap_sync(sc->bfe_tx_tag, sc->bfe_tx_map,
		    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);
		/* Transmit - twice due to apparent hardware bug */
		CSR_WRITE_4(sc, BFE_DMATX_PTR,
		    sc->bfe_tx_prod * sizeof(struct bfe_desc));
		/*
		 * XXX It seems the following write is not necessary
		 * to kick Tx command. What might be required would be
		 * a way flushing PCI posted write. Reading the register
		 * back ensures the flush operation. In addition,
		 * hardware will execute PCI posted write in the long
		 * run and watchdog timer for the kick command was set
		 * to 5 seconds. Therefore I think the second write
		 * access is not necessary or could be replaced with
		 * read operation.
		 */
		CSR_WRITE_4(sc, BFE_DMATX_PTR,
		    sc->bfe_tx_prod * sizeof(struct bfe_desc));

		/*
		 * Set a timeout in case the chip goes out to lunch.
		 */
		sc->bfe_watchdog_timer = 5;
	}
}