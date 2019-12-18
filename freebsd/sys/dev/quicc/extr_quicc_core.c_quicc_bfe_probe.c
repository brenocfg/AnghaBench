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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  u_int ;
struct quicc_softc {int /*<<< orphan*/ * sc_rres; scalar_t__ sc_rrid; int /*<<< orphan*/  sc_rtype; int /*<<< orphan*/  sc_clock; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 int /*<<< orphan*/  QUICC_PRAM_REV_NUM ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * device_get_desc (int /*<<< orphan*/ ) ; 
 struct quicc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int quicc_read2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
quicc_bfe_probe(device_t dev, u_int clock)
{
	struct quicc_softc *sc;
	uint16_t rev;

	sc = device_get_softc(dev);
	sc->sc_dev = dev;
	if (device_get_desc(dev) == NULL)
		device_set_desc(dev,
		    "Quad integrated communications controller");

	sc->sc_rrid = 0;
	sc->sc_rtype = SYS_RES_MEMORY;
	sc->sc_rres = bus_alloc_resource_any(dev, sc->sc_rtype, &sc->sc_rrid,
	    RF_ACTIVE);
	if (sc->sc_rres == NULL) {
		sc->sc_rrid = 0;
		sc->sc_rtype = SYS_RES_IOPORT;
		sc->sc_rres = bus_alloc_resource_any(dev, sc->sc_rtype,
		    &sc->sc_rrid, RF_ACTIVE);
		if (sc->sc_rres == NULL)
			return (ENXIO);
	}

	sc->sc_clock = clock;

	/*
	 * Check that the microcode revision is 0x00e8, as documented
	 * in the MPC8555E PowerQUICC III Integrated Processor Family
	 * Reference Manual.
	 */
	rev = quicc_read2(sc->sc_rres, QUICC_PRAM_REV_NUM);

	bus_release_resource(dev, sc->sc_rtype, sc->sc_rrid, sc->sc_rres);
	return ((rev == 0x00e8) ? BUS_PROBE_DEFAULT : ENXIO);
}