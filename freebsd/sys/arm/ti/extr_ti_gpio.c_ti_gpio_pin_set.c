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
 unsigned int GPIO_PIN_LOW ; 
 int /*<<< orphan*/  TI_GPIO_CLEARDATAOUT ; 
 int /*<<< orphan*/  TI_GPIO_LOCK (struct ti_gpio_softc*) ; 
 int /*<<< orphan*/  TI_GPIO_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TI_GPIO_SETDATAOUT ; 
 int /*<<< orphan*/  TI_GPIO_UNLOCK (struct ti_gpio_softc*) ; 
 struct ti_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ ti_gpio_valid_pin (struct ti_gpio_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_gpio_write_4 (struct ti_gpio_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ti_gpio_pin_set(device_t dev, uint32_t pin, unsigned int value)
{
	struct ti_gpio_softc *sc;
	uint32_t reg;

	sc = device_get_softc(dev);
	if (ti_gpio_valid_pin(sc, pin) != 0)
		return (EINVAL);

	TI_GPIO_LOCK(sc);
	if (value == GPIO_PIN_LOW)
		reg = TI_GPIO_CLEARDATAOUT;
	else
		reg = TI_GPIO_SETDATAOUT;
	ti_gpio_write_4(sc, reg, TI_GPIO_MASK(pin));
	TI_GPIO_UNLOCK(sc);

	return (0);
}