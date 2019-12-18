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
typedef  int uint32_t ;
struct ieee80211com {scalar_t__ ic_promisc; } ;
struct rtwn_softc {scalar_t__ bcn_vaps; scalar_t__ ap_vaps; scalar_t__ mon_vaps; int rcr; struct ieee80211com sc_ic; } ;

/* Variables and functions */
 int R92C_RCR_AAP ; 
 int R92C_RCR_ACF ; 
 int R92C_RCR_ADF ; 
 int R92C_RCR_AMF ; 
 int R92C_RCR_APM ; 
 int R92C_RCR_CBSSID_BCN ; 
 int R92C_RCR_CBSSID_DATA ; 
 int /*<<< orphan*/  RTWN_ASSERT_LOCKED (struct rtwn_softc*) ; 
 int /*<<< orphan*/  rtwn_rxfilter_set (struct rtwn_softc*) ; 

void
rtwn_set_promisc(struct rtwn_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;
	uint32_t mask_all, mask_min;

	RTWN_ASSERT_LOCKED(sc);

	mask_all = R92C_RCR_ACF | R92C_RCR_ADF | R92C_RCR_AMF | R92C_RCR_AAP;
	mask_min = R92C_RCR_APM;

	if (sc->bcn_vaps == 0)
		mask_min |= R92C_RCR_CBSSID_BCN;
	if (sc->ap_vaps == 0)
		mask_min |= R92C_RCR_CBSSID_DATA;

	if (ic->ic_promisc == 0 && sc->mon_vaps == 0) {
		if (sc->bcn_vaps != 0)
			mask_all |= R92C_RCR_CBSSID_BCN;
		if (sc->ap_vaps != 0)	/* for Null data frames */
			mask_all |= R92C_RCR_CBSSID_DATA;

		sc->rcr &= ~mask_all;
		sc->rcr |= mask_min;
	} else {
		sc->rcr &= ~mask_min;
		sc->rcr |= mask_all;
	}
	rtwn_rxfilter_set(sc);
}