#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rtwn_softc {int /*<<< orphan*/  (* sc_scan_curchan ) (struct ieee80211_scan_state*,unsigned long) ;int /*<<< orphan*/  ledlink; } ;
struct ieee80211_scan_state {TYPE_1__* ss_ic; } ;
struct TYPE_2__ {struct rtwn_softc* ic_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTWN_LED_LINK ; 
 int /*<<< orphan*/  RTWN_LOCK (struct rtwn_softc*) ; 
 int /*<<< orphan*/  RTWN_UNLOCK (struct rtwn_softc*) ; 
 int /*<<< orphan*/  rtwn_set_led (struct rtwn_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_scan_state*,unsigned long) ; 

__attribute__((used)) static void
rtwn_scan_curchan(struct ieee80211_scan_state *ss, unsigned long maxdwell)
{
	struct rtwn_softc *sc = ss->ss_ic->ic_softc;

	/* Make link LED blink during scan. */
	RTWN_LOCK(sc);
	rtwn_set_led(sc, RTWN_LED_LINK, !sc->ledlink);
	RTWN_UNLOCK(sc);

	sc->sc_scan_curchan(ss, maxdwell);
}