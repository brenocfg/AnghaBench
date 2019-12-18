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
typedef  scalar_t__ uint32_t ;
struct a37x0_gpio_softc {scalar_t__ sc_npins; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ A37X0_GPIO_BIT (scalar_t__) ; 
 int /*<<< orphan*/  A37X0_GPIO_OUT_EN (scalar_t__) ; 
 scalar_t__ A37X0_GPIO_READ (struct a37x0_gpio_softc*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 scalar_t__ GPIO_PIN_INPUT ; 
 scalar_t__ GPIO_PIN_OUTPUT ; 
 struct a37x0_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
a37x0_gpio_pin_getflags(device_t dev, uint32_t pin, uint32_t *flags)
{
	struct a37x0_gpio_softc *sc;
	uint32_t reg;

	sc = device_get_softc(dev);
	if (pin >= sc->sc_npins)
		return (EINVAL);
	reg = A37X0_GPIO_READ(sc, A37X0_GPIO_OUT_EN(pin));
	if ((reg & A37X0_GPIO_BIT(pin)) != 0)
		*flags = GPIO_PIN_OUTPUT;
	else
		*flags = GPIO_PIN_INPUT;

	return (0);
}