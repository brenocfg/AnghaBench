#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct ifnet* rcvif; } ;
struct mbuf {TYPE_1__ m_pkthdr; struct mbuf* m_nextpkt; } ;
struct ifnet {int /*<<< orphan*/  (* if_input ) (struct ifnet*,struct mbuf*) ;} ;
struct TYPE_4__ {scalar_t__ teardown; scalar_t__ running; } ;
struct cpsw_softc {TYPE_2__ rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPSW_CPDMA_CPDMA_EOI_VECTOR ; 
 int /*<<< orphan*/  CPSW_RX_LOCK (struct cpsw_softc*) ; 
 int /*<<< orphan*/  CPSW_RX_UNLOCK (struct cpsw_softc*) ; 
 int /*<<< orphan*/  IFCOUNTER_IPACKETS ; 
 struct mbuf* cpsw_rx_dequeue (struct cpsw_softc*) ; 
 int /*<<< orphan*/  cpsw_rx_enqueue (struct cpsw_softc*) ; 
 int /*<<< orphan*/  cpsw_write_4 (struct cpsw_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpsw_write_cp (struct cpsw_softc*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct ifnet*,struct mbuf*) ; 

__attribute__((used)) static void
cpsw_intr_rx(void *arg)
{
	struct cpsw_softc *sc;
	struct ifnet *ifp;
	struct mbuf *received, *next;

	sc = (struct cpsw_softc *)arg;
	CPSW_RX_LOCK(sc);
	if (sc->rx.teardown) {
		sc->rx.running = 0;
		sc->rx.teardown = 0;
		cpsw_write_cp(sc, &sc->rx, 0xfffffffc);
	}
	received = cpsw_rx_dequeue(sc);
	cpsw_rx_enqueue(sc);
	cpsw_write_4(sc, CPSW_CPDMA_CPDMA_EOI_VECTOR, 1);
	CPSW_RX_UNLOCK(sc);

	while (received != NULL) {
		next = received->m_nextpkt;
		received->m_nextpkt = NULL;
		ifp = received->m_pkthdr.rcvif;
		(*ifp->if_input)(ifp, received);
		if_inc_counter(ifp, IFCOUNTER_IPACKETS, 1);
		received = next;
	}
}