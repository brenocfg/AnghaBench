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
struct ti_gpio_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int TI_GPIO_DATAIN ; 
 int TI_GPIO_DATAOUT ; 
 int /*<<< orphan*/  TI_GPIO_LOCK (struct ti_gpio_softc*) ; 
 int TI_GPIO_MASK (int) ; 
 int TI_GPIO_OE ; 
 int /*<<< orphan*/  TI_GPIO_UNLOCK (struct ti_gpio_softc*) ; 
 struct ti_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int ti_gpio_read_4 (struct ti_gpio_softc*,int) ; 
 scalar_t__ ti_gpio_valid_pin (struct ti_gpio_softc*,int) ; 

__attribute__((used)) static int
ti_gpio_pin_get(device_t dev, uint32_t pin, unsigned int *value)
{
	struct ti_gpio_softc *sc;
	uint32_t oe, reg, val;

	sc = device_get_softc(dev);
	if (ti_gpio_valid_pin(sc, pin) != 0)
		return (EINVAL);

	/*
	 * Return data from output latch when set as output and from the 
	 * input register otherwise.
	 */
	TI_GPIO_LOCK(sc);
	oe = ti_gpio_read_4(sc, TI_GPIO_OE);
	if (oe & TI_GPIO_MASK(pin))
		reg = TI_GPIO_DATAIN;
	else
		reg = TI_GPIO_DATAOUT;
	val = ti_gpio_read_4(sc, reg);
	*value = (val & TI_GPIO_MASK(pin)) ? 1 : 0;
	TI_GPIO_UNLOCK(sc);

	return (0);
}