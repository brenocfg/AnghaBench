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
struct rsu_softc {int /*<<< orphan*/  sc_running; } ;
struct rsu_data {int dummy; } ;
struct mbuf {int dummy; } ;
struct ieee80211com {struct rsu_softc* ic_softc; } ;
struct ieee80211_node {struct ieee80211com* ni_ic; } ;
struct ieee80211_bpf_params {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int ENETDOWN ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  RSU_LOCK (struct rsu_softc*) ; 
 int /*<<< orphan*/  RSU_UNLOCK (struct rsu_softc*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  rsu_freebuf (struct rsu_softc*,struct rsu_data*) ; 
 struct rsu_data* rsu_getbuf (struct rsu_softc*) ; 
 scalar_t__ rsu_tx_start (struct rsu_softc*,struct ieee80211_node*,struct mbuf*,struct rsu_data*) ; 

__attribute__((used)) static int	
rsu_raw_xmit(struct ieee80211_node *ni, struct mbuf *m, 
    const struct ieee80211_bpf_params *params)
{
	struct ieee80211com *ic = ni->ni_ic;
	struct rsu_softc *sc = ic->ic_softc;
	struct rsu_data *bf;

	/* prevent management frames from being sent if we're not ready */
	if (!sc->sc_running) {
		m_freem(m);
		return (ENETDOWN);
	}
	RSU_LOCK(sc);
	bf = rsu_getbuf(sc);
	if (bf == NULL) {
		m_freem(m);
		RSU_UNLOCK(sc);
		return (ENOBUFS);
	}
	if (rsu_tx_start(sc, ni, m, bf) != 0) {
		m_freem(m);
		rsu_freebuf(sc, bf);
		RSU_UNLOCK(sc);
		return (EIO);
	}
	RSU_UNLOCK(sc);

	return (0);
}