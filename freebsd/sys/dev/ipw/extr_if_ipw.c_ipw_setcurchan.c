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
struct ieee80211com {struct ieee80211_channel* ic_curchan; } ;
struct ipw_softc {struct ieee80211com sc_ic; } ;
struct ieee80211_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_radiotap_chan_change (struct ieee80211com*) ; 

__attribute__((used)) static void
ipw_setcurchan(struct ipw_softc *sc, struct ieee80211_channel *chan)
{
	struct ieee80211com *ic = &sc->sc_ic;

	ic->ic_curchan = chan;
	ieee80211_radiotap_chan_change(ic);
}