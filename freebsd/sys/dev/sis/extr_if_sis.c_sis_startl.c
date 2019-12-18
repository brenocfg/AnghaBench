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
struct sis_softc {int sis_flags; int sis_tx_cnt; int sis_watchdog_timer; int /*<<< orphan*/  sis_tx_list_map; int /*<<< orphan*/  sis_tx_list_tag; } ;
struct mbuf {int dummy; } ;
struct ifnet {int if_drv_flags; int /*<<< orphan*/  if_snd; struct sis_softc* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_MTAP (struct ifnet*,struct mbuf*) ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFQ_DRV_DEQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFQ_DRV_PREPEND (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  SIS_CSR ; 
 int /*<<< orphan*/  SIS_CSR_TX_ENABLE ; 
 int SIS_FLAG_LINK ; 
 int /*<<< orphan*/  SIS_LOCK_ASSERT (struct sis_softc*) ; 
 int /*<<< orphan*/  SIS_SETBIT (struct sis_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SIS_TX_LIST_CNT ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sis_encap (struct sis_softc*,struct mbuf**) ; 

__attribute__((used)) static void
sis_startl(struct ifnet *ifp)
{
	struct sis_softc	*sc;
	struct mbuf		*m_head;
	int			queued;

	sc = ifp->if_softc;

	SIS_LOCK_ASSERT(sc);

	if ((ifp->if_drv_flags & (IFF_DRV_RUNNING | IFF_DRV_OACTIVE)) !=
	    IFF_DRV_RUNNING || (sc->sis_flags & SIS_FLAG_LINK) == 0)
		return;

	for (queued = 0; !IFQ_DRV_IS_EMPTY(&ifp->if_snd) &&
	    sc->sis_tx_cnt < SIS_TX_LIST_CNT - 4;) {
		IFQ_DRV_DEQUEUE(&ifp->if_snd, m_head);
		if (m_head == NULL)
			break;

		if (sis_encap(sc, &m_head) != 0) {
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
		/* Transmit */
		bus_dmamap_sync(sc->sis_tx_list_tag, sc->sis_tx_list_map,
		    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);
		SIS_SETBIT(sc, SIS_CSR, SIS_CSR_TX_ENABLE);

		/*
		 * Set a timeout in case the chip goes out to lunch.
		 */
		sc->sis_watchdog_timer = 5;
	}
}