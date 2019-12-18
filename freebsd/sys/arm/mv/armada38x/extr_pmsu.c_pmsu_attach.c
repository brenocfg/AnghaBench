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
struct pmsu_softc {int /*<<< orphan*/  res; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct pmsu_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pmsu_spec ; 

__attribute__((used)) static int
pmsu_attach(device_t dev)
{
	struct pmsu_softc *sc;
	int err;

	sc = device_get_softc(dev);
	sc->dev = dev;

	err = bus_alloc_resources(dev, pmsu_spec, &sc->res);
	if (err != 0) {
		device_printf(dev, "could not allocate resources\n");
		return (ENXIO);
	}

	return (0);
}