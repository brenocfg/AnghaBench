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
struct ieee80211com {int dummy; } ;
struct iwi_softc {int curchan; struct ieee80211com sc_ic; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_radiotap_chan_change (struct ieee80211com*) ; 

__attribute__((used)) static void
iwi_setcurchan(struct iwi_softc *sc, int chan)
{
	struct ieee80211com *ic = &sc->sc_ic;

	sc->curchan = chan;
	ieee80211_radiotap_chan_change(ic);
}