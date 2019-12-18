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
struct TYPE_2__ {struct ifnet* rcvif; } ;
struct mbuf {TYPE_1__ m_pkthdr; struct mbuf* m_nextpkt; } ;
struct ifnet {int /*<<< orphan*/  (* if_input ) (struct ifnet*,struct mbuf*) ;} ;
struct cpsw_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPSW_CPDMA_CPDMA_EOI_VECTOR ; 
 int /*<<< orphan*/  CPSW_RX_LOCK (struct cpsw_softc*) ; 
 int /*<<< orphan*/  CPSW_RX_UNLOCK (struct cpsw_softc*) ; 
 int /*<<< orphan*/  IFCOUNTER_IPACKETS ; 
 struct mbuf* cpsw_rx_dequeue (struct cpsw_softc*) ; 
 int /*<<< orphan*/  cpsw_rx_enqueue (struct cpsw_softc*) ; 
 int /*<<< orphan*/  cpsw_write_4 (struct cpsw_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct ifnet*,struct mbuf*) ; 

__attribute__((used)) static void
cpsw_intr_rx_thresh(void *arg)
{
	struct cpsw_softc *sc;
	struct ifnet *ifp;
	struct mbuf *received, *next;

	sc = (struct cpsw_softc *)arg;
	CPSW_RX_LOCK(sc);
	received = cpsw_rx_dequeue(sc);
	cpsw_rx_enqueue(sc);
	cpsw_write_4(sc, CPSW_CPDMA_CPDMA_EOI_VECTOR, 0);
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