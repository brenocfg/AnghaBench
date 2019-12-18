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
struct ieee80211com {int /*<<< orphan*/  ic_bsschan; } ;
struct rum_softc {struct ieee80211com sc_ic; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_IS_CHAN_5GHZ (int /*<<< orphan*/ ) ; 
 int RT2573_MRR_CCK_FALLBACK ; 
 int RT2573_MRR_ENABLED ; 
 int /*<<< orphan*/  RT2573_TXRX_CSR4 ; 
 int /*<<< orphan*/  rum_modbits (struct rum_softc*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rum_setbits (struct rum_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
rum_enable_mrr(struct rum_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;

	if (!IEEE80211_IS_CHAN_5GHZ(ic->ic_bsschan)) {
		rum_setbits(sc, RT2573_TXRX_CSR4,
		    RT2573_MRR_ENABLED | RT2573_MRR_CCK_FALLBACK);
	} else {
		rum_modbits(sc, RT2573_TXRX_CSR4,
		    RT2573_MRR_ENABLED, RT2573_MRR_CCK_FALLBACK);
	}
}