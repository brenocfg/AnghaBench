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
struct ar71xx_gpio_softc {int gpio_npins; TYPE_1__* gpio_pins; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int gp_pin; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR71XX_GPIO_CLEAR ; 
 int /*<<< orphan*/  AR71XX_GPIO_SET ; 
 int EINVAL ; 
 int /*<<< orphan*/  GPIO_WRITE (struct ar71xx_gpio_softc*,int /*<<< orphan*/ ,int) ; 
 struct ar71xx_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ar71xx_gpio_pin_set(device_t dev, uint32_t pin, unsigned int value)
{
	struct ar71xx_gpio_softc *sc = device_get_softc(dev);
	int i;

	for (i = 0; i < sc->gpio_npins; i++) {
		if (sc->gpio_pins[i].gp_pin == pin)
			break;
	}

	if (i >= sc->gpio_npins)
		return (EINVAL);

	if (value)
		GPIO_WRITE(sc, AR71XX_GPIO_SET, (1 << pin));
	else
		GPIO_WRITE(sc, AR71XX_GPIO_CLEAR, (1 << pin));

	return (0);
}