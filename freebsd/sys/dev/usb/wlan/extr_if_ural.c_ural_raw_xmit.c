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
struct ural_softc {scalar_t__ tx_nfree; int /*<<< orphan*/  sc_running; } ;
struct mbuf {int dummy; } ;
struct ieee80211com {struct ural_softc* ic_softc; } ;
struct ieee80211_node {struct ieee80211com* ni_ic; } ;
struct ieee80211_bpf_params {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int ENETDOWN ; 
 int /*<<< orphan*/  RAL_LOCK (struct ural_softc*) ; 
 scalar_t__ RAL_TX_MINFREE ; 
 int /*<<< orphan*/  RAL_UNLOCK (struct ural_softc*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 scalar_t__ ural_tx_mgt (struct ural_softc*,struct mbuf*,struct ieee80211_node*) ; 
 scalar_t__ ural_tx_raw (struct ural_softc*,struct mbuf*,struct ieee80211_node*,struct ieee80211_bpf_params const*) ; 

__attribute__((used)) static int
ural_raw_xmit(struct ieee80211_node *ni, struct mbuf *m,
	const struct ieee80211_bpf_params *params)
{
	struct ieee80211com *ic = ni->ni_ic;
	struct ural_softc *sc = ic->ic_softc;

	RAL_LOCK(sc);
	/* prevent management frames from being sent if we're not ready */
	if (!sc->sc_running) {
		RAL_UNLOCK(sc);
		m_freem(m);
		return ENETDOWN;
	}
	if (sc->tx_nfree < RAL_TX_MINFREE) {
		RAL_UNLOCK(sc);
		m_freem(m);
		return EIO;
	}

	if (params == NULL) {
		/*
		 * Legacy path; interpret frame contents to decide
		 * precisely how to send the frame.
		 */
		if (ural_tx_mgt(sc, m, ni) != 0)
			goto bad;
	} else {
		/*
		 * Caller supplied explicit parameters to use in
		 * sending the frame.
		 */
		if (ural_tx_raw(sc, m, ni, params) != 0)
			goto bad;
	}
	RAL_UNLOCK(sc);
	return 0;
bad:
	RAL_UNLOCK(sc);
	return EIO;		/* XXX */
}