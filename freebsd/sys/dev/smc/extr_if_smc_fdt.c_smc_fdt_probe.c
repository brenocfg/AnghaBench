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
struct smc_softc {int smc_usemem; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 struct smc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ ofw_bus_is_compatible (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ofw_bus_status_okay (int /*<<< orphan*/ ) ; 
 scalar_t__ smc_probe (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
smc_fdt_probe(device_t dev)
{
	struct	smc_softc *sc;

	if (!ofw_bus_status_okay(dev))
		return (ENXIO);

	if (ofw_bus_is_compatible(dev, "smsc,lan91c111")) {
		sc = device_get_softc(dev);
		sc->smc_usemem = 1;

		if (smc_probe(dev) != 0) {
			return (ENXIO);
		}

		return (0);
	}

	return (ENXIO);
}