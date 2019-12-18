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
struct dpaa_portals_softc {int /*<<< orphan*/  sc_dp_size; int /*<<< orphan*/  sc_dp_pa; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  OCP85XX_TGTIF_BMAN ; 
 int /*<<< orphan*/  XX_PortalSetInfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bman_portals_detach (int /*<<< orphan*/ ) ; 
 struct dpaa_portals_softc* bp_sc ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 struct dpaa_portals_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ law_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
bman_portals_attach(device_t dev)
{
	struct dpaa_portals_softc *sc;

	sc = bp_sc = device_get_softc(dev);
	
	/* Map bman portal to physical address space */
	if (law_enable(OCP85XX_TGTIF_BMAN, sc->sc_dp_pa, sc->sc_dp_size)) {
		bman_portals_detach(dev);
		return (ENXIO);
	}
	/* Set portal properties for XX_VirtToPhys() */
	XX_PortalSetInfo(dev);

	return (bus_generic_attach(dev));
}