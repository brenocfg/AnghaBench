#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ error; int /*<<< orphan*/  transferred; } ;
typedef  TYPE_2__ xdma_transfer_status_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {struct ifnet* rcvif; int /*<<< orphan*/  len; } ;
struct mbuf {TYPE_1__ m_pkthdr; int /*<<< orphan*/  m_len; } ;
struct ifnet {int /*<<< orphan*/  (* if_input ) (struct ifnet*,struct mbuf*) ;} ;
struct atse_softc {int /*<<< orphan*/  xchan_rx; struct ifnet* atse_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATSE_LOCK (struct atse_softc*) ; 
 int /*<<< orphan*/  ATSE_UNLOCK (struct atse_softc*) ; 
 int /*<<< orphan*/  ETHER_ALIGN ; 
 int /*<<< orphan*/  IFCOUNTER_IERRORS ; 
 int /*<<< orphan*/  atse_rx_enqueue (struct atse_softc*,scalar_t__) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m_adj (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  stub1 (struct ifnet*,struct mbuf*) ; 
 int xdma_dequeue_mbuf (int /*<<< orphan*/ ,struct mbuf**,TYPE_2__*) ; 

__attribute__((used)) static int
atse_xdma_rx_intr(void *arg, xdma_transfer_status_t *status)
{
	xdma_transfer_status_t st;
	struct atse_softc *sc;
	struct ifnet *ifp;
	struct mbuf *m;
	int err;
	uint32_t cnt_processed;

	sc = arg;

	ATSE_LOCK(sc);

	ifp = sc->atse_ifp;

	cnt_processed = 0;
	for (;;) {
		err = xdma_dequeue_mbuf(sc->xchan_rx, &m, &st);
		if (err != 0) {
			break;
		}
		cnt_processed++;

		if (st.error != 0) {
			if_inc_counter(ifp, IFCOUNTER_IERRORS, 1);
			m_freem(m);
			continue;
		}

		m->m_pkthdr.len = m->m_len = st.transferred;
		m->m_pkthdr.rcvif = ifp;
		m_adj(m, ETHER_ALIGN);
		ATSE_UNLOCK(sc);
		(*ifp->if_input)(ifp, m);
		ATSE_LOCK(sc);
	}

	atse_rx_enqueue(sc, cnt_processed);

	ATSE_UNLOCK(sc);

	return (0);
}