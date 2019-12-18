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
typedef  int uint32_t ;
struct mge_softc {scalar_t__ tx_desc_used_count; int wd_timer; } ;
struct TYPE_2__ {int csum_flags; } ;
struct mbuf {int m_flags; int /*<<< orphan*/ * m_next; TYPE_1__ m_pkthdr; } ;
struct ifnet {int if_drv_flags; int /*<<< orphan*/  if_snd; struct mge_softc* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_MTAP (struct ifnet*,struct mbuf*) ; 
 int CSUM_IP ; 
 int CSUM_TCP ; 
 int CSUM_UDP ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IF_DEQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  IF_PREPEND (int /*<<< orphan*/ *,struct mbuf*) ; 
 int MGE_ENABLE_TXQ ; 
 int MGE_READ (struct mge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MGE_TRANSMIT_LOCK_ASSERT (struct mge_softc*) ; 
 scalar_t__ MGE_TX_DESC_NUM ; 
 int /*<<< orphan*/  MGE_TX_QUEUE_CMD ; 
 int /*<<< orphan*/  MGE_WRITE (struct mge_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int M_VLANTAG ; 
 scalar_t__ M_WRITABLE (struct mbuf*) ; 
 struct mbuf* m_defrag (struct mbuf*,int /*<<< orphan*/ ) ; 
 struct mbuf* m_dup (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 scalar_t__ mge_encap (struct mge_softc*,struct mbuf*) ; 

__attribute__((used)) static void
mge_start_locked(struct ifnet *ifp)
{
	struct mge_softc *sc;
	struct mbuf *m0, *mtmp;
	uint32_t reg_val, queued = 0;

	sc = ifp->if_softc;

	MGE_TRANSMIT_LOCK_ASSERT(sc);

	if ((ifp->if_drv_flags & (IFF_DRV_RUNNING | IFF_DRV_OACTIVE)) !=
	    IFF_DRV_RUNNING)
		return;

	for (;;) {
		/* Get packet from the queue */
		IF_DEQUEUE(&ifp->if_snd, m0);
		if (m0 == NULL)
			break;

		if (m0->m_pkthdr.csum_flags & (CSUM_IP|CSUM_TCP|CSUM_UDP) ||
		    m0->m_flags & M_VLANTAG) {
			if (M_WRITABLE(m0) == 0) {
				mtmp = m_dup(m0, M_NOWAIT);
				m_freem(m0);
				if (mtmp == NULL)
					continue;
				m0 = mtmp;
			}
		}
		/* The driver support only one DMA fragment. */
		if (m0->m_next != NULL) {
			mtmp = m_defrag(m0, M_NOWAIT);
			if (mtmp != NULL)
				m0 = mtmp;
		}

		/* Check for free descriptors */
		if (sc->tx_desc_used_count + 1 >= MGE_TX_DESC_NUM) {
			IF_PREPEND(&ifp->if_snd, m0);
			ifp->if_drv_flags |= IFF_DRV_OACTIVE;
			break;
		}

		if (mge_encap(sc, m0) != 0)
			break;

		queued++;
		BPF_MTAP(ifp, m0);
	}

	if (queued) {
		/* Enable transmitter and watchdog timer */
		reg_val = MGE_READ(sc, MGE_TX_QUEUE_CMD);
		MGE_WRITE(sc, MGE_TX_QUEUE_CMD, reg_val | MGE_ENABLE_TXQ);
		sc->wd_timer = 5;
	}
}