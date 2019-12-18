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
struct urtw_softc {int sc_flags; int sc_txtimer; int /*<<< orphan*/  sc_tx_inactive; } ;
struct urtw_data {int dummy; } ;
struct mbuf {int dummy; } ;
struct ieee80211com {struct urtw_softc* ic_softc; } ;
struct ieee80211_node {struct ieee80211com* ni_ic; } ;
struct ieee80211_bpf_params {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int ENETDOWN ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  STAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct urtw_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  URTW_LOCK (struct urtw_softc*) ; 
 int /*<<< orphan*/  URTW_PRIORITY_LOW ; 
 int URTW_RUNNING ; 
 int /*<<< orphan*/  URTW_UNLOCK (struct urtw_softc*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  next ; 
 struct urtw_data* urtw_getbuf (struct urtw_softc*) ; 
 scalar_t__ urtw_tx_start (struct urtw_softc*,struct ieee80211_node*,struct mbuf*,struct urtw_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
urtw_raw_xmit(struct ieee80211_node *ni, struct mbuf *m,
    const struct ieee80211_bpf_params *params)
{
	struct ieee80211com *ic = ni->ni_ic;
	struct urtw_softc *sc = ic->ic_softc;
	struct urtw_data *bf;

	/* prevent management frames from being sent if we're not ready */
	if (!(sc->sc_flags & URTW_RUNNING)) {
		m_freem(m);
		return ENETDOWN;
	}
	URTW_LOCK(sc);
	bf = urtw_getbuf(sc);
	if (bf == NULL) {
		m_freem(m);
		URTW_UNLOCK(sc);
		return (ENOBUFS);		/* XXX */
	}

	if (urtw_tx_start(sc, ni, m, bf, URTW_PRIORITY_LOW) != 0) {
		STAILQ_INSERT_HEAD(&sc->sc_tx_inactive, bf, next);
		URTW_UNLOCK(sc);
		return (EIO);
	}
	URTW_UNLOCK(sc);

	sc->sc_txtimer = 5;
	return (0);
}