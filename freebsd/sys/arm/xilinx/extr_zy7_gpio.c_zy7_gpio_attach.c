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
struct zy7_gpio_softc {int /*<<< orphan*/ * busdev; int /*<<< orphan*/ * mem_res; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  ZGPIO_LOCK_INIT (struct zy7_gpio_softc*) ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 struct zy7_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * gpiobus_attach_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zy7_gpio_detach (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zy7_gpio_attach(device_t dev)
{
	struct zy7_gpio_softc *sc = device_get_softc(dev);
	int rid;

	sc->dev = dev;

	ZGPIO_LOCK_INIT(sc);

	/* Allocate memory. */
	rid = 0;
	sc->mem_res = bus_alloc_resource_any(dev,
		     SYS_RES_MEMORY, &rid, RF_ACTIVE);
	if (sc->mem_res == NULL) {
		device_printf(dev, "Can't allocate memory for device");
		zy7_gpio_detach(dev);
		return (ENOMEM);
	}

	sc->busdev = gpiobus_attach_bus(dev);
	if (sc->busdev == NULL) {
		zy7_gpio_detach(dev);
		return (ENOMEM);
	}

	return (0);
}