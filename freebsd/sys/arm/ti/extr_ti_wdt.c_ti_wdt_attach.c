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
struct ti_wdt_softc {int /*<<< orphan*/  sc_ev_tag; int /*<<< orphan*/  sc_intr; int /*<<< orphan*/ * sc_irq_res; int /*<<< orphan*/ * sc_mem_res; int /*<<< orphan*/  sc_bh; int /*<<< orphan*/  sc_bt; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int ENXIO ; 
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ti_wdt_softc*,int /*<<< orphan*/ ) ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int TI_IRQ_EN_DLY ; 
 int TI_IRQ_EN_OVF ; 
 int TI_WDSC_SR ; 
 int /*<<< orphan*/  TI_WDT_WDSC ; 
 int /*<<< orphan*/  TI_WDT_WIDR ; 
 int /*<<< orphan*/  TI_WDT_WIRQENSET ; 
 scalar_t__ bootverbose ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ti_wdt_softc*,int /*<<< orphan*/ *) ; 
 struct ti_wdt_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ti_wdt_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_wdt_disable (struct ti_wdt_softc*) ; 
 int /*<<< orphan*/  ti_wdt_event ; 
 int /*<<< orphan*/  ti_wdt_intr ; 
 int ti_wdt_reg_read (struct ti_wdt_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_wdt_reg_write (struct ti_wdt_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  watchdog_list ; 

__attribute__((used)) static int
ti_wdt_attach(device_t dev)
{
	struct ti_wdt_softc *sc;
	int rid;

	sc = device_get_softc(dev);
	rid = 0;
	sc->sc_mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (sc->sc_mem_res == NULL) {
		device_printf(dev, "could not allocate memory resource\n");
		return (ENXIO);
	}
	sc->sc_bt = rman_get_bustag(sc->sc_mem_res);
	sc->sc_bh = rman_get_bushandle(sc->sc_mem_res);
	sc->sc_irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid, RF_ACTIVE);
	if (sc->sc_irq_res == NULL) {
		device_printf(dev, "could not allocate interrupt resource\n");
		ti_wdt_detach(dev);
		return (ENXIO);
	}
	if (bus_setup_intr(dev, sc->sc_irq_res, INTR_MPSAFE | INTR_TYPE_MISC,
		NULL, ti_wdt_intr, sc,  &sc->sc_intr) != 0) {
		device_printf(dev,
		    "unable to setup the interrupt handler\n");
		ti_wdt_detach(dev);
		return (ENXIO);
	}
	/* Reset, enable interrupts and stop the watchdog. */
	ti_wdt_reg_write(sc, TI_WDT_WDSC,
	    ti_wdt_reg_read(sc, TI_WDT_WDSC) | TI_WDSC_SR);
	while (ti_wdt_reg_read(sc, TI_WDT_WDSC) & TI_WDSC_SR)
		DELAY(10);
	ti_wdt_reg_write(sc, TI_WDT_WIRQENSET, TI_IRQ_EN_OVF | TI_IRQ_EN_DLY);
	ti_wdt_disable(sc);
	if (bootverbose)
		device_printf(dev, "revision: 0x%x\n",
		    ti_wdt_reg_read(sc, TI_WDT_WIDR));
	sc->sc_ev_tag = EVENTHANDLER_REGISTER(watchdog_list, ti_wdt_event, sc,
	    0);

	return (0);
}