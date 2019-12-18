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
struct sy8106a_softc {int /*<<< orphan*/ * reg; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 struct sy8106a_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  iicbus_get_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sy8106a_reg_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sy8106a_attach(device_t dev)
{
	struct sy8106a_softc *sc;
	phandle_t node;

	sc = device_get_softc(dev);
	node = ofw_bus_get_node(dev);

	sc->addr = iicbus_get_addr(dev);

	sc->reg = sy8106a_reg_attach(dev, node);
	if (sc->reg == NULL) {
		device_printf(dev, "cannot attach regulator\n");
		return (ENXIO);
	}

	return (0);
}