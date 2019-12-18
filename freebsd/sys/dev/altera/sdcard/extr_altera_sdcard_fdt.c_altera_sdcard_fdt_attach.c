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
struct altera_sdcard_softc {int /*<<< orphan*/ * as_res; scalar_t__ as_rid; int /*<<< orphan*/  as_unit; int /*<<< orphan*/  as_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  altera_sdcard_attach (struct altera_sdcard_softc*) ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 struct altera_sdcard_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
altera_sdcard_fdt_attach(device_t dev)
{
	struct altera_sdcard_softc *sc;

	sc = device_get_softc(dev);
	sc->as_dev = dev;
	sc->as_unit = device_get_unit(dev);
	sc->as_rid = 0;
	sc->as_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
	    &sc->as_rid, RF_ACTIVE);
	if (sc->as_res == NULL) {
		device_printf(dev, "couldn't map memory\n");
		return (ENXIO);
	}
	altera_sdcard_attach(sc);
	return (0);
}