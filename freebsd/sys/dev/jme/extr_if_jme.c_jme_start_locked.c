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
struct TYPE_2__ {scalar_t__ jme_tx_cnt; } ;
struct jme_softc {int jme_flags; int jme_txcsr; int /*<<< orphan*/  jme_watchdog_timer; TYPE_1__ jme_cdata; } ;
struct ifnet {int if_drv_flags; int /*<<< orphan*/  if_snd; struct jme_softc* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_4 (struct jme_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ETHER_BPF_MTAP (struct ifnet*,struct mbuf*) ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFQ_DRV_DEQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFQ_DRV_PREPEND (int /*<<< orphan*/ *,struct mbuf*) ; 
 int JME_FLAG_LINK ; 
 int /*<<< orphan*/  JME_LOCK_ASSERT (struct jme_softc*) ; 
 int /*<<< orphan*/  JME_TXCSR ; 
 scalar_t__ JME_TX_DESC_HIWAT ; 
 int /*<<< orphan*/  JME_TX_TIMEOUT ; 
 int /*<<< orphan*/  TXCSR_TXQ0 ; 
 int TXCSR_TXQ_N_START (int /*<<< orphan*/ ) ; 
 int TXCSR_TX_ENB ; 
 scalar_t__ jme_encap (struct jme_softc*,struct mbuf**) ; 
 int /*<<< orphan*/  jme_txeof (struct jme_softc*) ; 

__attribute__((used)) static void
jme_start_locked(struct ifnet *ifp)
{
        struct jme_softc *sc;
        struct mbuf *m_head;
	int enq;

	sc = ifp->if_softc;

	JME_LOCK_ASSERT(sc);

	if (sc->jme_cdata.jme_tx_cnt >= JME_TX_DESC_HIWAT)
		jme_txeof(sc);

	if ((ifp->if_drv_flags & (IFF_DRV_RUNNING | IFF_DRV_OACTIVE)) !=
	    IFF_DRV_RUNNING || (sc->jme_flags & JME_FLAG_LINK) == 0)
		return;

	for (enq = 0; !IFQ_DRV_IS_EMPTY(&ifp->if_snd); ) {
		IFQ_DRV_DEQUEUE(&ifp->if_snd, m_head);
		if (m_head == NULL)
			break;
		/*
		 * Pack the data into the transmit ring. If we
		 * don't have room, set the OACTIVE flag and wait
		 * for the NIC to drain the ring.
		 */
		if (jme_encap(sc, &m_head)) {
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
		/*
		 * Reading TXCSR takes very long time under heavy load
		 * so cache TXCSR value and writes the ORed value with
		 * the kick command to the TXCSR. This saves one register
		 * access cycle.
		 */
		CSR_WRITE_4(sc, JME_TXCSR, sc->jme_txcsr | TXCSR_TX_ENB |
		    TXCSR_TXQ_N_START(TXCSR_TXQ0));
		/* Set a timeout in case the chip goes out to lunch. */
		sc->jme_watchdog_timer = JME_TX_TIMEOUT;
	}
}