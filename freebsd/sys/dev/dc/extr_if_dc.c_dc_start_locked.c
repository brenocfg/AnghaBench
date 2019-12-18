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
struct mbuf {int dummy; } ;
struct ifnet {int if_drv_flags; int /*<<< orphan*/  if_snd; struct dc_softc* if_softc; } ;
struct TYPE_2__ {scalar_t__ dc_tx_cnt; int /*<<< orphan*/  dc_tx_prod; int /*<<< orphan*/  dc_tx_first; } ;
struct dc_softc {scalar_t__ dc_link; int dc_flags; int dc_wdog_timer; TYPE_1__ dc_cdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_MTAP (struct ifnet*,struct mbuf*) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct dc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DC_LOCK_ASSERT (struct dc_softc*) ; 
 int /*<<< orphan*/  DC_TXSTART ; 
 scalar_t__ DC_TX_LIST_CNT ; 
 scalar_t__ DC_TX_LIST_RSVD ; 
 int DC_TX_POLL ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFQ_DRV_DEQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFQ_DRV_PREPEND (int /*<<< orphan*/ *,struct mbuf*) ; 
 scalar_t__ dc_encap (struct dc_softc*,struct mbuf**) ; 

__attribute__((used)) static void
dc_start_locked(struct ifnet *ifp)
{
	struct dc_softc *sc;
	struct mbuf *m_head;
	int queued;

	sc = ifp->if_softc;

	DC_LOCK_ASSERT(sc);

	if ((ifp->if_drv_flags & (IFF_DRV_RUNNING | IFF_DRV_OACTIVE)) !=
	    IFF_DRV_RUNNING || sc->dc_link == 0)
		return;

	sc->dc_cdata.dc_tx_first = sc->dc_cdata.dc_tx_prod;

	for (queued = 0; !IFQ_DRV_IS_EMPTY(&ifp->if_snd); ) {
		/*
		 * If there's no way we can send any packets, return now.
		 */
		if (sc->dc_cdata.dc_tx_cnt > DC_TX_LIST_CNT - DC_TX_LIST_RSVD) {
			ifp->if_drv_flags |= IFF_DRV_OACTIVE;
			break;
		}
		IFQ_DRV_DEQUEUE(&ifp->if_snd, m_head);
		if (m_head == NULL)
			break;

		if (dc_encap(sc, &m_head)) {
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

	if (queued > 0) {
		/* Transmit */
		if (!(sc->dc_flags & DC_TX_POLL))
			CSR_WRITE_4(sc, DC_TXSTART, 0xFFFFFFFF);

		/*
		 * Set a timeout in case the chip goes out to lunch.
		 */
		sc->dc_wdog_timer = 5;
	}
}