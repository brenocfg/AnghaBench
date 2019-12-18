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
struct chvgpio_softc {int sc_ngroups; int* sc_pins; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int
chvgpio_valid_pin(struct chvgpio_softc *sc, int pin)
{
	if (pin < 0)
		return EINVAL;
	if ((pin / 15) >= sc->sc_ngroups)
		return EINVAL;
	if ((pin % 15) >= sc->sc_pins[pin / 15])
		return EINVAL;
	return (0);
}