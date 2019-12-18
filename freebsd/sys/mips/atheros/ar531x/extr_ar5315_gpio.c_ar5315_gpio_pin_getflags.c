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
typedef  int uint32_t ;
struct ar5315_gpio_softc {int gpio_npins; TYPE_1__* gpio_pins; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int gp_pin; } ;

/* Variables and functions */
 int EINVAL ; 
 int GPIO_PIN_INPUT ; 
 int GPIO_PIN_OUTPUT ; 
 int GPIO_READ (struct ar5315_gpio_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar531x_gpio_cr () ; 
 struct ar5315_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ar5315_gpio_pin_getflags(device_t dev, uint32_t pin, uint32_t *flags)
{
	struct ar5315_gpio_softc *sc = device_get_softc(dev);
	int i;
	int dir;

	for (i = 0; i < sc->gpio_npins; i++) {
		if (sc->gpio_pins[i].gp_pin == pin)
			break;
	}

	if (i >= sc->gpio_npins)
		return (EINVAL);

	dir = GPIO_READ(sc, ar531x_gpio_cr()) & (1 << pin);

	*flags = dir ? GPIO_PIN_OUTPUT : GPIO_PIN_INPUT;

/*
	GPIO_LOCK(sc);
	*flags = sc->gpio_pins[i].gp_flags;
	GPIO_UNLOCK(sc);
*/

	return (0);
}