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
struct ieee80211com {scalar_t__ ic_opmode; struct ath_softc* ic_softc; } ;
struct ath_softc {int /*<<< orphan*/  sc_updateslot; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_M_HOSTAP ; 
 scalar_t__ IEEE80211_M_MBSS ; 
 int /*<<< orphan*/  UPDATE ; 
 int /*<<< orphan*/  ath_setslottime (struct ath_softc*) ; 

__attribute__((used)) static void
ath_updateslot(struct ieee80211com *ic)
{
	struct ath_softc *sc = ic->ic_softc;

	/*
	 * When not coordinating the BSS, change the hardware
	 * immediately.  For other operation we defer the change
	 * until beacon updates have propagated to the stations.
	 *
	 * XXX sc_updateslot isn't changed behind a lock?
	 */
	if (ic->ic_opmode == IEEE80211_M_HOSTAP ||
	    ic->ic_opmode == IEEE80211_M_MBSS)
		sc->sc_updateslot = UPDATE;
	else
		ath_setslottime(sc);
}