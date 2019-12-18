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
struct rum_softc {int /*<<< orphan*/  sc_bssid; } ;
struct ieee80211com {int ic_flags_ext; scalar_t__ ic_opmode; struct rum_softc* ic_softc; } ;

/* Variables and functions */
 int IEEE80211_FEXT_BGSCAN ; 
 scalar_t__ IEEE80211_M_AHDEMO ; 
 int /*<<< orphan*/  RUM_LOCK (struct rum_softc*) ; 
 int /*<<< orphan*/  RUM_UNLOCK (struct rum_softc*) ; 
 int /*<<< orphan*/  rum_enable_tsf (struct rum_softc*) ; 
 int /*<<< orphan*/  rum_enable_tsf_sync (struct rum_softc*) ; 
 int /*<<< orphan*/  rum_set_bssid (struct rum_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rum_scan_end(struct ieee80211com *ic)
{
	struct rum_softc *sc = ic->ic_softc;

	if (ic->ic_flags_ext & IEEE80211_FEXT_BGSCAN) {
		RUM_LOCK(sc);
		if (ic->ic_opmode != IEEE80211_M_AHDEMO)
			rum_enable_tsf_sync(sc);
		else
			rum_enable_tsf(sc);
		rum_set_bssid(sc, sc->sc_bssid);
		RUM_UNLOCK(sc);
	}
}