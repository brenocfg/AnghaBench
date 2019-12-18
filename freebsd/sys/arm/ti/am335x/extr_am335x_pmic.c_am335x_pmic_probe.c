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
struct am335x_pmic_softc {int /*<<< orphan*/  sc_addr; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 struct am335x_pmic_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  iicbus_get_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_is_compatible (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
am335x_pmic_probe(device_t dev)
{
	struct am335x_pmic_softc *sc;

	if (!ofw_bus_is_compatible(dev, "ti,tps65217"))
		return (ENXIO);

	sc = device_get_softc(dev);
	sc->sc_dev = dev;
	/* Convert to 8-bit addressing */
	sc->sc_addr = iicbus_get_addr(dev);

	device_set_desc(dev, "TI TPS65217 Power Management IC");

	return (0);
}