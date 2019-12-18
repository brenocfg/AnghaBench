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
struct TYPE_2__ {scalar_t__ rcvif; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct iwn_softc {int sc_flags; int sc_tx_timer; scalar_t__ qfullmsk; scalar_t__ sc_beacon_wait; } ;
struct ieee80211com {struct iwn_softc* ic_softc; } ;
struct ieee80211_node {int dummy; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int ENXIO ; 
 int IWN_FLAG_RUNNING ; 
 int /*<<< orphan*/  IWN_LOCK (struct iwn_softc*) ; 
 int /*<<< orphan*/  IWN_UNLOCK (struct iwn_softc*) ; 
 int iwn_tx_data (struct iwn_softc*,struct mbuf*,struct ieee80211_node*) ; 

__attribute__((used)) static int
iwn_transmit(struct ieee80211com *ic, struct mbuf *m)
{
	struct iwn_softc *sc = ic->ic_softc;
	struct ieee80211_node *ni;
	int error;

	ni = (struct ieee80211_node *)m->m_pkthdr.rcvif;

	IWN_LOCK(sc);
	if ((sc->sc_flags & IWN_FLAG_RUNNING) == 0 || sc->sc_beacon_wait) {
		IWN_UNLOCK(sc);
		return (ENXIO);
	}

	if (sc->qfullmsk) {
		IWN_UNLOCK(sc);
		return (ENOBUFS);
	}

	error = iwn_tx_data(sc, m, ni);
	if (!error)
		sc->sc_tx_timer = 5;
	IWN_UNLOCK(sc);
	return (error);
}