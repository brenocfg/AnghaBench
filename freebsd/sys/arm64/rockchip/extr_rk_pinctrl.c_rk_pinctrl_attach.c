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
struct rk_pinctrl_softc {int /*<<< orphan*/ * dev; struct rk_pinctrl_conf* conf; int /*<<< orphan*/  pmu; int /*<<< orphan*/  grf; } ;
struct rk_pinctrl_conf {int dummy; } ;
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/ * device_t ;
struct TYPE_2__ {scalar_t__ ocd_data; } ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ OF_child (scalar_t__) ; 
 int OF_getprop_alloc (scalar_t__,char*,void**) ; 
 scalar_t__ OF_hasprop (scalar_t__,char*) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 int /*<<< orphan*/  OF_prop_free (char*) ; 
 int bus_generic_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_generic_probe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compat_data ; 
 struct rk_pinctrl_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*,...) ; 
 int device_probe_and_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fdt_pinctrl_configure_tree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fdt_pinctrl_register (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ *) ; 
 scalar_t__ ofw_bus_node_is_compatible (scalar_t__,char*) ; 
 TYPE_1__* ofw_bus_search_compatible (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int rk_pinctrl_register_gpio (struct rk_pinctrl_softc*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * simplebus_add_device (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simplebus_init (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  strsep (char**,char*) ; 
 scalar_t__ syscon_get_by_ofw_property (int /*<<< orphan*/ *,scalar_t__,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
rk_pinctrl_attach(device_t dev)
{
	struct rk_pinctrl_softc *sc;
	phandle_t node;
	device_t cdev;
	char *gpio_name, *eptr;
	int rv;

	sc = device_get_softc(dev);
	sc->dev = dev;

	node = ofw_bus_get_node(dev);

	if (OF_hasprop(node, "rockchip,grf") &&
	    syscon_get_by_ofw_property(dev, node,
	    "rockchip,grf", &sc->grf) != 0) {
		device_printf(dev, "cannot get grf driver handle\n");
		return (ENXIO);
	}

	/* RK3399,RK3288 has banks in PMU. RK3328 does not have a PMU. */
	if (ofw_bus_node_is_compatible(node, "rockchip,rk3399-pinctrl") ||
	    ofw_bus_node_is_compatible(node, "rockchip,rk3288-pinctrl")) {
		if (OF_hasprop(node, "rockchip,pmu") &&
		    syscon_get_by_ofw_property(dev, node,
		    "rockchip,pmu", &sc->pmu) != 0) {
			device_printf(dev, "cannot get pmu driver handle\n");
			return (ENXIO);
		}
	}

	sc->conf = (struct rk_pinctrl_conf *)ofw_bus_search_compatible(dev,
	    compat_data)->ocd_data;

	fdt_pinctrl_register(dev, "rockchip,pins");

	simplebus_init(dev, node);

	bus_generic_probe(dev);

	/* Attach child devices */
	for (node = OF_child(node); node > 0; node = OF_peer(node)) {
		if (!ofw_bus_node_is_compatible(node, "rockchip,gpio-bank"))
			continue;

		rv = OF_getprop_alloc(node, "name", (void **)&gpio_name);
		if (rv <= 0) {
			device_printf(sc->dev, "Cannot GPIO subdevice name.\n");
			continue;
		}

		cdev = simplebus_add_device(dev, node, 0, NULL, -1, NULL);
		if (cdev == NULL) {
			device_printf(dev, " Cannot add GPIO subdevice: %s\n",
			    gpio_name);
			OF_prop_free(gpio_name);
			continue;
		}

		rv = device_probe_and_attach(cdev);
		if (rv != 0) {
			device_printf(sc->dev,
			    "Cannot attach GPIO subdevice: %s\n", gpio_name);
			OF_prop_free(gpio_name);
			continue;
		}

		/* Grep device name from name property */
		eptr = gpio_name;
		strsep(&eptr, "@");
		if (gpio_name == eptr) {
			device_printf(sc->dev,
			    "Unrecognized format of GPIO subdevice name: %s\n",
			    gpio_name);
			OF_prop_free(gpio_name);
			continue;
		}
		rv =  rk_pinctrl_register_gpio(sc, gpio_name, cdev);
		if (rv != 0) {
			device_printf(sc->dev,
			    "Cannot register GPIO subdevice %s: %d\n",
			    gpio_name, rv);
			OF_prop_free(gpio_name);
			continue;
		}
		OF_prop_free(gpio_name);
	}

	fdt_pinctrl_configure_tree(dev);

	return (bus_generic_attach(dev));
}