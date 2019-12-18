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
typedef  int uint8_t ;
typedef  size_t uint32_t ;
struct axp8xx_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {int /*<<< orphan*/  ctrl_reg; } ;

/* Variables and functions */
 int AXP_GPIO_FUNC ; 
#define  AXP_GPIO_FUNC_DRVHI 130 
#define  AXP_GPIO_FUNC_DRVLO 129 
#define  AXP_GPIO_FUNC_INPUT 128 
 int AXP_GPIO_FUNC_SHIFT ; 
 int /*<<< orphan*/  AXP_GPIO_SIGBIT ; 
 int /*<<< orphan*/  AXP_LOCK (struct axp8xx_softc*) ; 
 int /*<<< orphan*/  AXP_UNLOCK (struct axp8xx_softc*) ; 
 int EINVAL ; 
 int EIO ; 
 TYPE_1__* axp8xx_pins ; 
 int axp8xx_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 struct axp8xx_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 size_t nitems (TYPE_1__*) ; 

__attribute__((used)) static int
axp8xx_gpio_pin_get(device_t dev, uint32_t pin, unsigned int *val)
{
	struct axp8xx_softc *sc;
	uint8_t data, func;
	int error;

	if (pin >= nitems(axp8xx_pins))
		return (EINVAL);

	sc = device_get_softc(dev);

	AXP_LOCK(sc);
	error = axp8xx_read(dev, axp8xx_pins[pin].ctrl_reg, &data, 1);
	if (error == 0) {
		func = (data & AXP_GPIO_FUNC) >> AXP_GPIO_FUNC_SHIFT;
		switch (func) {
		case AXP_GPIO_FUNC_DRVLO:
			*val = 0;
			break;
		case AXP_GPIO_FUNC_DRVHI:
			*val = 1;
			break;
		case AXP_GPIO_FUNC_INPUT:
			error = axp8xx_read(dev, AXP_GPIO_SIGBIT, &data, 1);
			if (error == 0)
				*val = (data & (1 << pin)) ? 1 : 0;
			break;
		default:
			error = EIO;
			break;
		}
	}
	AXP_UNLOCK(sc);

	return (error);
}