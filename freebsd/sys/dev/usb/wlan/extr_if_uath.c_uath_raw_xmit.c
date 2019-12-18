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
struct uath_softc {int sc_flags; int sc_tx_timer; int /*<<< orphan*/  sc_tx_inactive; scalar_t__ sc_seqnum; } ;
struct uath_data {int dummy; } ;
struct mbuf {int dummy; } ;
struct ieee80211com {struct uath_softc* ic_softc; } ;
struct ieee80211_node {struct ieee80211com* ni_ic; } ;
struct ieee80211_bpf_params {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int ENETDOWN ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  STAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct uath_data*,int /*<<< orphan*/ ) ; 
 int UATH_FLAG_INITDONE ; 
 int UATH_FLAG_INVALID ; 
 int /*<<< orphan*/  UATH_LOCK (struct uath_softc*) ; 
 int /*<<< orphan*/  UATH_STAT_INC (struct uath_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UATH_UNLOCK (struct uath_softc*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  st_tx_inactive ; 
 struct uath_data* uath_getbuf (struct uath_softc*) ; 
 scalar_t__ uath_tx_start (struct uath_softc*,struct mbuf*,struct ieee80211_node*,struct uath_data*) ; 

__attribute__((used)) static int
uath_raw_xmit(struct ieee80211_node *ni, struct mbuf *m,
    const struct ieee80211_bpf_params *params)
{
	struct ieee80211com *ic = ni->ni_ic;
	struct uath_data *bf;
	struct uath_softc *sc = ic->ic_softc;

	UATH_LOCK(sc);
	/* prevent management frames from being sent if we're not ready */
	if ((sc->sc_flags & UATH_FLAG_INVALID) ||
	    !(sc->sc_flags & UATH_FLAG_INITDONE)) {
		m_freem(m);
		UATH_UNLOCK(sc);
		return (ENETDOWN);
	}

	/* grab a TX buffer  */
	bf = uath_getbuf(sc);
	if (bf == NULL) {
		m_freem(m);
		UATH_UNLOCK(sc);
		return (ENOBUFS);
	}

	sc->sc_seqnum = 0;
	if (uath_tx_start(sc, m, ni, bf) != 0) {
		STAILQ_INSERT_HEAD(&sc->sc_tx_inactive, bf, next);
		UATH_STAT_INC(sc, st_tx_inactive);
		UATH_UNLOCK(sc);
		return (EIO);
	}
	UATH_UNLOCK(sc);

	sc->sc_tx_timer = 5;
	return (0);
}