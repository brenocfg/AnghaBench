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
struct bwi_softc {scalar_t__ sc_led_blinking; } ;

/* Variables and functions */

__attribute__((used)) static void
bwi_led_blink_end(void *xsc)
{
	struct bwi_softc *sc = xsc;
	sc->sc_led_blinking = 0;
}