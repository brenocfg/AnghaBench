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
struct ti_spi_softc {int sc_numcs; int /*<<< orphan*/  sc_mtx; void* sc_mem_res; void* sc_irq_res; int /*<<< orphan*/  sc_intrhand; int /*<<< orphan*/  sc_bsh; int /*<<< orphan*/  sc_bst; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int EINVAL ; 
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int INVALID_CLK_IDENT ; 
 int /*<<< orphan*/  MCSPI_CONF_CH (int) ; 
 int MCSPI_CONF_DPE0 ; 
 int MCSPI_CONF_EPOL ; 
 int MCSPI_CONF_WL_SHIFT ; 
 int /*<<< orphan*/  MCSPI_IRQENABLE ; 
 int /*<<< orphan*/  MCSPI_IRQSTATUS ; 
 int /*<<< orphan*/  MCSPI_MODULCTRL ; 
 int MCSPI_MODULCTRL_SINGLE ; 
 int /*<<< orphan*/  MCSPI_REVISION ; 
 int MCSPI_REVISION_CUSTOM_MSK ; 
 int MCSPI_REVISION_CUSTOM_SHIFT ; 
 int MCSPI_REVISION_FUNC_MSK ; 
 int MCSPI_REVISION_FUNC_SHIFT ; 
 int MCSPI_REVISION_MAJOR_MSK ; 
 int MCSPI_REVISION_MAJOR_SHIFT ; 
 int MCSPI_REVISION_MINOR_MSK ; 
 int MCSPI_REVISION_MINOR_SHIFT ; 
 int MCSPI_REVISION_RTL_MSK ; 
 int MCSPI_REVISION_RTL_SHIFT ; 
 int MCSPI_REVISION_SCHEME_MSK ; 
 int MCSPI_REVISION_SCHEME_SHIFT ; 
 int /*<<< orphan*/  MCSPI_SYSCONFIG ; 
 int MCSPI_SYSCONFIG_SOFTRESET ; 
 int /*<<< orphan*/  MCSPI_SYSSTATUS ; 
 int MCSPI_SYSSTATUS_RESETDONE ; 
 int /*<<< orphan*/  MTX_DEF ; 
 scalar_t__ OF_getencprop (int /*<<< orphan*/ ,char*,int*,int) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int TI_SPI_READ (struct ti_spi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TI_SPI_WRITE (struct ti_spi_softc*,int /*<<< orphan*/ ,int) ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ti_spi_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 struct ti_spi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (void*) ; 
 int /*<<< orphan*/  rman_get_bustag (void*) ; 
 int ti_hwmods_get_clock (int /*<<< orphan*/ ) ; 
 int ti_prcm_clk_enable (int) ; 
 int /*<<< orphan*/  ti_spi_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_spi_intr ; 
 int /*<<< orphan*/  ti_spi_printr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_spi_set_clock (struct ti_spi_softc*,int,int) ; 

__attribute__((used)) static int
ti_spi_attach(device_t dev)
{
	int clk_id, err, i, rid, timeout;
	struct ti_spi_softc *sc;
	uint32_t rev;

	sc = device_get_softc(dev);
	sc->sc_dev = dev;

	/*
	 * Get the MMCHS device id from FDT.  If it's not there use the newbus
	 * unit number (which will work as long as the devices are in order and
	 * none are skipped in the fdt).  Note that this is a property we made
	 * up and added in freebsd, it doesn't exist in the published bindings.
	 */
	clk_id = ti_hwmods_get_clock(dev);
	if (clk_id == INVALID_CLK_IDENT) {
		device_printf(dev,
		    "failed to get clock based on hwmods property\n");
		return (EINVAL);
	}

	/* Activate the McSPI module. */
	err = ti_prcm_clk_enable(clk_id);
	if (err) {
		device_printf(dev, "Error: failed to activate source clock\n");
		return (err);
	}

	/* Get the number of available channels. */
	if ((OF_getencprop(ofw_bus_get_node(dev), "ti,spi-num-cs",
	    &sc->sc_numcs, sizeof(sc->sc_numcs))) <= 0) {
		sc->sc_numcs = 2;
	}

	rid = 0;
	sc->sc_mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (!sc->sc_mem_res) {
		device_printf(dev, "cannot allocate memory window\n");
		return (ENXIO);
	}

	sc->sc_bst = rman_get_bustag(sc->sc_mem_res);
	sc->sc_bsh = rman_get_bushandle(sc->sc_mem_res);

	rid = 0;
	sc->sc_irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
	    RF_ACTIVE);
	if (!sc->sc_irq_res) {
		bus_release_resource(dev, SYS_RES_MEMORY, 0, sc->sc_mem_res);
		device_printf(dev, "cannot allocate interrupt\n");
		return (ENXIO);
	}

	/* Hook up our interrupt handler. */
	if (bus_setup_intr(dev, sc->sc_irq_res, INTR_TYPE_MISC | INTR_MPSAFE,
	    NULL, ti_spi_intr, sc, &sc->sc_intrhand)) {
		bus_release_resource(dev, SYS_RES_IRQ, 0, sc->sc_irq_res);
		bus_release_resource(dev, SYS_RES_MEMORY, 0, sc->sc_mem_res);
		device_printf(dev, "cannot setup the interrupt handler\n");
		return (ENXIO);
	}

	mtx_init(&sc->sc_mtx, "ti_spi", NULL, MTX_DEF);

	/* Issue a softreset to the controller */
	TI_SPI_WRITE(sc, MCSPI_SYSCONFIG, MCSPI_SYSCONFIG_SOFTRESET);
	timeout = 1000;
	while (!(TI_SPI_READ(sc, MCSPI_SYSSTATUS) &
	    MCSPI_SYSSTATUS_RESETDONE)) {
		if (--timeout == 0) {
			device_printf(dev,
			    "Error: Controller reset operation timed out\n");
			ti_spi_detach(dev);
			return (ENXIO);
		}
		DELAY(100);
	}

	/* Print the McSPI module revision. */
	rev = TI_SPI_READ(sc, MCSPI_REVISION);
	device_printf(dev,
	    "scheme: %#x func: %#x rtl: %d rev: %d.%d custom rev: %d\n",
	    (rev >> MCSPI_REVISION_SCHEME_SHIFT) & MCSPI_REVISION_SCHEME_MSK,
	    (rev >> MCSPI_REVISION_FUNC_SHIFT) & MCSPI_REVISION_FUNC_MSK,
	    (rev >> MCSPI_REVISION_RTL_SHIFT) & MCSPI_REVISION_RTL_MSK,
	    (rev >> MCSPI_REVISION_MAJOR_SHIFT) & MCSPI_REVISION_MAJOR_MSK,
	    (rev >> MCSPI_REVISION_MINOR_SHIFT) & MCSPI_REVISION_MINOR_MSK,
	    (rev >> MCSPI_REVISION_CUSTOM_SHIFT) & MCSPI_REVISION_CUSTOM_MSK);

	/* Set Master mode, single channel. */
	TI_SPI_WRITE(sc, MCSPI_MODULCTRL, MCSPI_MODULCTRL_SINGLE);

	/* Clear pending interrupts and disable interrupts. */
	TI_SPI_WRITE(sc, MCSPI_IRQENABLE, 0x0);
	TI_SPI_WRITE(sc, MCSPI_IRQSTATUS, 0xffff);

	for (i = 0; i < sc->sc_numcs; i++) {
		/*
		 * Default to SPI mode 0, CS active low, 8 bits word length and
		 * 500kHz clock.
		 */
		TI_SPI_WRITE(sc, MCSPI_CONF_CH(i),
		    MCSPI_CONF_DPE0 | MCSPI_CONF_EPOL |
		    (8 - 1) << MCSPI_CONF_WL_SHIFT);
		/* Set initial clock - 500kHz. */
		ti_spi_set_clock(sc, i, 500000);
	}

#ifdef	TI_SPI_DEBUG
	ti_spi_printr(dev);
#endif

	device_add_child(dev, "spibus", -1);

	return (bus_generic_attach(dev));
}