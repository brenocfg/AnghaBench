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
typedef  size_t uint32_t ;
struct imx51_gpio_softc {size_t gpio_npins; TYPE_1__* gpio_pins; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {size_t gp_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 struct imx51_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
imx51_gpio_pin_getflags(device_t dev, uint32_t pin, uint32_t *flags)
{
	struct imx51_gpio_softc *sc;

	sc = device_get_softc(dev);

	if (pin >= sc->gpio_npins)
		return (EINVAL);

	*flags = sc->gpio_pins[pin].gp_flags;

	return (0);
}