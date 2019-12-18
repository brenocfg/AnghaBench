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
struct ath_softc {scalar_t__ sc_ledpin; scalar_t__ sc_led_pwr_pin; scalar_t__ sc_led_net_pin; int /*<<< orphan*/  sc_ah; scalar_t__ sc_hardled; int /*<<< orphan*/  sc_ledon; scalar_t__ sc_softled; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_LOCK (struct ath_softc*) ; 
 int /*<<< orphan*/  ATH_UNLOCK (struct ath_softc*) ; 
 int /*<<< orphan*/  HAL_GPIO_OUTPUT_MUX_AS_OUTPUT ; 
 int /*<<< orphan*/  HAL_GPIO_OUTPUT_MUX_MAC_NETWORK_LED ; 
 int /*<<< orphan*/  HAL_GPIO_OUTPUT_MUX_MAC_POWER_LED ; 
 int /*<<< orphan*/  HAL_PM_AWAKE ; 
 int /*<<< orphan*/  ath_hal_gpioCfgOutput (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_hal_gpioset (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  ath_power_restore_power_state (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_power_set_power_state (struct ath_softc*,int /*<<< orphan*/ ) ; 

void
ath_led_config(struct ath_softc *sc)
{

	ATH_LOCK(sc);
	ath_power_set_power_state(sc, HAL_PM_AWAKE);
	ATH_UNLOCK(sc);

	/* Software LED blinking - GPIO controlled LED */
	if (sc->sc_softled) {
		ath_hal_gpioCfgOutput(sc->sc_ah, sc->sc_ledpin,
		    HAL_GPIO_OUTPUT_MUX_AS_OUTPUT);
		ath_hal_gpioset(sc->sc_ah, sc->sc_ledpin, !sc->sc_ledon);
	}

	/* Hardware LED blinking - MAC controlled LED */
	if (sc->sc_hardled) {
		/*
		 * Only enable each LED if required.
		 *
		 * Some NICs only have one LED connected; others may
		 * have GPIO1/GPIO2 connected to other hardware.
		 */
		if (sc->sc_led_pwr_pin > 0)
			ath_hal_gpioCfgOutput(sc->sc_ah, sc->sc_led_pwr_pin,
			    HAL_GPIO_OUTPUT_MUX_MAC_POWER_LED);
		if (sc->sc_led_net_pin > 0)
			ath_hal_gpioCfgOutput(sc->sc_ah, sc->sc_led_net_pin,
			    HAL_GPIO_OUTPUT_MUX_MAC_NETWORK_LED);
	}

	ATH_LOCK(sc);
	ath_power_restore_power_state(sc);
	ATH_UNLOCK(sc);
}