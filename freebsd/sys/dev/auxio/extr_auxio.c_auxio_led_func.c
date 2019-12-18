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
typedef  int /*<<< orphan*/  u_int32_t ;
struct auxio_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUXIO_LED_LED ; 
 int /*<<< orphan*/  AUXIO_LOCK (struct auxio_softc*) ; 
 int /*<<< orphan*/  AUXIO_UNLOCK (struct auxio_softc*) ; 
 int /*<<< orphan*/  auxio_led_read (struct auxio_softc*) ; 
 int /*<<< orphan*/  auxio_led_write (struct auxio_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
auxio_led_func(void *arg, int onoff)
{
	struct auxio_softc *sc;
	u_int32_t led;

	sc = (struct auxio_softc *)arg;

	AUXIO_LOCK(sc);
	/*
	 * NB: We must not touch the other bits of the SBus AUXIO reg.
	 */
	led = auxio_led_read(sc);
	if (onoff)
		led |= AUXIO_LED_LED;
	else
		led &= ~AUXIO_LED_LED;
	auxio_led_write(sc, led);
	AUXIO_UNLOCK(sc);
}