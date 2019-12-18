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
struct bwi_softc {scalar_t__ sc_led_ticks; scalar_t__ sc_led_idle; int sc_rx_rate; int sc_tx_rate; scalar_t__ sc_led_blinking; struct bwi_led* sc_blink_led; } ;
struct bwi_led {int l_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  off_dur; int /*<<< orphan*/  on_dur; } ;

/* Variables and functions */
#define  BWI_LED_EVENT_POLL 130 
#define  BWI_LED_EVENT_RX 129 
#define  BWI_LED_EVENT_TX 128 
 int BWI_LED_F_POLLABLE ; 
 int /*<<< orphan*/  bwi_led_blink_start (struct bwi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* bwi_led_duration ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 scalar_t__ ticks ; 

__attribute__((used)) static void
bwi_led_event(struct bwi_softc *sc, int event)
{
	struct bwi_led *led = sc->sc_blink_led;
	int rate;

	if (event == BWI_LED_EVENT_POLL) {
		if ((led->l_flags & BWI_LED_F_POLLABLE) == 0)
			return;
		if (ticks - sc->sc_led_ticks < sc->sc_led_idle)
			return;
	}

	sc->sc_led_ticks = ticks;
	if (sc->sc_led_blinking)
		return;

	switch (event) {
	case BWI_LED_EVENT_RX:
		rate = sc->sc_rx_rate;
		break;
	case BWI_LED_EVENT_TX:
		rate = sc->sc_tx_rate;
		break;
	case BWI_LED_EVENT_POLL:
		rate = 0;
		break;
	default:
		panic("unknown LED event %d\n", event);
		break;
	}
	bwi_led_blink_start(sc, bwi_led_duration[rate].on_dur,
	    bwi_led_duration[rate].off_dur);
}