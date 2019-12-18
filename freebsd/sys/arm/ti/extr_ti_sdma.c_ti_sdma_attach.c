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
struct ti_sdma_softc {int sc_active_channels; int sc_hw_rev; int /*<<< orphan*/ * sc_irq_res; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/ * sc_mem_res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA4_IRQENABLE_L (unsigned int) ; 
 int /*<<< orphan*/  DMA4_OCP_SYSCONFIG ; 
 int /*<<< orphan*/  DMA4_REVISION ; 
 int /*<<< orphan*/  DMA4_SYSSTATUS ; 
 int EINVAL ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 unsigned int NUM_DMA_IRQS ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SDMA_CLK ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  TI_SDMA_LOCK_INIT (struct ti_sdma_softc*) ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 struct ti_sdma_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int hz ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 int /*<<< orphan*/  pause (char*,int) ; 
 int /*<<< orphan*/  ti_prcm_clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_sdma_intr ; 
 scalar_t__ ti_sdma_is_omap3_rev (struct ti_sdma_softc*) ; 
 int /*<<< orphan*/  ti_sdma_is_omap4_rev (struct ti_sdma_softc*) ; 
 int ti_sdma_read_4 (struct ti_sdma_softc*,int /*<<< orphan*/ ) ; 
 struct ti_sdma_softc* ti_sdma_sc ; 
 int /*<<< orphan*/  ti_sdma_write_4 (struct ti_sdma_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ti_sdma_attach(device_t dev)
{
	struct ti_sdma_softc *sc = device_get_softc(dev);
	unsigned int timeout;
	unsigned int i;
	int      rid;
	void    *ihl;
	int      err;

	/* Setup the basics */
	sc->sc_dev = dev;

	/* No channels active at the moment */
	sc->sc_active_channels = 0x00000000;

	/* Mutex to protect the shared data structures */
	TI_SDMA_LOCK_INIT(sc);

	/* Get the memory resource for the register mapping */
	rid = 0;
	sc->sc_mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid, RF_ACTIVE);
	if (sc->sc_mem_res == NULL)
		panic("%s: Cannot map registers", device_get_name(dev));

	/* Enable the interface and functional clocks */
	ti_prcm_clk_enable(SDMA_CLK);

	/* Read the sDMA revision register and sanity check it's known */
	sc->sc_hw_rev = ti_sdma_read_4(sc, DMA4_REVISION);
	device_printf(dev, "sDMA revision %08x\n", sc->sc_hw_rev);

	if (!ti_sdma_is_omap4_rev(sc) && !ti_sdma_is_omap3_rev(sc)) {
		device_printf(sc->sc_dev, "error - unknown sDMA H/W revision\n");
		return (EINVAL);
	}

	/* Disable all interrupts */
	for (i = 0; i < NUM_DMA_IRQS; i++) {
		ti_sdma_write_4(sc, DMA4_IRQENABLE_L(i), 0x00000000);
	}

	/* Soft-reset is only supported on pre-OMAP44xx devices */
	if (ti_sdma_is_omap3_rev(sc)) {

		/* Soft-reset */
		ti_sdma_write_4(sc, DMA4_OCP_SYSCONFIG, 0x0002);

		/* Set the timeout to 100ms*/
		timeout = (hz < 10) ? 1 : ((100 * hz) / 1000);

		/* Wait for DMA reset to complete */
		while ((ti_sdma_read_4(sc, DMA4_SYSSTATUS) & 0x1) == 0x0) {

			/* Sleep for a tick */
			pause("DMARESET", 1);

			if (timeout-- == 0) {
				device_printf(sc->sc_dev, "sDMA reset operation timed out\n");
				return (EINVAL);
			}
		}
	}

	/* 
	 * Install interrupt handlers for the for possible interrupts. Any channel
	 * can trip one of the four IRQs
	 */
	rid = 0;
	sc->sc_irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
	    RF_ACTIVE | RF_SHAREABLE);
	if (sc->sc_irq_res == NULL)
		panic("Unable to setup the dma irq handler.\n");

	err = bus_setup_intr(dev, sc->sc_irq_res, INTR_TYPE_MISC | INTR_MPSAFE,
	    NULL, ti_sdma_intr, NULL, &ihl);
	if (err)
		panic("%s: Cannot register IRQ", device_get_name(dev));

	/* Store the DMA structure globally ... this driver should never be unloaded */
	ti_sdma_sc = sc;

	return (0);
}