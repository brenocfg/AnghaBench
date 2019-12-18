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
struct iwn_softc {int dummy; } ;
struct ieee80211vap {scalar_t__ iv_state; } ;
struct ieee80211com {int /*<<< orphan*/  ic_vaps; struct iwn_softc* ic_softc; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_S_RUN ; 
 int /*<<< orphan*/  IWN_LED_LINK ; 
 int /*<<< orphan*/  IWN_LOCK (struct iwn_softc*) ; 
 int /*<<< orphan*/  IWN_UNLOCK (struct iwn_softc*) ; 
 struct ieee80211vap* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwn_set_led (struct iwn_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
iwn_scan_end(struct ieee80211com *ic)
{
	struct iwn_softc *sc = ic->ic_softc;
	struct ieee80211vap *vap = TAILQ_FIRST(&ic->ic_vaps);

	IWN_LOCK(sc);
	if (vap->iv_state == IEEE80211_S_RUN) {
		/* Set link LED to ON status if we are associated */
		iwn_set_led(sc, IWN_LED_LINK, 0, 1);
	}
	IWN_UNLOCK(sc);
}