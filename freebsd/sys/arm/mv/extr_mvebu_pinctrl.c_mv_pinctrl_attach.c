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
struct mv_pinctrl_softc {int /*<<< orphan*/ * syscon; int /*<<< orphan*/  dev; struct mv_padconf* padconf; } ;
struct mv_padconf {int dummy; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ ocd_data; } ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ SYSCON_GET_HANDLE (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  compat_data ; 
 struct mv_pinctrl_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fdt_pinctrl_configure_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdt_pinctrl_register (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 TYPE_1__* ofw_bus_search_compatible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mv_pinctrl_attach(device_t dev)
{
	struct mv_pinctrl_softc *sc;
	phandle_t node;

	sc = device_get_softc(dev);
	sc->dev = dev;
	sc->padconf = (struct mv_padconf *)
	    ofw_bus_search_compatible(dev,compat_data)->ocd_data;

	if (SYSCON_GET_HANDLE(sc->dev, &sc->syscon) != 0 ||
	    sc->syscon == NULL) {
		device_printf(dev, "cannot get syscon for device\n");
		return (ENXIO);
	}

	node = ofw_bus_get_node(dev);

	fdt_pinctrl_register(dev, "marvell,pins");
	fdt_pinctrl_configure_tree(dev);

	return (0);
}