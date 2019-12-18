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
struct aml8726_gpio_softc {int npins; int /*<<< orphan*/ * res; int /*<<< orphan*/ * busdev; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  prop ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int pcell_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AML_GPIO_LOCK_DESTROY (struct aml8726_gpio_softc*) ; 
 int /*<<< orphan*/  AML_GPIO_LOCK_INIT (struct aml8726_gpio_softc*) ; 
 int ENXIO ; 
 scalar_t__ OF_getencprop (int /*<<< orphan*/ ,char*,int*,int) ; 
 int /*<<< orphan*/  aml8726_gpio_spec ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct aml8726_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * gpiobus_attach_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 scalar_t__ rman_get_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aml8726_gpio_attach(device_t dev)
{
	struct aml8726_gpio_softc *sc = device_get_softc(dev);
	phandle_t node;
	pcell_t prop;

	sc->dev = dev;

	node = ofw_bus_get_node(dev);

	if (OF_getencprop(node, "pin-count",
	    &prop, sizeof(prop)) <= 0) {
		device_printf(dev, "missing pin-count attribute in FDT\n");
		return (ENXIO);
	}
	sc->npins = prop;

	if (sc->npins > 32)
		return (ENXIO);

	if (bus_alloc_resources(dev, aml8726_gpio_spec, sc->res)) {
		device_printf(dev, "can not allocate resources for device\n");
		return (ENXIO);
	}

	/*
	 * The GPIOAO OUT bits occupy the upper word of the OEN register.
	 */
	if (rman_get_start(sc->res[1]) == rman_get_start(sc->res[0]))
	  if (sc->npins > 16) {
		device_printf(dev,
		    "too many pins for overlapping OEN and OUT\n");
		bus_release_resources(dev, aml8726_gpio_spec, sc->res);
		return (ENXIO);
		}

	AML_GPIO_LOCK_INIT(sc);

	sc->busdev = gpiobus_attach_bus(dev);
	if (sc->busdev == NULL) {
		AML_GPIO_LOCK_DESTROY(sc);
		bus_release_resources(dev, aml8726_gpio_spec, sc->res);
		return (ENXIO);
	}

	return (0);
}