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
 int EINVAL ; 
 int GPIO_PIN_INPUT ; 
 int GPIO_PIN_OUTPUT ; 
 int GPIO_PIN_PULLDOWN ; 
 int GPIO_PIN_PULLUP ; 
#define  PADCONF_INPUT 132 
#define  PADCONF_INPUT_PULLDOWN 131 
#define  PADCONF_INPUT_PULLUP 130 
#define  PADCONF_OUTPUT 129 
#define  PADCONF_OUTPUT_PULLUP 128 
 struct ti_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ ti_pinmux_padconf_get_gpiomode (int,unsigned int*) ; 

__attribute__((used)) static int
am335x_gpio_get_flags(device_t dev, uint32_t gpio, uint32_t *flags)
{
	unsigned int state;
	struct ti_gpio_softc *sc = device_get_softc(dev);

	if (ti_pinmux_padconf_get_gpiomode(sc->sc_bank*32 + gpio, &state) != 0) {
		*flags = 0;
		return (EINVAL);
	} else {
		switch (state) {
			case PADCONF_OUTPUT:
				*flags = GPIO_PIN_OUTPUT;
				break;
			case PADCONF_OUTPUT_PULLUP:
				*flags = GPIO_PIN_OUTPUT | GPIO_PIN_PULLUP;
				break;
			case PADCONF_INPUT:
				*flags = GPIO_PIN_INPUT;
				break;
			case PADCONF_INPUT_PULLUP:
				*flags = GPIO_PIN_INPUT | GPIO_PIN_PULLUP;
				break;
			case PADCONF_INPUT_PULLDOWN:
				*flags = GPIO_PIN_INPUT | GPIO_PIN_PULLDOWN;
				break;
			default:
				*flags = 0;
				break;
		}
	}

	return (0);
}