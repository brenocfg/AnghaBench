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
struct hrowpic_softc {int /*<<< orphan*/ * sc_rres; int /*<<< orphan*/  sc_bh; int /*<<< orphan*/  sc_bt; scalar_t__ sc_rrid; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HPIC_CLEAR ; 
 int /*<<< orphan*/  HPIC_ENABLE ; 
 int /*<<< orphan*/  HPIC_PRIMARY ; 
 int /*<<< orphan*/  HPIC_SECONDARY ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 struct hrowpic_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hrowpic_write_reg (struct hrowpic_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  powerpc_register_pic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
hrowpic_attach(device_t dev)
{
	struct hrowpic_softc *sc;

	sc = device_get_softc(dev);
	sc->sc_dev = dev;

	sc->sc_rrid = 0;
	sc->sc_rres = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &sc->sc_rrid,
	    RF_ACTIVE);

	if (sc->sc_rres == NULL) {
		device_printf(dev, "Could not alloc mem resource!\n");
		return (ENXIO);
	}

	sc->sc_bt = rman_get_bustag(sc->sc_rres);
	sc->sc_bh = rman_get_bushandle(sc->sc_rres);

	/*
	 * Disable all interrupt sources and clear outstanding interrupts
	 */
	hrowpic_write_reg(sc, HPIC_ENABLE, HPIC_PRIMARY, 0);
	hrowpic_write_reg(sc, HPIC_CLEAR,  HPIC_PRIMARY, 0xffffffff);
	hrowpic_write_reg(sc, HPIC_ENABLE, HPIC_SECONDARY, 0);
	hrowpic_write_reg(sc, HPIC_CLEAR,  HPIC_SECONDARY, 0xffffffff);

	powerpc_register_pic(dev, ofw_bus_get_node(dev), 64, 0, FALSE);
	return (0);
}