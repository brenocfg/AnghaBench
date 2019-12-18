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
struct amdgpio_softc {TYPE_1__* sc_gpio_pins; int /*<<< orphan*/ ** sc_res; } ;
struct TYPE_2__ {int gp_pin; scalar_t__ gp_caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintf (char*,int) ; 

__attribute__((used)) static bool
amdgpio_valid_pin(struct amdgpio_softc *sc, int pin)
{
	dprintf("pin %d\n", pin);
	if (sc->sc_res[0] == NULL)
		return (false);

	if ((sc->sc_gpio_pins[pin].gp_pin == pin) &&
		(sc->sc_gpio_pins[pin].gp_caps != 0))
		return (true);

	return (false);
}