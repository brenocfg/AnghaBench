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
struct adt746x_softc {int /*<<< orphan*/  sc_addr; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 struct adt746x_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  iicbus_get_addr (int /*<<< orphan*/ ) ; 
 char* ofw_bus_get_compat (int /*<<< orphan*/ ) ; 
 char* ofw_bus_get_name (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
adt746x_probe(device_t dev)
{
	const char  *name, *compatible;
	struct adt746x_softc *sc;

	name = ofw_bus_get_name(dev);
	compatible = ofw_bus_get_compat(dev);

	if (!name)
		return (ENXIO);

	if (strcmp(name, "fan") != 0 ||
	    (strcmp(compatible, "adt7460") != 0 &&
	     strcmp(compatible, "adt7467") != 0))
		return (ENXIO);

	sc = device_get_softc(dev);
	sc->sc_dev = dev;
	sc->sc_addr = iicbus_get_addr(dev);

	device_set_desc(dev, "Apple Thermostat Unit ADT746X");

	return (0);
}