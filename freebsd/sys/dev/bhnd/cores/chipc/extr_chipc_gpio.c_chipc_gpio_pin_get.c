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
struct chipc_gpio_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CC_GPIO_LOCK (struct chipc_gpio_softc*) ; 
#define  CC_GPIO_PIN_INPUT 130 
#define  CC_GPIO_PIN_OUTPUT 129 
#define  CC_GPIO_PIN_TRISTATE 128 
 int CC_GPIO_RDFLAG (struct chipc_gpio_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CC_GPIO_UNLOCK (struct chipc_gpio_softc*) ; 
 int /*<<< orphan*/  CC_GPIO_VALID_PIN (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  GPIOIN ; 
 int /*<<< orphan*/  GPIOOUT ; 
 int /*<<< orphan*/  GPIO_PIN_HIGH ; 
 int /*<<< orphan*/  GPIO_PIN_LOW ; 
 int chipc_gpio_pin_get_mode (struct chipc_gpio_softc*,int /*<<< orphan*/ ) ; 
 struct chipc_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
chipc_gpio_pin_get(device_t dev, uint32_t pin_num, uint32_t *pin_value)
{
	struct chipc_gpio_softc	*sc;
	bool			 pin_high;

	if (!CC_GPIO_VALID_PIN(pin_num))
		return (EINVAL);

	sc = device_get_softc(dev);
	pin_high = false;

	CC_GPIO_LOCK(sc);

	switch (chipc_gpio_pin_get_mode(sc, pin_num)) {
	case CC_GPIO_PIN_INPUT:
		pin_high = CC_GPIO_RDFLAG(sc, pin_num, GPIOIN);
		break;

	case CC_GPIO_PIN_OUTPUT:
		pin_high = CC_GPIO_RDFLAG(sc, pin_num, GPIOOUT);
		break;

	case CC_GPIO_PIN_TRISTATE:
		pin_high = false;
		break;
	}

	CC_GPIO_UNLOCK(sc);

	*pin_value = pin_high ? GPIO_PIN_HIGH : GPIO_PIN_LOW;

	return (0);
}