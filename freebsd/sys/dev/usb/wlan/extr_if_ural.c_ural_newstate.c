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
struct ural_vap {int (* newstate ) (struct ieee80211vap*,int,int) ;int /*<<< orphan*/  ratectl_ch; } ;
struct ural_softc {int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_bssid; } ;
struct mbuf {int dummy; } ;
struct ieee80211vap {size_t iv_state; struct ieee80211_txparam* iv_txparms; int /*<<< orphan*/  iv_opmode; struct ieee80211_node* iv_bss; struct ieee80211com* iv_ic; } ;
struct ieee80211com {int /*<<< orphan*/  ic_curchan; int /*<<< orphan*/  ic_bsschan; struct ural_softc* ic_softc; } ;
struct ieee80211_txparam {int /*<<< orphan*/  ucastrate; } ;
struct ieee80211_node {int /*<<< orphan*/  ni_bssid; } ;
typedef  enum ieee80211_state { ____Placeholder_ieee80211_state } ieee80211_state ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEEE80211_ADDR_COPY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEEE80211_CHAN_ANYC ; 
 int /*<<< orphan*/  IEEE80211_FIXED_RATE_NONE ; 
 int /*<<< orphan*/  IEEE80211_LOCK (struct ieee80211com*) ; 
 int /*<<< orphan*/  IEEE80211_M_HOSTAP ; 
 int /*<<< orphan*/  IEEE80211_M_IBSS ; 
 int /*<<< orphan*/  IEEE80211_M_MONITOR ; 
#define  IEEE80211_S_INIT 129 
#define  IEEE80211_S_RUN 128 
 int /*<<< orphan*/  IEEE80211_UNLOCK (struct ieee80211com*) ; 
 int /*<<< orphan*/  RAL_LOCK (struct ural_softc*) ; 
 int /*<<< orphan*/  RAL_MAC_CSR20 ; 
 int /*<<< orphan*/  RAL_TXRX_CSR19 ; 
 int /*<<< orphan*/  RAL_UNLOCK (struct ural_softc*) ; 
 struct ural_vap* URAL_VAP (struct ieee80211vap*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 struct mbuf* ieee80211_beacon_alloc (struct ieee80211_node*) ; 
 size_t ieee80211_chan2mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_free_node (struct ieee80211_node*) ; 
 struct ieee80211_node* ieee80211_ref_node (struct ieee80211_node*) ; 
 int /*<<< orphan*/ * ieee80211_state_name ; 
 int stub1 (struct ieee80211vap*,int,int) ; 
 int /*<<< orphan*/  ural_enable_tsf (struct ural_softc*) ; 
 int /*<<< orphan*/  ural_enable_tsf_sync (struct ural_softc*) ; 
 int /*<<< orphan*/  ural_ratectl_start (struct ural_softc*,struct ieee80211_node*) ; 
 int /*<<< orphan*/  ural_set_basicrates (struct ural_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ural_set_bssid (struct ural_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ural_set_txpreamble (struct ural_softc*) ; 
 int /*<<< orphan*/  ural_tx_bcn (struct ural_softc*,struct mbuf*,struct ieee80211_node*) ; 
 int /*<<< orphan*/  ural_update_slot (struct ural_softc*) ; 
 int /*<<< orphan*/  ural_write (struct ural_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_callout_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ural_newstate(struct ieee80211vap *vap, enum ieee80211_state nstate, int arg)
{
	struct ural_vap *uvp = URAL_VAP(vap);
	struct ieee80211com *ic = vap->iv_ic;
	struct ural_softc *sc = ic->ic_softc;
	const struct ieee80211_txparam *tp;
	struct ieee80211_node *ni;
	struct mbuf *m;

	DPRINTF("%s -> %s\n",
		ieee80211_state_name[vap->iv_state],
		ieee80211_state_name[nstate]);

	IEEE80211_UNLOCK(ic);
	RAL_LOCK(sc);
	usb_callout_stop(&uvp->ratectl_ch);

	switch (nstate) {
	case IEEE80211_S_INIT:
		if (vap->iv_state == IEEE80211_S_RUN) {
			/* abort TSF synchronization */
			ural_write(sc, RAL_TXRX_CSR19, 0);

			/* force tx led to stop blinking */
			ural_write(sc, RAL_MAC_CSR20, 0);
		}
		break;

	case IEEE80211_S_RUN:
		ni = ieee80211_ref_node(vap->iv_bss);

		if (vap->iv_opmode != IEEE80211_M_MONITOR) {
			if (ic->ic_bsschan == IEEE80211_CHAN_ANYC)
				goto fail;

			ural_update_slot(sc);
			ural_set_txpreamble(sc);
			ural_set_basicrates(sc, ic->ic_bsschan);
			IEEE80211_ADDR_COPY(sc->sc_bssid, ni->ni_bssid);
			ural_set_bssid(sc, sc->sc_bssid);
		}

		if (vap->iv_opmode == IEEE80211_M_HOSTAP ||
		    vap->iv_opmode == IEEE80211_M_IBSS) {
			m = ieee80211_beacon_alloc(ni);
			if (m == NULL) {
				device_printf(sc->sc_dev,
				    "could not allocate beacon\n");
				goto fail;
			}
			ieee80211_ref_node(ni);
			if (ural_tx_bcn(sc, m, ni) != 0) {
				device_printf(sc->sc_dev,
				    "could not send beacon\n");
				goto fail;
			}
		}

		/* make tx led blink on tx (controlled by ASIC) */
		ural_write(sc, RAL_MAC_CSR20, 1);

		if (vap->iv_opmode != IEEE80211_M_MONITOR)
			ural_enable_tsf_sync(sc);
		else
			ural_enable_tsf(sc);

		/* enable automatic rate adaptation */
		/* XXX should use ic_bsschan but not valid until after newstate call below */
		tp = &vap->iv_txparms[ieee80211_chan2mode(ic->ic_curchan)];
		if (tp->ucastrate == IEEE80211_FIXED_RATE_NONE)
			ural_ratectl_start(sc, ni);
		ieee80211_free_node(ni);
		break;

	default:
		break;
	}
	RAL_UNLOCK(sc);
	IEEE80211_LOCK(ic);
	return (uvp->newstate(vap, nstate, arg));

fail:
	RAL_UNLOCK(sc);
	IEEE80211_LOCK(ic);
	ieee80211_free_node(ni);
	return (-1);
}