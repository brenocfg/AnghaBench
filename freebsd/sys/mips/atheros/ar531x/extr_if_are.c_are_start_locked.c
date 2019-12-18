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
struct ifnet {int if_drv_flags; int /*<<< orphan*/  if_snd; struct are_softc* if_softc; } ;
struct TYPE_2__ {int are_tx_cnt; } ;
struct are_softc {scalar_t__ are_link_status; TYPE_1__ are_cdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARE_LOCK_ASSERT (struct are_softc*) ; 
 int ARE_TX_RING_CNT ; 
 int CSR_READ_4 (struct are_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_STATUS ; 
 int /*<<< orphan*/  CSR_TXPOLL ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct are_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ETHER_BPF_MTAP (struct ifnet*,struct mbuf*) ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFQ_DRV_DEQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFQ_DRV_PREPEND (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  TXPOLL_TPD ; 
 scalar_t__ are_encap (struct are_softc*,struct mbuf**) ; 

__attribute__((used)) static void
are_start_locked(struct ifnet *ifp)
{
	struct are_softc		*sc;
	struct mbuf		*m_head;
	int			enq;
	int			txstat;

	sc = ifp->if_softc;

	ARE_LOCK_ASSERT(sc);

	if ((ifp->if_drv_flags & (IFF_DRV_RUNNING | IFF_DRV_OACTIVE)) !=
	    IFF_DRV_RUNNING || sc->are_link_status == 0 )
		return;

	for (enq = 0; !IFQ_DRV_IS_EMPTY(&ifp->if_snd) &&
	    sc->are_cdata.are_tx_cnt < ARE_TX_RING_CNT - 2; ) {
		IFQ_DRV_DEQUEUE(&ifp->if_snd, m_head);
		if (m_head == NULL)
			break;
		/*
		 * Pack the data into the transmit ring. If we
		 * don't have room, set the OACTIVE flag and wait
		 * for the NIC to drain the ring.
		 */
		if (are_encap(sc, &m_head)) {
			if (m_head == NULL)
				break;
			IFQ_DRV_PREPEND(&ifp->if_snd, m_head);
			ifp->if_drv_flags |= IFF_DRV_OACTIVE;
			break;
		}

		enq++;
		/*
		 * If there's a BPF listener, bounce a copy of this frame
		 * to him.
		 */
		ETHER_BPF_MTAP(ifp, m_head);
	}

	if (enq > 0) { 
		txstat = (CSR_READ_4(sc, CSR_STATUS) >> 20) & 7;
		if (txstat == 0 || txstat == 6) {
			/* Transmit Process Stat is stop or suspended */
			CSR_WRITE_4(sc, CSR_TXPOLL, TXPOLL_TPD);
		}
	}
}