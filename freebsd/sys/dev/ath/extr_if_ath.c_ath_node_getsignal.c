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
struct ieee80211com {int (* ic_node_getrssi ) (struct ieee80211_node const*) ;struct ath_softc* ic_softc; } ;
struct ieee80211_node {int /*<<< orphan*/  ni_chan; struct ieee80211com* ni_ic; } ;
struct ath_softc {struct ath_hal* sc_ah; } ;
struct ath_hal {int dummy; } ;
typedef  int int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_CHAN_ANYC ; 
 int ath_hal_getchannoise (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int stub1 (struct ieee80211_node const*) ; 

__attribute__((used)) static void
ath_node_getsignal(const struct ieee80211_node *ni, int8_t *rssi, int8_t *noise)
{
	struct ieee80211com *ic = ni->ni_ic;
	struct ath_softc *sc = ic->ic_softc;
	struct ath_hal *ah = sc->sc_ah;

	*rssi = ic->ic_node_getrssi(ni);
	if (ni->ni_chan != IEEE80211_CHAN_ANYC)
		*noise = ath_hal_getchannoise(ah, ni->ni_chan);
	else
		*noise = -95;		/* nominally correct */
}