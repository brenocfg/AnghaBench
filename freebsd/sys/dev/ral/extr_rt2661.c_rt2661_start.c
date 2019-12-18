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
struct rt2661_softc {int sc_flags; int sc_tx_timer; int /*<<< orphan*/  sc_snd; TYPE_1__* txq; scalar_t__ sc_invalid; } ;
struct TYPE_5__ {scalar_t__ rcvif; } ;
struct mbuf {TYPE_2__ m_pkthdr; } ;
struct ieee80211_node {TYPE_3__* ni_vap; } ;
struct TYPE_6__ {int /*<<< orphan*/  iv_ifp; } ;
struct TYPE_4__ {int queued; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int M_WME_GETAC (struct mbuf*) ; 
 int /*<<< orphan*/  RAL_LOCK_ASSERT (struct rt2661_softc*) ; 
 int RAL_RUNNING ; 
 int RT2661_TX_RING_COUNT ; 
 int /*<<< orphan*/  ieee80211_free_node (struct ieee80211_node*) ; 
 int /*<<< orphan*/  if_inc_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct mbuf* mbufq_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbufq_prepend (int /*<<< orphan*/ *,struct mbuf*) ; 
 scalar_t__ rt2661_tx_data (struct rt2661_softc*,struct mbuf*,struct ieee80211_node*,int) ; 

__attribute__((used)) static void
rt2661_start(struct rt2661_softc *sc)
{
	struct mbuf *m;
	struct ieee80211_node *ni;
	int ac;

	RAL_LOCK_ASSERT(sc);

	/* prevent management frames from being sent if we're not ready */
	if (!(sc->sc_flags & RAL_RUNNING) || sc->sc_invalid)
		return;

	while ((m = mbufq_dequeue(&sc->sc_snd)) != NULL) {
		ac = M_WME_GETAC(m);
		if (sc->txq[ac].queued >= RT2661_TX_RING_COUNT - 1) {
			/* there is no place left in this ring */
			mbufq_prepend(&sc->sc_snd, m);
			break;
		}
		ni = (struct ieee80211_node *) m->m_pkthdr.rcvif;
		if (rt2661_tx_data(sc, m, ni, ac) != 0) {
			if_inc_counter(ni->ni_vap->iv_ifp,
			    IFCOUNTER_OERRORS, 1);
			ieee80211_free_node(ni);
			break;
		}
		sc->sc_tx_timer = 5;
	}
}