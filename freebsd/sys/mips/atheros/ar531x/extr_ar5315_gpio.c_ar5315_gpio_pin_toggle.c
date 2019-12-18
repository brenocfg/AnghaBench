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
 int /*<<< orphan*/  GPIO_CLEAR_BITS (struct ar5315_gpio_softc*,int /*<<< orphan*/ ,int) ; 
 int GPIO_READ (struct ar5315_gpio_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIO_SET_BITS (struct ar5315_gpio_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ar531x_gpio_do () ; 
 struct ar5315_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ar5315_gpio_pin_toggle(device_t dev, uint32_t pin)
{
	int res, i;
	struct ar5315_gpio_softc *sc = device_get_softc(dev);

	for (i = 0; i < sc->gpio_npins; i++) {
		if (sc->gpio_pins[i].gp_pin == pin)
			break;
	}

	if (i >= sc->gpio_npins)
		return (EINVAL);

	res = (GPIO_READ(sc, ar531x_gpio_do()) & (1 << pin)) ? 1 : 0;
	if (res)
		GPIO_CLEAR_BITS(sc, ar531x_gpio_do(), pin);
	else
		GPIO_SET_BITS(sc, ar531x_gpio_do(), pin);

	return (0);
}