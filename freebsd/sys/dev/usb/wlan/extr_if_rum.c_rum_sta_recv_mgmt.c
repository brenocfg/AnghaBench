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
struct rum_vap {int /*<<< orphan*/  (* recv_mgmt ) (struct ieee80211_node*,struct mbuf*,int,struct ieee80211_rx_stats const*,int,int) ;} ;
struct rum_softc {int last_rx_flags; } ;
struct mbuf {int dummy; } ;
struct ieee80211vap {scalar_t__ iv_state; TYPE_1__* iv_ic; } ;
struct ieee80211_rx_stats {int dummy; } ;
struct ieee80211_node {struct ieee80211vap* ni_vap; } ;
struct TYPE_2__ {struct rum_softc* ic_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,int,int) ; 
 int IEEE80211_FC0_SUBTYPE_BEACON ; 
 scalar_t__ IEEE80211_S_SLEEP ; 
 int RT2573_RX_BC ; 
 int RT2573_RX_MYBSS ; 
 int /*<<< orphan*/  RUM_LOCK (struct rum_softc*) ; 
 int /*<<< orphan*/  RUM_UNLOCK (struct rum_softc*) ; 
 struct rum_vap* RUM_VAP (struct ieee80211vap*) ; 
 int /*<<< orphan*/  rum_set_power_state (struct rum_softc*,int) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_node*,struct mbuf*,int,struct ieee80211_rx_stats const*,int,int) ; 

__attribute__((used)) static void
rum_sta_recv_mgmt(struct ieee80211_node *ni, struct mbuf *m, int subtype,
    const struct ieee80211_rx_stats *rxs,
    int rssi, int nf)
{
	struct ieee80211vap *vap = ni->ni_vap;
	struct rum_softc *sc = vap->iv_ic->ic_softc;
	struct rum_vap *rvp = RUM_VAP(vap);

	if (vap->iv_state == IEEE80211_S_SLEEP &&
	    subtype == IEEE80211_FC0_SUBTYPE_BEACON) {
		RUM_LOCK(sc);
		DPRINTFN(12, "beacon, mybss %d (flags %02X)\n",
		    !!(sc->last_rx_flags & RT2573_RX_MYBSS),
		    sc->last_rx_flags);

		if ((sc->last_rx_flags & (RT2573_RX_MYBSS | RT2573_RX_BC)) ==
		    (RT2573_RX_MYBSS | RT2573_RX_BC)) {
			/*
			 * Put it to sleep here; in case if there is a data
			 * for us, iv_recv_mgmt() will wakeup the device via
			 * SLEEP -> RUN state transition.
			 */
			rum_set_power_state(sc, 1);
		}
		RUM_UNLOCK(sc);
	}

	rvp->recv_mgmt(ni, m, subtype, rxs, rssi, nf);
}