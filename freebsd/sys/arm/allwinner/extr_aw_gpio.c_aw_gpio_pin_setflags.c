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
 int /*<<< orphan*/  AW_GPIO_LOCK (struct aw_gpio_softc*) ; 
 int /*<<< orphan*/  AW_GPIO_UNLOCK (struct aw_gpio_softc*) ; 
 int EINVAL ; 
 int aw_gpio_pin_configure (struct aw_gpio_softc*,scalar_t__,scalar_t__) ; 
 struct aw_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aw_gpio_pin_setflags(device_t dev, uint32_t pin, uint32_t flags)
{
	struct aw_gpio_softc *sc;
	int err;

	sc = device_get_softc(dev);
	if (pin > sc->padconf->npins)
		return (EINVAL);

	AW_GPIO_LOCK(sc);
	err = aw_gpio_pin_configure(sc, pin, flags);
	AW_GPIO_UNLOCK(sc);

	return (err);
}