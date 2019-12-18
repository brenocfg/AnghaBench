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
struct rsu_softc {int sc_active_scan; int /*<<< orphan*/  sc_dev; } ;
struct ieee80211vap {int dummy; } ;
struct ieee80211com {int /*<<< orphan*/  ic_vaps; struct ieee80211_scan_state* ic_scan; struct rsu_softc* ic_softc; } ;
struct ieee80211_scan_state {int ss_flags; scalar_t__ ss_nssid; int /*<<< orphan*/ * ss_ssid; } ;

/* Variables and functions */
 int IEEE80211_SCAN_ACTIVE ; 
 int /*<<< orphan*/  RSU_LOCK (struct rsu_softc*) ; 
 int /*<<< orphan*/  RSU_UNLOCK (struct rsu_softc*) ; 
 struct ieee80211vap* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ieee80211_cancel_scan (struct ieee80211vap*) ; 
 int rsu_site_survey (struct rsu_softc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
rsu_scan_start(struct ieee80211com *ic)
{
	struct rsu_softc *sc = ic->ic_softc;
	struct ieee80211_scan_state *ss = ic->ic_scan;
	struct ieee80211vap *vap = TAILQ_FIRST(&ic->ic_vaps);
	int error;

	/* Scanning is done by the firmware. */
	RSU_LOCK(sc);
	sc->sc_active_scan = !!(ss->ss_flags & IEEE80211_SCAN_ACTIVE);
	/* XXX TODO: force awake if in network-sleep? */
	error = rsu_site_survey(sc, ss->ss_nssid > 0 ? &ss->ss_ssid[0] : NULL);
	RSU_UNLOCK(sc);
	if (error != 0) {
		device_printf(sc->sc_dev,
		    "could not send site survey command\n");
		ieee80211_cancel_scan(vap);
	}
}