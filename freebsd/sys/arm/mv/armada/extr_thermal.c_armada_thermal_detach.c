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
struct armada_thermal_softc {int /*<<< orphan*/ * ctrl_res; int /*<<< orphan*/ * stat_res; scalar_t__ chip_temperature; int /*<<< orphan*/  temp_upd; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 struct armada_thermal_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_rid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
armada_thermal_detach(device_t dev)
{
	struct armada_thermal_softc *sc;

	sc = device_get_softc(dev);

	if (!device_is_attached(dev))
		return (0);

	callout_drain(&sc->temp_upd);

	sc->chip_temperature = 0;

	bus_release_resource(dev, SYS_RES_MEMORY,
	    rman_get_rid(sc->stat_res), sc->stat_res);
	sc->stat_res = NULL;

	bus_release_resource(dev, SYS_RES_MEMORY,
	    rman_get_rid(sc->ctrl_res), sc->ctrl_res);
	sc->ctrl_res = NULL;

	return (0);
}