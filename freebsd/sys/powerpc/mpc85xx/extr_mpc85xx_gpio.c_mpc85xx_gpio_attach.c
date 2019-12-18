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
struct mpc85xx_gpio_softc {int /*<<< orphan*/ * busdev; int /*<<< orphan*/ * in_res; int /*<<< orphan*/ * out_res; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GPIO_LOCK_INIT (struct mpc85xx_gpio_softc*) ; 
 int /*<<< orphan*/  OF_device_register_xref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OF_xref_from_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 struct mpc85xx_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * gpiobus_attach_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpc85xx_gpio_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mpc85xx_gpio_attach(device_t dev)
{
	struct mpc85xx_gpio_softc *sc = device_get_softc(dev);
	int rid;

	sc->dev = dev;

	GPIO_LOCK_INIT(sc);

	/* Allocate memory. */
	rid = 0;
	sc->out_res = bus_alloc_resource_any(dev,
		     SYS_RES_MEMORY, &rid, RF_ACTIVE);
	if (sc->out_res == NULL) {
		device_printf(dev, "Can't allocate memory for device output port");
		mpc85xx_gpio_detach(dev);
		return (ENOMEM);
	}

	rid = 1;
	sc->in_res = bus_alloc_resource_any(dev,
		     SYS_RES_MEMORY, &rid, RF_ACTIVE);
	if (sc->in_res == NULL) {
		device_printf(dev, "Can't allocate memory for device input port");
		mpc85xx_gpio_detach(dev);
		return (ENOMEM);
	}

	sc->busdev = gpiobus_attach_bus(dev);
	if (sc->busdev == NULL) {
		mpc85xx_gpio_detach(dev);
		return (ENOMEM);
	}

	OF_device_register_xref(OF_xref_from_node(ofw_bus_get_node(dev)), dev);

	return (0);
}