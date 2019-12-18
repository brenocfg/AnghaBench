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
struct ieee80211com {int ic_htcaps; } ;
struct rtwn_softc {struct ieee80211com sc_ic; struct r12a_softc* sc_priv; } ;
struct r12a_softc {int chip; } ;

/* Variables and functions */
 int IEEE80211_HTCAP_LDPC ; 
 int IEEE80211_HTC_TXLDPC ; 
 int R12A_CHIP_C_CUT ; 

__attribute__((used)) static void
r12au_adj_devcaps(struct rtwn_softc *sc)
{
	struct r12a_softc *rs = sc->sc_priv;
	struct ieee80211com *ic = &sc->sc_ic;

	if (rs->chip & R12A_CHIP_C_CUT) {
		ic->ic_htcaps |= IEEE80211_HTCAP_LDPC |
				 IEEE80211_HTC_TXLDPC;
	}

	/* TODO: STBC, VHT etc */
}