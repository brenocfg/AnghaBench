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
typedef  int uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  bst; int /*<<< orphan*/  bsh; } ;
struct tsec_softc {int is_etsec; int /*<<< orphan*/ * sc_rres; scalar_t__ sc_rrid; TYPE_1__ sc_bas; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int TSEC_ETSEC_ID ; 
 int TSEC_READ (struct tsec_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TSEC_REG_ID ; 
 int /*<<< orphan*/  TSEC_REG_ID2 ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 struct tsec_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * ofw_bus_get_type (int /*<<< orphan*/ ) ; 
 scalar_t__ ofw_bus_is_compatible (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ofw_bus_status_okay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
tsec_fdt_probe(device_t dev)
{
	struct tsec_softc *sc;
	uint32_t id;

	if (!ofw_bus_status_okay(dev))
		return (ENXIO);

	if (ofw_bus_get_type(dev) == NULL ||
	    strcmp(ofw_bus_get_type(dev), "network") != 0)
		return (ENXIO);

	if (!ofw_bus_is_compatible(dev, "gianfar") &&
	    !ofw_bus_is_compatible(dev, "fsl,etsec2"))
		return (ENXIO);

	sc = device_get_softc(dev);

	/*
	 * Device trees with "fsl,etsec2" compatible nodes don't have a reg
	 * property, as it's been relegated to the queue-group children.
	 */
	if (ofw_bus_is_compatible(dev, "fsl,etsec2"))
		sc->is_etsec = 1;
	else {
		sc->sc_rrid = 0;
		sc->sc_rres = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &sc->sc_rrid,
		    RF_ACTIVE);
		if (sc->sc_rres == NULL)
			return (ENXIO);

		sc->sc_bas.bsh = rman_get_bushandle(sc->sc_rres);
		sc->sc_bas.bst = rman_get_bustag(sc->sc_rres);

		/* Check if we are eTSEC (enhanced TSEC) */
		id = TSEC_READ(sc, TSEC_REG_ID);
		sc->is_etsec = ((id >> 16) == TSEC_ETSEC_ID) ? 1 : 0;
		id |= TSEC_READ(sc, TSEC_REG_ID2);

		bus_release_resource(dev, SYS_RES_MEMORY, sc->sc_rrid, sc->sc_rres);

		if (id == 0) {
			device_printf(dev, "could not identify TSEC type\n");
			return (ENXIO);
		}
	}

	if (sc->is_etsec)
		device_set_desc(dev, "Enhanced Three-Speed Ethernet Controller");
	else
		device_set_desc(dev, "Three-Speed Ethernet Controller");

	return (BUS_PROBE_DEFAULT);
}