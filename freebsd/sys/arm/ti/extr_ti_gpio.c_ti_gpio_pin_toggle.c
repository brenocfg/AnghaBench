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
 int TI_GPIO_CLEARDATAOUT ; 
 int /*<<< orphan*/  TI_GPIO_DATAOUT ; 
 int /*<<< orphan*/  TI_GPIO_LOCK (struct ti_gpio_softc*) ; 
 int TI_GPIO_MASK (int) ; 
 int TI_GPIO_SETDATAOUT ; 
 int /*<<< orphan*/  TI_GPIO_UNLOCK (struct ti_gpio_softc*) ; 
 struct ti_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int ti_gpio_read_4 (struct ti_gpio_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ ti_gpio_valid_pin (struct ti_gpio_softc*,int) ; 
 int /*<<< orphan*/  ti_gpio_write_4 (struct ti_gpio_softc*,int,int) ; 

__attribute__((used)) static int
ti_gpio_pin_toggle(device_t dev, uint32_t pin)
{
	struct ti_gpio_softc *sc;
	uint32_t reg, val;

	sc = device_get_softc(dev);
	if (ti_gpio_valid_pin(sc, pin) != 0)
		return (EINVAL);

	/* Toggle the pin */
	TI_GPIO_LOCK(sc);
	val = ti_gpio_read_4(sc, TI_GPIO_DATAOUT);
	if (val & TI_GPIO_MASK(pin))
		reg = TI_GPIO_CLEARDATAOUT;
	else
		reg = TI_GPIO_SETDATAOUT;
	ti_gpio_write_4(sc, reg, TI_GPIO_MASK(pin));
	TI_GPIO_UNLOCK(sc);

	return (0);
}