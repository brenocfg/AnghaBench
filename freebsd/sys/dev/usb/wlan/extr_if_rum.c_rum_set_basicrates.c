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
struct ieee80211com {scalar_t__ ic_curmode; int /*<<< orphan*/  ic_bsschan; } ;
struct rum_softc {struct ieee80211com sc_ic; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_IS_CHAN_5GHZ (int /*<<< orphan*/ ) ; 
 scalar_t__ IEEE80211_MODE_11B ; 
 int /*<<< orphan*/  RT2573_TXRX_CSR5 ; 
 int /*<<< orphan*/  rum_write (struct rum_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
rum_set_basicrates(struct rum_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;

	/* update basic rate set */
	if (ic->ic_curmode == IEEE80211_MODE_11B) {
		/* 11b basic rates: 1, 2Mbps */
		rum_write(sc, RT2573_TXRX_CSR5, 0x3);
	} else if (IEEE80211_IS_CHAN_5GHZ(ic->ic_bsschan)) {
		/* 11a basic rates: 6, 12, 24Mbps */
		rum_write(sc, RT2573_TXRX_CSR5, 0x150);
	} else {
		/* 11b/g basic rates: 1, 2, 5.5, 11Mbps */
		rum_write(sc, RT2573_TXRX_CSR5, 0xf);
	}
}