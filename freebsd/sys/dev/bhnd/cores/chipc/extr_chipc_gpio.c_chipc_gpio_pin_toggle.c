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
 int /*<<< orphan*/  CC_GPIO_WRFLAG (struct chipc_gpio_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  GPIOOUT ; 
 int chipc_gpio_pin_get_mode (struct chipc_gpio_softc*,int /*<<< orphan*/ ) ; 
 struct chipc_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
chipc_gpio_pin_toggle(device_t dev, uint32_t pin_num)
{
	struct chipc_gpio_softc	*sc;
	bool			 pin_high;
	int			 error;

	if (!CC_GPIO_VALID_PIN(pin_num))
		return (EINVAL);

	sc = device_get_softc(dev);
	error = 0;

	CC_GPIO_LOCK(sc);

	switch (chipc_gpio_pin_get_mode(sc, pin_num)) {
	case CC_GPIO_PIN_INPUT:
	case CC_GPIO_PIN_TRISTATE:
		error = ENODEV;
		break;

	case CC_GPIO_PIN_OUTPUT:
		pin_high = CC_GPIO_RDFLAG(sc, pin_num, GPIOOUT);
		CC_GPIO_WRFLAG(sc, pin_num, GPIOOUT, !pin_high);
		break;
	}

	CC_GPIO_UNLOCK(sc);

	return (error);
}