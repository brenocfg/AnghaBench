#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rt_softc {int /*<<< orphan*/  tx_watchdog_ch; int /*<<< orphan*/  tx_timer; TYPE_2__* tx_ring; int /*<<< orphan*/ * tx_data_queue_full; } ;
struct TYPE_4__ {int /*<<< orphan*/ * rcvif; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct ifnet {int if_drv_flags; int /*<<< orphan*/  if_snd; struct rt_softc* if_softc; } ;
struct TYPE_5__ {scalar_t__ data_queued; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFQ_DRV_DEQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  RT_DEBUG_TX ; 
 int /*<<< orphan*/  RT_DPRINTF (struct rt_softc*,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ RT_SOFTC_TX_RING_DATA_COUNT ; 
 int /*<<< orphan*/  RT_SOFTC_TX_RING_LOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  RT_SOFTC_TX_RING_UNLOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  RT_TX_WATCHDOG_TIMEOUT ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rt_softc*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 scalar_t__ rt_tx_data (struct rt_softc*,struct mbuf*,int) ; 
 int /*<<< orphan*/  rt_tx_watchdog ; 

__attribute__((used)) static void
rt_start(struct ifnet *ifp)
{
	struct rt_softc *sc;
	struct mbuf *m;
	int qid = 0 /* XXX must check QoS priority */;

	sc = ifp->if_softc;

	if (!(ifp->if_drv_flags & IFF_DRV_RUNNING))
		return;

	for (;;) {
		IFQ_DRV_DEQUEUE(&ifp->if_snd, m);
		if (m == NULL)
			break;

		m->m_pkthdr.rcvif = NULL;

		RT_SOFTC_TX_RING_LOCK(&sc->tx_ring[qid]);

		if (sc->tx_ring[qid].data_queued >=
		    RT_SOFTC_TX_RING_DATA_COUNT) {
			RT_SOFTC_TX_RING_UNLOCK(&sc->tx_ring[qid]);

			RT_DPRINTF(sc, RT_DEBUG_TX,
			    "if_start: Tx ring with qid=%d is full\n", qid);

			m_freem(m);

			ifp->if_drv_flags |= IFF_DRV_OACTIVE;
			if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);

			sc->tx_data_queue_full[qid]++;

			break;
		}

		if (rt_tx_data(sc, m, qid) != 0) {
			RT_SOFTC_TX_RING_UNLOCK(&sc->tx_ring[qid]);

			if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);

			break;
		}

		RT_SOFTC_TX_RING_UNLOCK(&sc->tx_ring[qid]);
		sc->tx_timer = RT_TX_WATCHDOG_TIMEOUT;
		callout_reset(&sc->tx_watchdog_ch, hz, rt_tx_watchdog, sc);
	}
}