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
typedef  scalar_t__ uint32_t ;
struct regnode_fixed_sc {TYPE_1__* param; TYPE_2__* gpio_entry; } ;
struct regnode {int dummy; } ;
struct gpiobus_pin {int /*<<< orphan*/  pin; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {struct gpiobus_pin gpio_pin; } ;
struct TYPE_3__ {int /*<<< orphan*/  enable_active_high; } ;

/* Variables and functions */
 int GPIO_PIN_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int REGULATOR_STATUS_ENABLED ; 
 struct regnode_fixed_sc* regnode_get_softc (struct regnode*) ; 

__attribute__((used)) static int
regnode_fixed_status(struct regnode *regnode, int *status)
{
	struct regnode_fixed_sc *sc;
	struct gpiobus_pin *pin;
	uint32_t val;
	int rv;

	sc = regnode_get_softc(regnode);

	*status = 0;
	if (sc->gpio_entry == NULL) {
		*status = REGULATOR_STATUS_ENABLED;
		return (0);
	}
	pin = &sc->gpio_entry->gpio_pin;

	rv = GPIO_PIN_GET(pin->dev, pin->pin, &val);
	if (rv == 0) {
		if (!sc->param->enable_active_high ^ (val != 0))
			*status = REGULATOR_STATUS_ENABLED;
	}
	return (rv);
}