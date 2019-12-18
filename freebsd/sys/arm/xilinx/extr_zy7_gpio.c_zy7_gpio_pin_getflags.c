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
struct zy7_gpio_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int GPIO_PIN_INPUT ; 
 int GPIO_PIN_OUTPUT ; 
 int GPIO_PIN_TRISTATE ; 
 int RD4 (struct zy7_gpio_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VALID_PIN (int) ; 
 int /*<<< orphan*/  ZGPIO_LOCK (struct zy7_gpio_softc*) ; 
 int /*<<< orphan*/  ZGPIO_UNLOCK (struct zy7_gpio_softc*) ; 
 int /*<<< orphan*/  ZY7_GPIO_DIRM (int) ; 
 int /*<<< orphan*/  ZY7_GPIO_OEN (int) ; 
 struct zy7_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zy7_gpio_pin_getflags(device_t dev, uint32_t pin, uint32_t *flags)
{
	struct zy7_gpio_softc *sc = device_get_softc(dev);

	if (!VALID_PIN(pin))
		return (EINVAL);

	ZGPIO_LOCK(sc);

	if ((RD4(sc, ZY7_GPIO_DIRM(pin >> 5)) & (1 << (pin & 31))) != 0) {
		/* output */
		if ((RD4(sc, ZY7_GPIO_OEN(pin >> 5)) & (1 << (pin & 31))) == 0)
			*flags = (GPIO_PIN_OUTPUT | GPIO_PIN_TRISTATE);
		else
			*flags = GPIO_PIN_OUTPUT;
	} else
		/* input */
		*flags = GPIO_PIN_INPUT;

	ZGPIO_UNLOCK(sc);

	return (0);
}