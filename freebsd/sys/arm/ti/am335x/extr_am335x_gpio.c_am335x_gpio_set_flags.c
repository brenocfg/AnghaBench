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
typedef  int uint32_t ;
struct ti_gpio_softc {int sc_bank; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int GPIO_PIN_INPUT ; 
 int GPIO_PIN_OUTPUT ; 
 int GPIO_PIN_PULLDOWN ; 
 int GPIO_PIN_PULLUP ; 
 unsigned int PADCONF_INPUT ; 
 unsigned int PADCONF_INPUT_PULLDOWN ; 
 unsigned int PADCONF_INPUT_PULLUP ; 
 unsigned int PADCONF_OUTPUT ; 
 unsigned int PADCONF_OUTPUT_PULLUP ; 
 struct ti_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int ti_pinmux_padconf_set_gpiomode (int,unsigned int) ; 

__attribute__((used)) static int
am335x_gpio_set_flags(device_t dev, uint32_t gpio, uint32_t flags)
{
	unsigned int state = 0;
	struct ti_gpio_softc *sc = device_get_softc(dev);

	if (flags & GPIO_PIN_OUTPUT) {
		if (flags & GPIO_PIN_PULLUP)
			state = PADCONF_OUTPUT_PULLUP;
		else
			state = PADCONF_OUTPUT;
	} else if (flags & GPIO_PIN_INPUT) {
		if (flags & GPIO_PIN_PULLUP)
			state = PADCONF_INPUT_PULLUP;
		else if (flags & GPIO_PIN_PULLDOWN)
			state = PADCONF_INPUT_PULLDOWN;
		else
			state = PADCONF_INPUT;
	}
	return ti_pinmux_padconf_set_gpiomode(sc->sc_bank*32 + gpio, state);
}