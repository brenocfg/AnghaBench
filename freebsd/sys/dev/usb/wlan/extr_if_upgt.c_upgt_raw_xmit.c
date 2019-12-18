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
struct upgt_softc {int sc_flags; int sc_tx_timer; int /*<<< orphan*/  sc_tx_inactive; } ;
struct upgt_data {int dummy; } ;
struct mbuf {int dummy; } ;
struct ieee80211com {struct upgt_softc* ic_softc; } ;
struct ieee80211_node {struct ieee80211com* ni_ic; } ;
struct ieee80211_bpf_params {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int ENETDOWN ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  STAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct upgt_data*,int /*<<< orphan*/ ) ; 
 int UPGT_FLAG_INITDONE ; 
 int /*<<< orphan*/  UPGT_LOCK (struct upgt_softc*) ; 
 int /*<<< orphan*/  UPGT_STAT_INC (struct upgt_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPGT_UNLOCK (struct upgt_softc*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  st_tx_inactive ; 
 struct upgt_data* upgt_gettxbuf (struct upgt_softc*) ; 
 scalar_t__ upgt_tx_start (struct upgt_softc*,struct mbuf*,struct ieee80211_node*,struct upgt_data*) ; 

__attribute__((used)) static int
upgt_raw_xmit(struct ieee80211_node *ni, struct mbuf *m,
	const struct ieee80211_bpf_params *params)
{
	struct ieee80211com *ic = ni->ni_ic;
	struct upgt_softc *sc = ic->ic_softc;
	struct upgt_data *data_tx = NULL;

	UPGT_LOCK(sc);
	/* prevent management frames from being sent if we're not ready */
	if (!(sc->sc_flags & UPGT_FLAG_INITDONE)) {
		m_freem(m);
		UPGT_UNLOCK(sc);
		return ENETDOWN;
	}

	data_tx = upgt_gettxbuf(sc);
	if (data_tx == NULL) {
		m_freem(m);
		UPGT_UNLOCK(sc);
		return (ENOBUFS);
	}

	if (upgt_tx_start(sc, m, ni, data_tx) != 0) {
		STAILQ_INSERT_HEAD(&sc->sc_tx_inactive, data_tx, next);
		UPGT_STAT_INC(sc, st_tx_inactive);
		UPGT_UNLOCK(sc);
		return (EIO);
	}
	UPGT_UNLOCK(sc);

	sc->sc_tx_timer = 5;
	return (0);
}