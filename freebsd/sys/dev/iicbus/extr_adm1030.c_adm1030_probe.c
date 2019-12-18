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
typedef  int /*<<< orphan*/  thermostat ;
struct adm1030_softc {int /*<<< orphan*/  sc_addr; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ OF_getprop (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 struct adm1030_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  iicbus_get_addr (int /*<<< orphan*/ ) ; 
 char* ofw_bus_get_compat (int /*<<< orphan*/ ) ; 
 char* ofw_bus_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
adm1030_probe(device_t dev)
{
	const char     *name, *compatible;
	struct adm1030_softc *sc;
	phandle_t	handle;
	phandle_t	thermostat;

	name = ofw_bus_get_name(dev);
	compatible = ofw_bus_get_compat(dev);
	handle = ofw_bus_get_node(dev);

	if (!name)
		return (ENXIO);

	if (strcmp(name, "fan") != 0 || strcmp(compatible, "adm1030") != 0)
		return (ENXIO);

	/* This driver can only be used if there's an associated temp sensor. */
	if (OF_getprop(handle, "platform-getTemp", &thermostat, sizeof(thermostat)) < 0)
		return (ENXIO);

	sc = device_get_softc(dev);
	sc->sc_dev = dev;
	sc->sc_addr = iicbus_get_addr(dev);

	device_set_desc(dev, "G4 MDD Fan driver");

	return (0);
}