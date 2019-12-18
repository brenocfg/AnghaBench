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
struct TYPE_2__ {int /*<<< orphan*/  ich_arg; int /*<<< orphan*/  ich_func; } ;
struct syr827_softc {int /*<<< orphan*/ * reg; TYPE_1__ intr_hook; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 scalar_t__ config_intrhook_establish (TYPE_1__*) ; 
 struct syr827_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  iicbus_get_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * syr827_reg_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syr827_start ; 

__attribute__((used)) static int
syr827_attach(device_t dev)
{
	struct syr827_softc *sc;
	phandle_t node;

	sc = device_get_softc(dev);
	node = ofw_bus_get_node(dev);

	sc->addr = iicbus_get_addr(dev);

	sc->intr_hook.ich_func = syr827_start;
	sc->intr_hook.ich_arg = dev;

	if (config_intrhook_establish(&sc->intr_hook) != 0)
		return (ENOMEM);

	sc->reg = syr827_reg_attach(dev, node);
	if (sc->reg == NULL) {
		device_printf(dev, "cannot attach regulator\n");
		return (ENXIO);
	}

	return (0);
}