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
struct terasic_de4led_softc {int /*<<< orphan*/ * tdl_res; scalar_t__ tdl_rid; int /*<<< orphan*/  tdl_unit; int /*<<< orphan*/  tdl_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 struct terasic_de4led_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  terasic_de4led_attach (struct terasic_de4led_softc*) ; 

__attribute__((used)) static int
terasic_de4led_nexus_attach(device_t dev)
{
	struct terasic_de4led_softc *sc;

	sc = device_get_softc(dev);
	sc->tdl_dev = dev;
	sc->tdl_unit = device_get_unit(dev);
	sc->tdl_rid = 0;
	sc->tdl_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
	    &sc->tdl_rid, RF_ACTIVE);
	if (sc->tdl_res == NULL) {
		device_printf(dev, "couldn't map memory\n");
		return (ENXIO);
	}
	terasic_de4led_attach(sc);
	return (0);
}