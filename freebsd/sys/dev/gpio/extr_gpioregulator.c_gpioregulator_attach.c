#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct regnode {int dummy; } ;
struct TYPE_6__ {int id; int /*<<< orphan*/  ofw_node; } ;
struct TYPE_4__ {TYPE_3__ reg_init_def; } ;
struct gpioregulator_softc {TYPE_1__ init_def; TYPE_2__* reg_sc; void* dev; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  void* device_t ;
struct TYPE_5__ {TYPE_1__* def; int /*<<< orphan*/  param; void* base_dev; struct regnode* regnode; } ;

/* Variables and functions */
 int ENXIO ; 
 struct gpioregulator_softc* device_get_softc (void*) ; 
 int /*<<< orphan*/  device_printf (void*,char*) ; 
 int gpioregulator_parse_fdt (struct gpioregulator_softc*) ; 
 int /*<<< orphan*/  gpioregulator_regnode_class ; 
 int /*<<< orphan*/  ofw_bus_get_node (void*) ; 
 struct regnode* regnode_create (void*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 TYPE_2__* regnode_get_softc (struct regnode*) ; 
 int /*<<< orphan*/  regnode_get_stdparam (struct regnode*) ; 
 int /*<<< orphan*/  regnode_register (struct regnode*) ; 

__attribute__((used)) static int
gpioregulator_attach(device_t dev)
{
	struct gpioregulator_softc *sc;
	struct regnode *regnode;
	phandle_t node;
	int error;

	sc = device_get_softc(dev);
	sc->dev = dev;
	node = ofw_bus_get_node(dev);

	error = gpioregulator_parse_fdt(sc);
	if (error != 0) {
		device_printf(dev, "cannot parse parameters\n");
		return (ENXIO);
	}
	sc->init_def.reg_init_def.id = 1;
	sc->init_def.reg_init_def.ofw_node = node;

	regnode = regnode_create(dev, &gpioregulator_regnode_class,
	    &sc->init_def.reg_init_def);
	if (regnode == NULL) {
		device_printf(dev, "cannot create regulator\n");
		return (ENXIO);
	}

	sc->reg_sc = regnode_get_softc(regnode);
	sc->reg_sc->regnode = regnode;
	sc->reg_sc->base_dev = dev;
	sc->reg_sc->param = regnode_get_stdparam(regnode);
	sc->reg_sc->def = &sc->init_def;

	regnode_register(regnode);

	return (0);
}