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
struct ieee80211com {int ic_cryptocaps; int ic_flags; } ;
struct ath_softc {int /*<<< orphan*/  sc_ah; int /*<<< orphan*/  sc_wmetkipmic; struct ieee80211com sc_ic; } ;

/* Variables and functions */
 int /*<<< orphan*/  AH_FALSE ; 
 int /*<<< orphan*/  AH_TRUE ; 
 int IEEE80211_CRYPTO_TKIP ; 
 int IEEE80211_CRYPTO_TKIPMIC ; 
 int IEEE80211_F_WME ; 
 int /*<<< orphan*/  ath_hal_settkipmic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ath_settkipmic(struct ath_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;

	if ((ic->ic_cryptocaps & IEEE80211_CRYPTO_TKIP) && !sc->sc_wmetkipmic) {
		if (ic->ic_flags & IEEE80211_F_WME) {
			ath_hal_settkipmic(sc->sc_ah, AH_FALSE);
			ic->ic_cryptocaps &= ~IEEE80211_CRYPTO_TKIPMIC;
		} else {
			ath_hal_settkipmic(sc->sc_ah, AH_TRUE);
			ic->ic_cryptocaps |= IEEE80211_CRYPTO_TKIPMIC;
		}
	}
}