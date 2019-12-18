#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int queued; } ;
struct rt2560_softc {int sc_tx_timer; int /*<<< orphan*/  sc_snd; TYPE_2__ txq; } ;
struct TYPE_6__ {scalar_t__ rcvif; } ;
struct mbuf {TYPE_3__ m_pkthdr; } ;
struct ieee80211_node {TYPE_1__* ni_vap; } ;
struct TYPE_4__ {int /*<<< orphan*/  iv_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  RAL_LOCK_ASSERT (struct rt2560_softc*) ; 
 int RT2560_TX_RING_COUNT ; 
 int /*<<< orphan*/  ieee80211_free_node (struct ieee80211_node*) ; 
 int /*<<< orphan*/  if_inc_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct mbuf* mbufq_dequeue (int /*<<< orphan*/ *) ; 
 scalar_t__ rt2560_tx_data (struct rt2560_softc*,struct mbuf*,struct ieee80211_node*) ; 

__attribute__((used)) static void
rt2560_start(struct rt2560_softc *sc)
{
	struct ieee80211_node *ni;
	struct mbuf *m;

	RAL_LOCK_ASSERT(sc);

	while (sc->txq.queued < RT2560_TX_RING_COUNT - 1 &&
	    (m = mbufq_dequeue(&sc->sc_snd)) != NULL) {
		ni = (struct ieee80211_node *) m->m_pkthdr.rcvif;
		if (rt2560_tx_data(sc, m, ni) != 0) {
			if_inc_counter(ni->ni_vap->iv_ifp,
			    IFCOUNTER_OERRORS, 1);
			ieee80211_free_node(ni);
			break;
		}
		sc->sc_tx_timer = 5;
	}
}