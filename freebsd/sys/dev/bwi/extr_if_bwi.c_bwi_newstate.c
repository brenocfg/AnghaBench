#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ieee80211vap {int iv_state; scalar_t__ iv_opmode; TYPE_1__* iv_bss; struct ieee80211com* iv_ic; } ;
struct ieee80211com {scalar_t__ ic_opmode; struct bwi_softc* ic_softc; } ;
struct bwi_vap {int (* bv_newstate ) (struct ieee80211vap*,int,int) ;} ;
struct bwi_softc {int sc_flags; int /*<<< orphan*/  sc_calib_ch; int /*<<< orphan*/  sc_txpwrcb_type; TYPE_2__* sc_cur_regwin; } ;
struct bwi_mac {int dummy; } ;
typedef  enum ieee80211_state { ____Placeholder_ieee80211_state } ieee80211_state ;
struct TYPE_4__ {scalar_t__ rw_type; } ;
struct TYPE_3__ {int /*<<< orphan*/  ni_bssid; } ;

/* Variables and functions */
 int BWI_F_STOP ; 
 int /*<<< orphan*/  BWI_LOCK (struct bwi_softc*) ; 
 scalar_t__ BWI_REGWIN_T_MAC ; 
 int /*<<< orphan*/  BWI_TXPWR_CALIB ; 
 int /*<<< orphan*/  BWI_TXPWR_FORCE ; 
 int /*<<< orphan*/  BWI_TXPWR_INIT ; 
 int /*<<< orphan*/  BWI_UNLOCK (struct bwi_softc*) ; 
 struct bwi_vap* BWI_VAP (struct ieee80211vap*) ; 
 scalar_t__ IEEE80211_M_MONITOR ; 
 scalar_t__ IEEE80211_M_STA ; 
 int IEEE80211_S_INIT ; 
 int IEEE80211_S_RUN ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  bwi_calibrate ; 
 int /*<<< orphan*/  bwi_led_newstate (struct bwi_softc*,int) ; 
 int /*<<< orphan*/  bwi_mac_calibrate_txpower (struct bwi_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwi_set_bssid (struct bwi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwi_zero_addr ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bwi_softc*) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hz ; 
 int stub1 (struct ieee80211vap*,int,int) ; 

__attribute__((used)) static int
bwi_newstate(struct ieee80211vap *vap, enum ieee80211_state nstate, int arg)
{
	struct bwi_vap *bvp = BWI_VAP(vap);
	struct ieee80211com *ic= vap->iv_ic;
	struct bwi_softc *sc = ic->ic_softc;
	enum ieee80211_state ostate = vap->iv_state;
	struct bwi_mac *mac;
	int error;

	BWI_LOCK(sc);

	callout_stop(&sc->sc_calib_ch);

	if (nstate == IEEE80211_S_INIT)
		sc->sc_txpwrcb_type = BWI_TXPWR_INIT;

	bwi_led_newstate(sc, nstate);

	error = bvp->bv_newstate(vap, nstate, arg);
	if (error != 0)
		goto back;

	/*
	 * Clear the BSSID when we stop a STA
	 */
	if (vap->iv_opmode == IEEE80211_M_STA) {
		if (ostate == IEEE80211_S_RUN && nstate != IEEE80211_S_RUN) {
			/*
			 * Clear out the BSSID.  If we reassociate to
			 * the same AP, this will reinialize things
			 * correctly...
			 */
			if (ic->ic_opmode == IEEE80211_M_STA && 
			    !(sc->sc_flags & BWI_F_STOP))
				bwi_set_bssid(sc, bwi_zero_addr);
		}
	}

	if (vap->iv_opmode == IEEE80211_M_MONITOR) {
		/* Nothing to do */
	} else if (nstate == IEEE80211_S_RUN) {
		bwi_set_bssid(sc, vap->iv_bss->ni_bssid);

		KASSERT(sc->sc_cur_regwin->rw_type == BWI_REGWIN_T_MAC,
		    ("current regwin type %d", sc->sc_cur_regwin->rw_type));
		mac = (struct bwi_mac *)sc->sc_cur_regwin;

		/* Initial TX power calibration */
		bwi_mac_calibrate_txpower(mac, BWI_TXPWR_INIT);
#ifdef notyet
		sc->sc_txpwrcb_type = BWI_TXPWR_FORCE;
#else
		sc->sc_txpwrcb_type = BWI_TXPWR_CALIB;
#endif

		callout_reset(&sc->sc_calib_ch, hz, bwi_calibrate, sc);
	}
back:
	BWI_UNLOCK(sc);

	return error;
}