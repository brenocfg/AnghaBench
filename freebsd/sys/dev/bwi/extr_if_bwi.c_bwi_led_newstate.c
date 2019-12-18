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
typedef  int /*<<< orphan*/  uint16_t ;
struct ieee80211com {int /*<<< orphan*/  ic_curmode; } ;
struct bwi_softc {int sc_flags; struct bwi_led* sc_leds; scalar_t__ sc_led_blinking; int /*<<< orphan*/  sc_led_blink_ch; struct ieee80211com sc_ic; } ;
struct bwi_led {int l_act; int l_flags; } ;
typedef  enum ieee80211_state { ____Placeholder_ieee80211_state } ieee80211_state ;

/* Variables and functions */
 int BWI_F_RUNNING ; 
 int BWI_LED_ACT_11G ; 
#define  BWI_LED_ACT_5GHZ 132 
 int BWI_LED_ACT_ASSOC ; 
 int BWI_LED_ACT_NULL ; 
#define  BWI_LED_ACT_OFF 131 
#define  BWI_LED_ACT_ON 130 
 int BWI_LED_ACT_UNKN ; 
 int BWI_LED_F_BLINK ; 
 int BWI_LED_MAX ; 
 int /*<<< orphan*/  BWI_MAC_GPIO_CTRL ; 
 int /*<<< orphan*/  CSR_READ_2 (struct bwi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct bwi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEEE80211_MODE_11G ; 
#define  IEEE80211_S_INIT 129 
#define  IEEE80211_S_RUN 128 
 int /*<<< orphan*/  bwi_led_onoff (struct bwi_led*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bwi_led_newstate(struct bwi_softc *sc, enum ieee80211_state nstate)
{
	struct ieee80211com *ic = &sc->sc_ic;
	uint16_t val;
	int i;

	if (nstate == IEEE80211_S_INIT) {
		callout_stop(&sc->sc_led_blink_ch);
		sc->sc_led_blinking = 0;
	}

	if ((sc->sc_flags & BWI_F_RUNNING) == 0)
		return;

	val = CSR_READ_2(sc, BWI_MAC_GPIO_CTRL);
	for (i = 0; i < BWI_LED_MAX; ++i) {
		struct bwi_led *led = &sc->sc_leds[i];
		int on;

		if (led->l_act == BWI_LED_ACT_UNKN ||
		    led->l_act == BWI_LED_ACT_NULL)
			continue;

		if ((led->l_flags & BWI_LED_F_BLINK) &&
		    nstate != IEEE80211_S_INIT)
		    	continue;

		switch (led->l_act) {
		case BWI_LED_ACT_ON:	/* Always on */
			on = 1;
			break;
		case BWI_LED_ACT_OFF:	/* Always off */
		case BWI_LED_ACT_5GHZ:	/* TODO: 11A */
			on = 0;
			break;
		default:
			on = 1;
			switch (nstate) {
			case IEEE80211_S_INIT:
				on = 0;
				break;
			case IEEE80211_S_RUN:
				if (led->l_act == BWI_LED_ACT_11G &&
				    ic->ic_curmode != IEEE80211_MODE_11G)
					on = 0;
				break;
			default:
				if (led->l_act == BWI_LED_ACT_ASSOC)
					on = 0;
				break;
			}
			break;
		}

		val = bwi_led_onoff(led, val, on);
	}
	CSR_WRITE_2(sc, BWI_MAC_GPIO_CTRL, val);
}