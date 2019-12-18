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
struct ieee80211com {struct bwn_softc* ic_softc; } ;
struct ieee80211_node {struct ieee80211com* ni_ic; } ;
struct ieee80211_bpf_params {int dummy; } ;
struct bwn_softc {int sc_flags; int sc_watchdog_timer; struct bwn_mac* sc_curmac; } ;
struct bwn_mac {scalar_t__ mac_status; } ;

/* Variables and functions */
 int BWN_FLAG_RUNNING ; 
 int /*<<< orphan*/  BWN_LOCK (struct bwn_softc*) ; 
 scalar_t__ BWN_MAC_STATUS_STARTED ; 
 int /*<<< orphan*/  BWN_UNLOCK (struct bwn_softc*) ; 
 int ENETDOWN ; 
 int ENOBUFS ; 
 scalar_t__ bwn_tx_isfull (struct bwn_softc*,struct mbuf*) ; 
 int bwn_tx_start (struct bwn_softc*,struct ieee80211_node*,struct mbuf*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 

__attribute__((used)) static int
bwn_raw_xmit(struct ieee80211_node *ni, struct mbuf *m,
	const struct ieee80211_bpf_params *params)
{
	struct ieee80211com *ic = ni->ni_ic;
	struct bwn_softc *sc = ic->ic_softc;
	struct bwn_mac *mac = sc->sc_curmac;
	int error;

	if ((sc->sc_flags & BWN_FLAG_RUNNING) == 0 ||
	    mac->mac_status < BWN_MAC_STATUS_STARTED) {
		m_freem(m);
		return (ENETDOWN);
	}

	BWN_LOCK(sc);
	if (bwn_tx_isfull(sc, m)) {
		m_freem(m);
		BWN_UNLOCK(sc);
		return (ENOBUFS);
	}

	error = bwn_tx_start(sc, ni, m);
	if (error == 0)
		sc->sc_watchdog_timer = 5;
	BWN_UNLOCK(sc);
	return (error);
}