#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint32_t ;
struct axp8xx_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {int /*<<< orphan*/  ctrl_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXP_GPIO_FUNC ; 
 int /*<<< orphan*/  AXP_GPIO_FUNC_INPUT ; 
 int /*<<< orphan*/  AXP_LOCK (struct axp8xx_softc*) ; 
 int /*<<< orphan*/  AXP_UNLOCK (struct axp8xx_softc*) ; 
 int EINVAL ; 
 size_t GPIO_PIN_INPUT ; 
 size_t GPIO_PIN_OUTPUT ; 
 TYPE_1__* axp8xx_pins ; 
 int axp8xx_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int axp8xx_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct axp8xx_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 size_t nitems (TYPE_1__*) ; 

__attribute__((used)) static int
axp8xx_gpio_pin_setflags(device_t dev, uint32_t pin, uint32_t flags)
{
	struct axp8xx_softc *sc;
	uint8_t data;
	int error;

	if (pin >= nitems(axp8xx_pins))
		return (EINVAL);

	sc = device_get_softc(dev);

	AXP_LOCK(sc);
	error = axp8xx_read(dev, axp8xx_pins[pin].ctrl_reg, &data, 1);
	if (error == 0) {
		data &= ~AXP_GPIO_FUNC;
		if ((flags & (GPIO_PIN_INPUT|GPIO_PIN_OUTPUT)) != 0) {
			if ((flags & GPIO_PIN_OUTPUT) == 0)
				data |= AXP_GPIO_FUNC_INPUT;
		}
		error = axp8xx_write(dev, axp8xx_pins[pin].ctrl_reg, data);
	}
	AXP_UNLOCK(sc);

	return (error);
}