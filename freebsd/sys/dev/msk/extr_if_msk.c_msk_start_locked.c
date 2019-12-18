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
struct TYPE_2__ {scalar_t__ msk_tx_cnt; int /*<<< orphan*/  msk_tx_prod; } ;
struct msk_if_softc {int msk_flags; int /*<<< orphan*/  msk_watchdog_timer; TYPE_1__ msk_cdata; int /*<<< orphan*/  msk_txq; int /*<<< orphan*/  msk_softc; } ;
struct mbuf {int dummy; } ;
struct ifnet {int if_drv_flags; int /*<<< orphan*/  if_snd; struct msk_if_softc* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ETHER_BPF_MTAP (struct ifnet*,struct mbuf*) ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFQ_DRV_DEQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFQ_DRV_PREPEND (int /*<<< orphan*/ *,struct mbuf*) ; 
 int MSK_FLAG_LINK ; 
 int /*<<< orphan*/  MSK_IF_LOCK_ASSERT (struct msk_if_softc*) ; 
 scalar_t__ MSK_RESERVED_TX_DESC_CNT ; 
 scalar_t__ MSK_TX_RING_CNT ; 
 int /*<<< orphan*/  MSK_TX_TIMEOUT ; 
 int /*<<< orphan*/  PREF_UNIT_PUT_IDX_REG ; 
 int /*<<< orphan*/  Y2_PREF_Q_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ msk_encap (struct msk_if_softc*,struct mbuf**) ; 

__attribute__((used)) static void
msk_start_locked(struct ifnet *ifp)
{
	struct msk_if_softc *sc_if;
	struct mbuf *m_head;
	int enq;

	sc_if = ifp->if_softc;
	MSK_IF_LOCK_ASSERT(sc_if);

	if ((ifp->if_drv_flags & (IFF_DRV_RUNNING | IFF_DRV_OACTIVE)) !=
	    IFF_DRV_RUNNING || (sc_if->msk_flags & MSK_FLAG_LINK) == 0)
		return;

	for (enq = 0; !IFQ_DRV_IS_EMPTY(&ifp->if_snd) &&
	    sc_if->msk_cdata.msk_tx_cnt <
	    (MSK_TX_RING_CNT - MSK_RESERVED_TX_DESC_CNT); ) {
		IFQ_DRV_DEQUEUE(&ifp->if_snd, m_head);
		if (m_head == NULL)
			break;
		/*
		 * Pack the data into the transmit ring. If we
		 * don't have room, set the OACTIVE flag and wait
		 * for the NIC to drain the ring.
		 */
		if (msk_encap(sc_if, &m_head) != 0) {
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
		/* Transmit */
		CSR_WRITE_2(sc_if->msk_softc,
		    Y2_PREF_Q_ADDR(sc_if->msk_txq, PREF_UNIT_PUT_IDX_REG),
		    sc_if->msk_cdata.msk_tx_prod);

		/* Set a timeout in case the chip goes out to lunch. */
		sc_if->msk_watchdog_timer = MSK_TX_TIMEOUT;
	}
}