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
typedef  size_t uint32_t ;
struct imx51_gpio_softc {size_t gpio_npins; TYPE_1__* gpio_pins; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int gp_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int GPIO_PIN_OPENDRAIN ; 
 int /*<<< orphan*/  IMX_GPIO_DR_REG ; 
 int /*<<< orphan*/  IMX_GPIO_PSR_REG ; 
 size_t READ4 (struct imx51_gpio_softc*,int /*<<< orphan*/ ) ; 
 struct imx51_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
imx51_gpio_pin_get(device_t dev, uint32_t pin, unsigned int *val)
{
	struct imx51_gpio_softc *sc;

	sc = device_get_softc(dev);

	if (pin >= sc->gpio_npins)
		return (EINVAL);

	/*
	 * Normally a pin set for output can be read by reading the DR reg which
	 * indicates what value is being driven to that pin.  The exception is
	 * pins configured for open-drain mode, in which case we have to read
	 * the pad status register in case the pin is being driven externally.
	 * Doing so requires that the SION bit be configured in pinmux, which
	 * isn't the case for most normal gpio pins, so only try to read via PSR
	 * if the OPENDRAIN flag is set, and it's the user's job to correctly
	 * configure SION along with open-drain output mode for those pins.
	 */
	if (sc->gpio_pins[pin].gp_flags & GPIO_PIN_OPENDRAIN)
		*val = (READ4(sc, IMX_GPIO_PSR_REG) >> pin) & 1;
	else
		*val = (READ4(sc, IMX_GPIO_DR_REG) >> pin) & 1;

	return (0);
}