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
struct bwn_softc {scalar_t__ sc_led_ticks; scalar_t__ sc_led_idle; int sc_rx_rate; int sc_tx_rate; scalar_t__ sc_led_blinking; struct bwn_led* sc_blink_led; } ;
struct bwn_mac {struct bwn_softc* mac_sc; } ;
struct bwn_led {int led_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  off_dur; int /*<<< orphan*/  on_dur; } ;

/* Variables and functions */
#define  BWN_LED_EVENT_POLL 130 
#define  BWN_LED_EVENT_RX 129 
#define  BWN_LED_EVENT_TX 128 
 int BWN_LED_F_POLLABLE ; 
 int /*<<< orphan*/  bwn_led_blink_start (struct bwn_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* bwn_led_duration ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 scalar_t__ ticks ; 

__attribute__((used)) static void
bwn_led_event(struct bwn_mac *mac, int event)
{
	struct bwn_softc *sc = mac->mac_sc;
	struct bwn_led *led = sc->sc_blink_led;
	int rate;

	if (event == BWN_LED_EVENT_POLL) {
		if ((led->led_flags & BWN_LED_F_POLLABLE) == 0)
			return;
		if (ticks - sc->sc_led_ticks < sc->sc_led_idle)
			return;
	}

	sc->sc_led_ticks = ticks;
	if (sc->sc_led_blinking)
		return;

	switch (event) {
	case BWN_LED_EVENT_RX:
		rate = sc->sc_rx_rate;
		break;
	case BWN_LED_EVENT_TX:
		rate = sc->sc_tx_rate;
		break;
	case BWN_LED_EVENT_POLL:
		rate = 0;
		break;
	default:
		panic("unknown LED event %d\n", event);
		break;
	}
	bwn_led_blink_start(mac, bwn_led_duration[rate].on_dur,
	    bwn_led_duration[rate].off_dur);
}