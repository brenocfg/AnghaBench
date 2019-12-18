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
struct ieee80211com {int ic_flags; } ;
struct rum_softc {struct ieee80211com sc_ic; } ;

/* Variables and functions */
 int IEEE80211_F_SHPREAMBLE ; 
 int /*<<< orphan*/  RT2573_SHORT_PREAMBLE ; 
 int /*<<< orphan*/  RT2573_TXRX_CSR4 ; 
 int /*<<< orphan*/  rum_clrbits (struct rum_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rum_setbits (struct rum_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rum_set_txpreamble(struct rum_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;

	if (ic->ic_flags & IEEE80211_F_SHPREAMBLE)
		rum_setbits(sc, RT2573_TXRX_CSR4, RT2573_SHORT_PREAMBLE);
	else
		rum_clrbits(sc, RT2573_TXRX_CSR4, RT2573_SHORT_PREAMBLE);
}