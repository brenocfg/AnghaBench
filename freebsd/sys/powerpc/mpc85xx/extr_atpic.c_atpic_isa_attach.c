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
struct atpic_softc {int* sc_rid; int sc_irid; int /*<<< orphan*/ ** sc_res; int /*<<< orphan*/ * sc_ires; int /*<<< orphan*/  sc_icookie; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 size_t ATPIC_MASTER ; 
 size_t ATPIC_SLAVE ; 
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  atpic_init (struct atpic_softc*,size_t) ; 
 int /*<<< orphan*/  atpic_intr ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct atpic_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  powerpc_register_pic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
atpic_isa_attach(device_t dev)
{
	struct atpic_softc *sc;
	int error;

	sc = device_get_softc(dev);
	sc->sc_dev = dev;

	error = ENXIO;

	sc->sc_rid[ATPIC_MASTER] = 0;
	sc->sc_res[ATPIC_MASTER] = bus_alloc_resource_any(dev, SYS_RES_IOPORT,
	    &sc->sc_rid[ATPIC_MASTER], RF_ACTIVE);
	if (sc->sc_res[ATPIC_MASTER] == NULL)
		goto fail;

	sc->sc_rid[ATPIC_SLAVE] = 1;
	sc->sc_res[ATPIC_SLAVE] = bus_alloc_resource_any(dev, SYS_RES_IOPORT,
	    &sc->sc_rid[ATPIC_SLAVE], RF_ACTIVE);
	if (sc->sc_res[ATPIC_SLAVE] == NULL)
		goto fail;

	sc->sc_irid = 0;
	sc->sc_ires = bus_alloc_resource_any(dev, SYS_RES_IRQ, &sc->sc_irid,
	    RF_ACTIVE);
	if (sc->sc_ires == NULL)
		goto fail;

	error = bus_setup_intr(dev, sc->sc_ires, INTR_TYPE_MISC | INTR_MPSAFE,
	    NULL, atpic_intr, dev, &sc->sc_icookie);
	if (error)
		goto fail;

	atpic_init(sc, ATPIC_SLAVE);
	atpic_init(sc, ATPIC_MASTER);

	powerpc_register_pic(dev, 0, 16, 0, TRUE);
	return (0);

 fail:
	if (sc->sc_ires != NULL)
		bus_release_resource(dev, SYS_RES_IRQ, sc->sc_irid,
		    sc->sc_ires);
	if (sc->sc_res[ATPIC_SLAVE] != NULL)
		bus_release_resource(dev, SYS_RES_IOPORT,
		    sc->sc_rid[ATPIC_SLAVE], sc->sc_res[ATPIC_SLAVE]);
	if (sc->sc_res[ATPIC_MASTER] != NULL)
		bus_release_resource(dev, SYS_RES_IOPORT,
		    sc->sc_rid[ATPIC_MASTER], sc->sc_res[ATPIC_MASTER]);
	return (error);
}