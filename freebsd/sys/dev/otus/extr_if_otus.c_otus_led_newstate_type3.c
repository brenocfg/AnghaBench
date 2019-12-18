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
struct ieee80211com {int /*<<< orphan*/  ic_vaps; } ;
struct otus_softc {int led_state; int /*<<< orphan*/  sc_curchan; struct ieee80211com sc_ic; } ;
struct ieee80211vap {scalar_t__ iv_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_GPIO_REG_PORT_DATA ; 
 int AR_LED0_ON ; 
 int AR_LED1_ON ; 
 scalar_t__ IEEE80211_IS_CHAN_2GHZ (int /*<<< orphan*/ ) ; 
 scalar_t__ IEEE80211_S_INIT ; 
 scalar_t__ IEEE80211_S_RUN ; 
 int /*<<< orphan*/  OTUS_LOCK_ASSERT (struct otus_softc*) ; 
 struct ieee80211vap* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  otus_write (struct otus_softc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ otus_write_barrier (struct otus_softc*) ; 

void
otus_led_newstate_type3(struct otus_softc *sc)
{
#if 0
	struct ieee80211com *ic = &sc->sc_ic;
	struct ieee80211vap *vap = TAILQ_FIRST(&ic->ic_vaps);

	uint32_t state = sc->led_state;

	OTUS_LOCK_ASSERT(sc);

	if (!vap) {
		state = 0;	/* led off */
	} else if (vap->iv_state == IEEE80211_S_INIT) {
		state = 0;	/* LED off. */
	} else if (vap->iv_state == IEEE80211_S_RUN) {
		/* Associated, LED always on. */
		if (IEEE80211_IS_CHAN_2GHZ(sc->sc_curchan))
			state = AR_LED0_ON;	/* 2GHz=>Red. */
		else
			state = AR_LED1_ON;	/* 5GHz=>Blue. */
	} else {
		/* Scanning, blink LED. */
		state ^= AR_LED0_ON | AR_LED1_ON;
		if (IEEE80211_IS_CHAN_2GHZ(sc->sc_curchan))
			state &= ~AR_LED1_ON;
		else
			state &= ~AR_LED0_ON;
	}
	if (state != sc->led_state) {
		otus_write(sc, AR_GPIO_REG_PORT_DATA, state);
		if (otus_write_barrier(sc) == 0)
			sc->led_state = state;
	}
#endif
}