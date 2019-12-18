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
struct regnode {int dummy; } ;
struct gpioregulator_reg_sc {TYPE_2__* def; TYPE_1__* param; } ;
struct TYPE_4__ {int enable_pin_valid; int startup_delay_us; int /*<<< orphan*/  enable_pin; } ;
struct TYPE_3__ {int /*<<< orphan*/  enable_active_high; } ;

/* Variables and functions */
 int gpio_pin_set_active (int /*<<< orphan*/ ,int) ; 
 struct gpioregulator_reg_sc* regnode_get_softc (struct regnode*) ; 

__attribute__((used)) static int
gpioregulator_regnode_enable(struct regnode *regnode, bool enable, int *udelay)
{
	struct gpioregulator_reg_sc *sc;
	bool active;
	int error;

	sc = regnode_get_softc(regnode);

	if (sc->def->enable_pin_valid == 1) {
		active = enable;
		if (!sc->param->enable_active_high)
			active = !active;
		error = gpio_pin_set_active(sc->def->enable_pin, active);
		if (error != 0)
			return (error);
	}

	*udelay = sc->def->startup_delay_us;

	return (0);
}