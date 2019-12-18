#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct gpiobus_ivar {int npins; size_t* pins; int /*<<< orphan*/  rl; } ;
struct ofw_gpiobus_devinfo {int /*<<< orphan*/  opd_obdinfo; struct gpiobus_ivar opd_dinfo; } ;
struct gpiobus_softc {size_t sc_npins; TYPE_1__* sc_pins; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ mapped; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 struct gpiobus_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct ofw_gpiobus_devinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiobus_free_ivars (struct gpiobus_ivar*) ; 
 int /*<<< orphan*/  ofw_bus_gen_destroy_devinfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resource_list_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ofw_gpiobus_destroy_devinfo(device_t bus, struct ofw_gpiobus_devinfo *dinfo)
{
	int i;
	struct gpiobus_ivar *devi;
	struct gpiobus_softc *sc;

	sc = device_get_softc(bus);
	devi = &dinfo->opd_dinfo;
	for (i = 0; i < devi->npins; i++) {
		if (devi->pins[i] > sc->sc_npins)
			continue;
		sc->sc_pins[devi->pins[i]].mapped = 0;
	}
	gpiobus_free_ivars(devi);
	resource_list_free(&dinfo->opd_dinfo.rl);
	ofw_bus_gen_destroy_devinfo(&dinfo->opd_obdinfo);
	free(dinfo, M_DEVBUF);
}