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
struct rtwn_vap {int /*<<< orphan*/  id; int /*<<< orphan*/  tsf_sync_adhoc_task; } ;
struct ieee80211com {int dummy; } ;
struct rtwn_softc {int /*<<< orphan*/  sc_dev; struct ieee80211com sc_ic; } ;
struct ieee80211vap {int iv_opmode; } ;

/* Variables and functions */
#define  IEEE80211_M_HOSTAP 130 
#define  IEEE80211_M_IBSS 129 
#define  IEEE80211_M_STA 128 
 int /*<<< orphan*/  R92C_BCN_CTRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R92C_BCN_CTRL_DIS_TSF_UDT0 ; 
 int /*<<< orphan*/  R92C_DUAL_TSF_RESET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R92C_DUAL_TSF_RST ; 
 struct rtwn_vap* RTWN_VAP (struct ieee80211vap*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ieee80211_runtask (struct ieee80211com*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtwn_beacon_enable (struct rtwn_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtwn_setbits_1 (struct rtwn_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtwn_write_1 (struct rtwn_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rtwn_tsf_sync_enable(struct rtwn_softc *sc, struct ieee80211vap *vap)
{
	struct ieee80211com *ic = &sc->sc_ic;
	struct rtwn_vap *uvp = RTWN_VAP(vap);

	/* Reset TSF. */
	rtwn_write_1(sc, R92C_DUAL_TSF_RST, R92C_DUAL_TSF_RESET(uvp->id));

	switch (vap->iv_opmode) {
	case IEEE80211_M_STA:
		/* Enable TSF synchronization. */
		rtwn_setbits_1(sc, R92C_BCN_CTRL(uvp->id),
		    R92C_BCN_CTRL_DIS_TSF_UDT0, 0);
		break;
	case IEEE80211_M_IBSS:
		ieee80211_runtask(ic, &uvp->tsf_sync_adhoc_task);
		/* FALLTHROUGH */
	case IEEE80211_M_HOSTAP:
		/* Enable beaconing. */
		rtwn_beacon_enable(sc, uvp->id, 1);
		break;
	default:
		device_printf(sc->sc_dev, "undefined opmode %d\n",
		    vap->iv_opmode);
		return;
	}
}