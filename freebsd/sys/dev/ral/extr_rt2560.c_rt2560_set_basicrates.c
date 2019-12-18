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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct ieee80211com {int /*<<< orphan*/  ic_rt; } ;
struct rt2560_softc {struct ieee80211com sc_ic; } ;
struct ieee80211_rateset {int rs_nrates; int* rs_rates; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (struct rt2560_softc*,char*,int) ; 
 int IEEE80211_RATE_BASIC ; 
 int /*<<< orphan*/  IEEE80211_RV (int) ; 
 int /*<<< orphan*/  RAL_WRITE (struct rt2560_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RT2560_ARSP_PLCP_1 ; 
 int ieee80211_legacy_rate_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rt2560_set_basicrates(struct rt2560_softc *sc,
    const struct ieee80211_rateset *rs)
{
	struct ieee80211com *ic = &sc->sc_ic;
	uint32_t mask = 0;
	uint8_t rate;
	int i;

	for (i = 0; i < rs->rs_nrates; i++) {
		rate = rs->rs_rates[i];

		if (!(rate & IEEE80211_RATE_BASIC))
			continue;

		mask |= 1 << ieee80211_legacy_rate_lookup(ic->ic_rt,
		    IEEE80211_RV(rate));
	}

	RAL_WRITE(sc, RT2560_ARSP_PLCP_1, mask);

	DPRINTF(sc, "Setting basic rate mask to 0x%x\n", mask);
}