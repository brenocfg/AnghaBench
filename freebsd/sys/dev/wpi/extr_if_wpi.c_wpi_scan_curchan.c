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
struct wpi_softc {int dummy; } ;
struct ieee80211vap {struct ieee80211com* iv_ic; } ;
struct ieee80211com {int /*<<< orphan*/  ic_curchan; struct wpi_softc* ic_softc; } ;
struct ieee80211_scan_state {struct ieee80211vap* ss_vap; } ;

/* Variables and functions */
 int /*<<< orphan*/  WPI_RXON_LOCK (struct wpi_softc*) ; 
 int /*<<< orphan*/  WPI_RXON_UNLOCK (struct wpi_softc*) ; 
 int /*<<< orphan*/  ieee80211_cancel_scan (struct ieee80211vap*) ; 
 int wpi_scan (struct wpi_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
wpi_scan_curchan(struct ieee80211_scan_state *ss, unsigned long maxdwell)
{
	struct ieee80211vap *vap = ss->ss_vap;
	struct ieee80211com *ic = vap->iv_ic;
	struct wpi_softc *sc = ic->ic_softc;
	int error;

	WPI_RXON_LOCK(sc);
	error = wpi_scan(sc, ic->ic_curchan);
	WPI_RXON_UNLOCK(sc);
	if (error != 0)
		ieee80211_cancel_scan(vap);
}