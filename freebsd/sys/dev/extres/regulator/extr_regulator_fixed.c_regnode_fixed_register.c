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
struct regnode_fixed_sc {TYPE_1__* param; TYPE_2__* gpio_entry; int /*<<< orphan*/  gpio_open_drain; } ;
struct regnode_fixed_init_def {int /*<<< orphan*/ * gpio_pin; int /*<<< orphan*/  gpio_open_drain; int /*<<< orphan*/  reg_init_def; } ;
struct regnode {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {int /*<<< orphan*/  always_on; } ;
struct TYPE_3__ {int /*<<< orphan*/  always_on; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 struct regnode* regnode_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regnode_fixed_class ; 
 TYPE_2__* regnode_get_gpio_entry (int /*<<< orphan*/ *) ; 
 struct regnode_fixed_sc* regnode_get_softc (struct regnode*) ; 
 struct regnode* regnode_register (struct regnode*) ; 

int
regnode_fixed_register(device_t dev, struct regnode_fixed_init_def *init_def)
{
	struct regnode *regnode;
	struct regnode_fixed_sc *sc;

	regnode = regnode_create(dev, &regnode_fixed_class,
	    &init_def->reg_init_def);
	if (regnode == NULL) {
		device_printf(dev, "Cannot create regulator.\n");
		return(ENXIO);
	}
	sc = regnode_get_softc(regnode);
	sc->gpio_open_drain = init_def->gpio_open_drain;
	if (init_def->gpio_pin != NULL) {
		sc->gpio_entry = regnode_get_gpio_entry(init_def->gpio_pin);
		if (sc->gpio_entry == NULL)
			return(ENXIO);
	}
	regnode = regnode_register(regnode);
	if (regnode == NULL) {
		device_printf(dev, "Cannot register regulator.\n");
		return(ENXIO);
	}

	if (sc->gpio_entry != NULL)
		sc->gpio_entry->always_on |= sc->param->always_on;

	return (0);
}