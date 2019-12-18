#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct regnode_fixed_sc {TYPE_2__* param; TYPE_1__* gpio_entry; } ;
struct regnode {int dummy; } ;
struct gpiobus_pin {int /*<<< orphan*/  pin; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {int enable_delay; scalar_t__ enable_active_high; } ;
struct TYPE_3__ {scalar_t__ enable_cnt; struct gpiobus_pin gpio_pin; scalar_t__ always_on; } ;

/* Variables and functions */
 int GPIO_PIN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regnode_get_device (struct regnode*) ; 
 struct regnode_fixed_sc* regnode_get_softc (struct regnode*) ; 

__attribute__((used)) static int
regnode_fixed_stop(struct regnode *regnode, int *udelay)
{
	device_t dev;
	struct regnode_fixed_sc *sc;
	struct gpiobus_pin *pin;
	int rv;

	sc = regnode_get_softc(regnode);
	dev = regnode_get_device(regnode);

	*udelay = 0;
	if (sc->gpio_entry == NULL)
		return (0);
	if (sc->gpio_entry->always_on)
		return (0);
	pin = &sc->gpio_entry->gpio_pin;
	if (sc->gpio_entry->enable_cnt > 0) {
		/* Other regulator(s) are enabled. */
		/* XXXX Any diagnostic message? Or error? */
		return (0);
	}
	rv = GPIO_PIN_SET(pin->dev, pin->pin,
	    sc->param->enable_active_high ? false: true);
	if (rv != 0) {
		device_printf(dev, "Cannot set GPIO pin: %d\n", pin->pin);
		return (rv);
	}
	*udelay = sc->param->enable_delay;
	return (0);
}