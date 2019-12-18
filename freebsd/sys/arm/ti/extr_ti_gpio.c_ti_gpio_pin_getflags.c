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
typedef  int /*<<< orphan*/  uint32_t ;
struct ti_gpio_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TI_GPIO_GET_FLAGS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TI_GPIO_LOCK (struct ti_gpio_softc*) ; 
 int /*<<< orphan*/  TI_GPIO_UNLOCK (struct ti_gpio_softc*) ; 
 struct ti_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ ti_gpio_valid_pin (struct ti_gpio_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ti_gpio_pin_getflags(device_t dev, uint32_t pin, uint32_t *flags)
{
	struct ti_gpio_softc *sc;

	sc = device_get_softc(dev);
	if (ti_gpio_valid_pin(sc, pin) != 0)
		return (EINVAL);

	/* Get the current pin state */
	TI_GPIO_LOCK(sc);
	TI_GPIO_GET_FLAGS(dev, pin, flags);
	TI_GPIO_UNLOCK(sc);

	return (0);
}