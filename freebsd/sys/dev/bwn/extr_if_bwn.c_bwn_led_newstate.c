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
struct bwn_softc {int sc_flags; struct bwn_led* sc_leds; scalar_t__ sc_led_blinking; int /*<<< orphan*/  sc_led_blink_ch; struct ieee80211com sc_ic; } ;
struct bwn_mac {struct bwn_softc* mac_sc; } ;
struct bwn_led {int led_act; int led_flags; } ;
typedef  enum ieee80211_state { ____Placeholder_ieee80211_state } ieee80211_state ;

/* Variables and functions */
 int BWN_FLAG_RUNNING ; 
 int /*<<< orphan*/  BWN_GPIO_CONTROL ; 
 int BWN_LED_ACT_11G ; 
#define  BWN_LED_ACT_5GHZ 132 
 int BWN_LED_ACT_ASSOC ; 
 int BWN_LED_ACT_NULL ; 
#define  BWN_LED_ACT_OFF 131 
#define  BWN_LED_ACT_ON 130 
 int BWN_LED_ACT_UNKN ; 
 int BWN_LED_F_BLINK ; 
 int BWN_LED_MAX ; 
 int /*<<< orphan*/  BWN_READ_2 (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BWN_WRITE_2 (struct bwn_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEEE80211_MODE_11G ; 
#define  IEEE80211_S_INIT 129 
#define  IEEE80211_S_RUN 128 
 int /*<<< orphan*/  bwn_led_onoff (struct bwn_led*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bwn_led_newstate(struct bwn_mac *mac, enum ieee80211_state nstate)
{
	struct bwn_softc *sc = mac->mac_sc;
	struct ieee80211com *ic = &sc->sc_ic;
	uint16_t val;
	int i;

	if (nstate == IEEE80211_S_INIT) {
		callout_stop(&sc->sc_led_blink_ch);
		sc->sc_led_blinking = 0;
	}

	if ((sc->sc_flags & BWN_FLAG_RUNNING) == 0)
		return;

	val = BWN_READ_2(mac, BWN_GPIO_CONTROL);
	for (i = 0; i < BWN_LED_MAX; ++i) {
		struct bwn_led *led = &sc->sc_leds[i];
		int on;

		if (led->led_act == BWN_LED_ACT_UNKN ||
		    led->led_act == BWN_LED_ACT_NULL)
			continue;

		if ((led->led_flags & BWN_LED_F_BLINK) &&
		    nstate != IEEE80211_S_INIT)
			continue;

		switch (led->led_act) {
		case BWN_LED_ACT_ON:    /* Always on */
			on = 1;
			break;
		case BWN_LED_ACT_OFF:   /* Always off */
		case BWN_LED_ACT_5GHZ:  /* TODO: 11A */
			on = 0;
			break;
		default:
			on = 1;
			switch (nstate) {
			case IEEE80211_S_INIT:
				on = 0;
				break;
			case IEEE80211_S_RUN:
				if (led->led_act == BWN_LED_ACT_11G &&
				    ic->ic_curmode != IEEE80211_MODE_11G)
					on = 0;
				break;
			default:
				if (led->led_act == BWN_LED_ACT_ASSOC)
					on = 0;
				break;
			}
			break;
		}

		val = bwn_led_onoff(led, val, on);
	}
	BWN_WRITE_2(mac, BWN_GPIO_CONTROL, val);
}