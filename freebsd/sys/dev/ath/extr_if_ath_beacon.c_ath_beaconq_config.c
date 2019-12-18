#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wmeParams {int /*<<< orphan*/  wmep_logcwmax; int /*<<< orphan*/  wmep_logcwmin; int /*<<< orphan*/  wmep_aifsn; } ;
struct ieee80211com {scalar_t__ ic_opmode; } ;
struct chanAccParams {struct wmeParams* cap_wmeParams; } ;
struct ath_softc {int /*<<< orphan*/  sc_bhalq; int /*<<< orphan*/  sc_dev; struct ath_hal* sc_ah; struct ieee80211com sc_ic; } ;
struct ath_hal {int dummy; } ;
struct TYPE_4__ {int tqi_cwmin; int tqi_cwmax; int /*<<< orphan*/  tqi_aifs; } ;
typedef  TYPE_1__ HAL_TXQ_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_BEACON_AIFS_DEFAULT ; 
 int ATH_BEACON_CWMAX_DEFAULT ; 
 int ATH_BEACON_CWMIN_DEFAULT ; 
 int ATH_EXPONENT_TO_VALUE (int /*<<< orphan*/ ) ; 
 scalar_t__ IEEE80211_M_HOSTAP ; 
 scalar_t__ IEEE80211_M_MBSS ; 
 size_t WME_AC_BE ; 
 int /*<<< orphan*/  ath_hal_gettxqueueprops (struct ath_hal*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ath_hal_resettxqueue (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_hal_settxqueueprops (struct ath_hal*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ieee80211_wme_ic_getparams (struct ieee80211com*,struct chanAccParams*) ; 

int
ath_beaconq_config(struct ath_softc *sc)
{
#define	ATH_EXPONENT_TO_VALUE(v)	((1<<(v))-1)
	struct ieee80211com *ic = &sc->sc_ic;
	struct ath_hal *ah = sc->sc_ah;
	HAL_TXQ_INFO qi;

	ath_hal_gettxqueueprops(ah, sc->sc_bhalq, &qi);
	if (ic->ic_opmode == IEEE80211_M_HOSTAP ||
	    ic->ic_opmode == IEEE80211_M_MBSS) {
		/*
		 * Always burst out beacon and CAB traffic.
		 */
		qi.tqi_aifs = ATH_BEACON_AIFS_DEFAULT;
		qi.tqi_cwmin = ATH_BEACON_CWMIN_DEFAULT;
		qi.tqi_cwmax = ATH_BEACON_CWMAX_DEFAULT;
	} else {
		struct chanAccParams chp;
		struct wmeParams *wmep;

		ieee80211_wme_ic_getparams(ic, &chp);
		wmep = &chp.cap_wmeParams[WME_AC_BE];

		/*
		 * Adhoc mode; important thing is to use 2x cwmin.
		 */
		qi.tqi_aifs = wmep->wmep_aifsn;
		qi.tqi_cwmin = 2*ATH_EXPONENT_TO_VALUE(wmep->wmep_logcwmin);
		qi.tqi_cwmax = ATH_EXPONENT_TO_VALUE(wmep->wmep_logcwmax);
	}

	if (!ath_hal_settxqueueprops(ah, sc->sc_bhalq, &qi)) {
		device_printf(sc->sc_dev, "unable to update parameters for "
			"beacon hardware queue!\n");
		return 0;
	} else {
		ath_hal_resettxqueue(ah, sc->sc_bhalq); /* push to h/w */
		return 1;
	}
#undef ATH_EXPONENT_TO_VALUE
}