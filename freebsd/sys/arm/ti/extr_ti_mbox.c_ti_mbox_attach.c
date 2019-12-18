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
typedef  int uint32_t ;
struct ti_mbox_softc {int /*<<< orphan*/  sc_intr; int /*<<< orphan*/ * sc_irq_res; int /*<<< orphan*/ * sc_mem_res; int /*<<< orphan*/  sc_bh; int /*<<< orphan*/  sc_bt; int /*<<< orphan*/  sc_mtx; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  DPRINTF (char*,int) ; 
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int /*<<< orphan*/  MAILBOX0_CLK ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  TI_MBOX_IRQENABLE_SET (int) ; 
 int /*<<< orphan*/  TI_MBOX_REVISION ; 
 int /*<<< orphan*/  TI_MBOX_SYSCONFIG ; 
 int TI_MBOX_SYSCONFIG_SMARTIDLE ; 
 int TI_MBOX_SYSCONFIG_SOFTRST ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ti_mbox_softc*,int /*<<< orphan*/ *) ; 
 struct ti_mbox_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ti_mbox_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_mbox_intr ; 
 int ti_mbox_reg_read (struct ti_mbox_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_mbox_reg_write (struct ti_mbox_softc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ti_prcm_clk_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ti_mbox_attach(device_t dev)
{
	struct ti_mbox_softc *sc;
	int rid, delay, chan;
	uint32_t rev, sysconfig;

	if (ti_prcm_clk_enable(MAILBOX0_CLK) != 0) {
		device_printf(dev, "could not enable MBOX clock\n");
		return (ENXIO);
	}
	sc = device_get_softc(dev);
	rid = 0;
	mtx_init(&sc->sc_mtx, "TI mbox", NULL, MTX_DEF);
	sc->sc_mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (sc->sc_mem_res == NULL) {
		device_printf(dev, "could not allocate memory resource\n");
		return (ENXIO);
	}
	sc->sc_bt = rman_get_bustag(sc->sc_mem_res);
	sc->sc_bh = rman_get_bushandle(sc->sc_mem_res);
	rid = 0;
	sc->sc_irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
	    RF_ACTIVE);
	if (sc->sc_irq_res == NULL) {
		device_printf(dev, "could not allocate interrupt resource\n");
		ti_mbox_detach(dev);
		return (ENXIO);
	}
	if (bus_setup_intr(dev, sc->sc_irq_res, INTR_MPSAFE | INTR_TYPE_MISC,
	    NULL, ti_mbox_intr, sc, &sc->sc_intr) != 0) {
		device_printf(dev, "unable to setup the interrupt handler\n");
		ti_mbox_detach(dev);
		return (ENXIO);
	}
	/*
	 * Reset the controller.
	 */
	sysconfig = ti_mbox_reg_read(sc, TI_MBOX_SYSCONFIG);
	DPRINTF("initial sysconfig %d\n", sysconfig);
	sysconfig |= TI_MBOX_SYSCONFIG_SOFTRST;
	delay = 100;
	while (ti_mbox_reg_read(sc, TI_MBOX_SYSCONFIG) & 
	    TI_MBOX_SYSCONFIG_SOFTRST) {
		delay--;
		DELAY(10);
	}
	if (delay == 0) {
		device_printf(dev, "controller reset failed\n");
		ti_mbox_detach(dev);
		return (ENXIO);
	}
	/*
	 * Enable smart idle mode.
	 */
	ti_mbox_reg_write(sc, TI_MBOX_SYSCONFIG,
	    ti_mbox_reg_read(sc, TI_MBOX_SYSCONFIG) | TI_MBOX_SYSCONFIG_SMARTIDLE);
	rev = ti_mbox_reg_read(sc, TI_MBOX_REVISION);
	DPRINTF("rev %d\n", rev);
	device_printf(dev, "revision %d.%d\n", (rev >> 8) & 0x4, rev & 0x40);
	/*
	 * Enable message interrupts.
	 */
	for (chan = 0; chan < 8; chan++)
		ti_mbox_reg_write(sc, TI_MBOX_IRQENABLE_SET(chan), 1);

	return (0);
}