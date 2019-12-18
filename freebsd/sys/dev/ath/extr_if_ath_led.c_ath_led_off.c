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
struct ath_softc {int /*<<< orphan*/  sc_ledoff; int /*<<< orphan*/  sc_ledtimer; int /*<<< orphan*/  sc_ledon; int /*<<< orphan*/  sc_ledpin; int /*<<< orphan*/  sc_ah; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath_hal_gpioset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath_led_done ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ath_softc*) ; 

__attribute__((used)) static void
ath_led_off(void *arg)
{
	struct ath_softc *sc = arg;

	ath_hal_gpioset(sc->sc_ah, sc->sc_ledpin, !sc->sc_ledon);
	callout_reset(&sc->sc_ledtimer, sc->sc_ledoff, ath_led_done, sc);
}