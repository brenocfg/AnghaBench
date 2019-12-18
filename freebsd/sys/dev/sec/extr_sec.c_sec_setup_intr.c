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
struct sec_softc {int /*<<< orphan*/  sc_dev; } ;
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  driver_intr_t ;

/* Variables and functions */
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 struct resource* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,struct resource*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sec_softc*,void**) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static int
sec_setup_intr(struct sec_softc *sc, struct resource **ires, void **ihand,
    int *irid, driver_intr_t handler, const char *iname)
{
	int error;

	(*ires) = bus_alloc_resource_any(sc->sc_dev, SYS_RES_IRQ, irid,
	    RF_ACTIVE);

	if ((*ires) == NULL) {
		device_printf(sc->sc_dev, "could not allocate %s IRQ\n", iname);
		return (ENXIO);
	}

	error = bus_setup_intr(sc->sc_dev, *ires, INTR_MPSAFE | INTR_TYPE_NET,
	    NULL, handler, sc, ihand);

	if (error) {
		device_printf(sc->sc_dev, "failed to set up %s IRQ\n", iname);
		if (bus_release_resource(sc->sc_dev, SYS_RES_IRQ, *irid, *ires))
			device_printf(sc->sc_dev, "could not release %s IRQ\n",
			    iname);

		(*ires) = NULL;
		return (error);
	}

	return (0);
}