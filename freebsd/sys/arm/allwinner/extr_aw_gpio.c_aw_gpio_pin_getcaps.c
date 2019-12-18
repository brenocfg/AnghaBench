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
typedef  scalar_t__ uint32_t ;
struct aw_gpio_softc {TYPE_1__* padconf; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ npins; } ;

/* Variables and functions */
 scalar_t__ AW_GPIO_DEFAULT_CAPS ; 
 int EINVAL ; 
 struct aw_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aw_gpio_pin_getcaps(device_t dev, uint32_t pin, uint32_t *caps)
{
	struct aw_gpio_softc *sc;

	sc = device_get_softc(dev);
	if (pin >= sc->padconf->npins)
		return (EINVAL);

	*caps = AW_GPIO_DEFAULT_CAPS;

	return (0);
}