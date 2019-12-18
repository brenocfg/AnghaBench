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
struct ieee80211com {int /*<<< orphan*/  ic_curchan; } ;
struct mwl_softc {int /*<<< orphan*/  sc_mh; struct ieee80211com sc_ic; } ;
struct ieee80211_rateset {int* rs_rates; } ;
typedef  int /*<<< orphan*/  rates ;
struct TYPE_4__ {int MgtRate; int McastRate; } ;
typedef  TYPE_1__ MWL_HAL_TXRATE ;

/* Variables and functions */
 int IEEE80211_RATE_VAL ; 
 struct ieee80211_rateset* ieee80211_get_suprates (struct ieee80211com*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int mwl_hal_settxrate_auto (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int
mwl_setcurchanrates(struct mwl_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;
	const struct ieee80211_rateset *rs;
	MWL_HAL_TXRATE rates;

	memset(&rates, 0, sizeof(rates));
	rs = ieee80211_get_suprates(ic, ic->ic_curchan);
	/* rate used to send management frames */
	rates.MgtRate = rs->rs_rates[0] & IEEE80211_RATE_VAL;
	/* rate used to send multicast frames */
	rates.McastRate = rates.MgtRate;

	return mwl_hal_settxrate_auto(sc->sc_mh, &rates);
}