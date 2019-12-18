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
struct syscon_generic_softc {int /*<<< orphan*/ * syscon; int /*<<< orphan*/ * mem_res; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYSCON_LOCK_INIT (struct syscon_generic_softc*) ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 struct syscon_generic_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * syscon_create_ofw_node (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syscon_generic_class ; 

__attribute__((used)) static int
syscon_generic_attach(device_t dev)
{
	struct syscon_generic_softc *sc;
	int rid;

	sc = device_get_softc(dev);
	sc->dev = dev;
	rid = 0;

	sc->mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (sc->mem_res == NULL) {
		device_printf(dev, "Cannot allocate memory resource\n");
		return (ENXIO);
	}

	SYSCON_LOCK_INIT(sc);
	sc->syscon = syscon_create_ofw_node(dev, &syscon_generic_class,
		ofw_bus_get_node(dev));
	if (sc->syscon == NULL) {
		device_printf(dev, "Failed to create/register syscon\n");
		return (ENXIO);
	}
	return (0);
}