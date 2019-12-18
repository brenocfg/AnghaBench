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
struct jz4780_gpio_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  JZ4780_GPIO_LOCK (struct jz4780_gpio_softc*) ; 
 int /*<<< orphan*/  JZ4780_GPIO_PINS ; 
 int /*<<< orphan*/  JZ4780_GPIO_UNLOCK (struct jz4780_gpio_softc*) ; 
 struct jz4780_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int jz4780_gpio_pin_set_bias (struct jz4780_gpio_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int jz4780_gpio_pin_set_func (struct jz4780_gpio_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
jz4780_gpio_configure_pin(device_t dev, uint32_t pin, uint32_t func,
    uint32_t flags)
{
	struct jz4780_gpio_softc *sc;
	int retval;

	if (pin >= JZ4780_GPIO_PINS)
		return (EINVAL);

	sc = device_get_softc(dev);
	JZ4780_GPIO_LOCK(sc);
	retval = jz4780_gpio_pin_set_func(sc, pin, func);
	if (retval == 0)
		retval = jz4780_gpio_pin_set_bias(sc, pin, flags);
	JZ4780_GPIO_UNLOCK(sc);
	return (retval);
}