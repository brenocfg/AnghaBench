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
typedef  int /*<<< orphan*/  usb_error_t ;
typedef  int uint8_t ;
struct urtw_softc {scalar_t__ sc_gpio_blinkstate; scalar_t__ sc_gpio_blinktime; int sc_gpio_ledstate; int sc_gpio_ledon; int /*<<< orphan*/  sc_led_ch; scalar_t__ sc_gpio_ledinprogress; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (struct urtw_softc*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  URTW_DEBUG_STATE ; 
 int URTW_LED_BLINK_CM3 ; 
#define  URTW_LED_BLINK_NORMAL 128 
 int URTW_LED_BLINK_SLOWLY ; 
 int /*<<< orphan*/  URTW_LED_GPIO ; 
 scalar_t__ URTW_LED_OFF ; 
 scalar_t__ URTW_LED_ON ; 
 int /*<<< orphan*/  USB_ERR_INVAL ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  urtw_led_ch ; 
 int /*<<< orphan*/  urtw_led_off (struct urtw_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  urtw_led_on (struct urtw_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct urtw_softc*) ; 

__attribute__((used)) static usb_error_t
urtw_led_blink(struct urtw_softc *sc)
{
	uint8_t ing = 0;
	usb_error_t error;

	if (sc->sc_gpio_blinkstate == URTW_LED_ON)
		error = urtw_led_on(sc, URTW_LED_GPIO);
	else
		error = urtw_led_off(sc, URTW_LED_GPIO);
	sc->sc_gpio_blinktime--;
	if (sc->sc_gpio_blinktime == 0)
		ing = 1;
	else {
		if (sc->sc_gpio_ledstate != URTW_LED_BLINK_NORMAL &&
		    sc->sc_gpio_ledstate != URTW_LED_BLINK_SLOWLY &&
		    sc->sc_gpio_ledstate != URTW_LED_BLINK_CM3)
			ing = 1;
	}
	if (ing == 1) {
		if (sc->sc_gpio_ledstate == URTW_LED_ON &&
		    sc->sc_gpio_ledon == 0)
			error = urtw_led_on(sc, URTW_LED_GPIO);
		else if (sc->sc_gpio_ledstate == URTW_LED_OFF &&
		    sc->sc_gpio_ledon == 1)
			error = urtw_led_off(sc, URTW_LED_GPIO);

		sc->sc_gpio_blinktime = 0;
		sc->sc_gpio_ledinprogress = 0;
		return (0);
	}

	sc->sc_gpio_blinkstate = (sc->sc_gpio_blinkstate != URTW_LED_ON) ?
	    URTW_LED_ON : URTW_LED_OFF;

	switch (sc->sc_gpio_ledstate) {
	case URTW_LED_BLINK_NORMAL:
		usb_callout_reset(&sc->sc_led_ch, hz, urtw_led_ch, sc);
		break;
	default:
		DPRINTF(sc, URTW_DEBUG_STATE,
		    "unknown LED status 0x%x",
		    sc->sc_gpio_ledstate);
		return (USB_ERR_INVAL);
	}
	return (0);
}