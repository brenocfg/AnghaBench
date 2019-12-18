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
struct bwn_softc {int sc_led_blinking; int sc_led_blink_offdur; int /*<<< orphan*/  sc_led_blink_ch; struct bwn_led* sc_blink_led; } ;
struct bwn_mac {struct bwn_softc* mac_sc; } ;
struct bwn_led {int led_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_GPIO_CONTROL ; 
 int BWN_LED_F_SLOW ; 
 int /*<<< orphan*/  BWN_LED_SLOWDOWN (int) ; 
 int /*<<< orphan*/  BWN_READ_2 (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BWN_WRITE_2 (struct bwn_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwn_led_blink_next ; 
 int /*<<< orphan*/  bwn_led_onoff (struct bwn_led*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct bwn_mac*) ; 

__attribute__((used)) static void
bwn_led_blink_start(struct bwn_mac *mac, int on_dur, int off_dur)
{
	struct bwn_softc *sc = mac->mac_sc;
	struct bwn_led *led = sc->sc_blink_led;
	uint16_t val;

	val = BWN_READ_2(mac, BWN_GPIO_CONTROL);
	val = bwn_led_onoff(led, val, 1);
	BWN_WRITE_2(mac, BWN_GPIO_CONTROL, val);

	if (led->led_flags & BWN_LED_F_SLOW) {
		BWN_LED_SLOWDOWN(on_dur);
		BWN_LED_SLOWDOWN(off_dur);
	}

	sc->sc_led_blinking = 1;
	sc->sc_led_blink_offdur = off_dur;

	callout_reset(&sc->sc_led_blink_ch, on_dur, bwn_led_blink_next, mac);
}