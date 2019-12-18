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
struct ifnet {int if_drv_flags; int /*<<< orphan*/  if_snd; struct age_softc* if_softc; } ;
struct age_softc {int age_flags; int /*<<< orphan*/  age_watchdog_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGE_COMMIT_MBOX (struct age_softc*) ; 
 int AGE_FLAG_LINK ; 
 int /*<<< orphan*/  AGE_LOCK_ASSERT (struct age_softc*) ; 
 int /*<<< orphan*/  AGE_TX_TIMEOUT ; 
 int /*<<< orphan*/  ETHER_BPF_MTAP (struct ifnet*,struct mbuf*) ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFQ_DRV_DEQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFQ_DRV_PREPEND (int /*<<< orphan*/ *,struct mbuf*) ; 
 scalar_t__ age_encap (struct age_softc*,struct mbuf**) ; 

__attribute__((used)) static void
age_start_locked(struct ifnet *ifp)
{
        struct age_softc *sc;
        struct mbuf *m_head;
	int enq;

	sc = ifp->if_softc;

	AGE_LOCK_ASSERT(sc);

	if ((ifp->if_drv_flags & (IFF_DRV_RUNNING | IFF_DRV_OACTIVE)) !=
	    IFF_DRV_RUNNING || (sc->age_flags & AGE_FLAG_LINK) == 0)
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
		if (age_encap(sc, &m_head)) {
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
		/* Update mbox. */
		AGE_COMMIT_MBOX(sc);
		/* Set a timeout in case the chip goes out to lunch. */
		sc->age_watchdog_timer = AGE_TX_TIMEOUT;
	}
}