#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  max_clk; int /*<<< orphan*/  quirks; } ;
struct fsl_sdhci_softc {scalar_t__ hwtype; int slot_init_done; TYPE_1__ slot; int /*<<< orphan*/  gpio; int /*<<< orphan*/  baseclk_hz; int /*<<< orphan*/  intr_cookie; void* irq_res; void* mem_res; int /*<<< orphan*/  r1bfix_callout; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_6__ {scalar_t__ ocd_data; } ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ HWTYPE_NONE ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_BIO ; 
 scalar_t__ OF_hasprop (int /*<<< orphan*/ ,char*) ; 
 int RD4 (struct fsl_sdhci_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SDHCI_QUIRK_BROKEN_DMA ; 
 int /*<<< orphan*/  SDHCI_QUIRK_DATA_TIMEOUT_USES_SDCLK ; 
 int /*<<< orphan*/  SDHC_PROT_CTRL ; 
 int SDHC_PROT_EMODE_BIG ; 
 int SDHC_PROT_EMODE_LITTLE ; 
 int SDHC_PROT_EMODE_MASK ; 
 int /*<<< orphan*/  SDHC_WTMK_LVL ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  WR4 (struct fsl_sdhci_softc*,int /*<<< orphan*/ ,int) ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_probe (int /*<<< orphan*/ ) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct fsl_sdhci_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  compat_data ; 
 struct fsl_sdhci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fsl_sdhci_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsl_sdhci_get_platform_clock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsl_sdhci_intr ; 
 int /*<<< orphan*/  imx_ccm_sdhci_hz () ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 scalar_t__ ofw_bus_is_compatible (int /*<<< orphan*/ ,char*) ; 
 TYPE_4__* ofw_bus_search_compatible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  sdhci_fdt_gpio_setup (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  sdhci_init_slot (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_start_slot (TYPE_1__*) ; 

__attribute__((used)) static int
fsl_sdhci_attach(device_t dev)
{
	struct fsl_sdhci_softc *sc = device_get_softc(dev);
	int rid, err;
#ifdef __powerpc__
	phandle_t node;
	uint32_t protctl;
#endif

	sc->dev = dev;

	callout_init(&sc->r1bfix_callout, 1);

	sc->hwtype = ofw_bus_search_compatible(dev, compat_data)->ocd_data;
	if (sc->hwtype == HWTYPE_NONE)
		panic("Impossible: not compatible in fsl_sdhci_attach()");

	rid = 0;
	sc->mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (!sc->mem_res) {
		device_printf(dev, "cannot allocate memory window\n");
		err = ENXIO;
		goto fail;
	}

	rid = 0;
	sc->irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
	    RF_ACTIVE);
	if (!sc->irq_res) {
		device_printf(dev, "cannot allocate interrupt\n");
		err = ENXIO;
		goto fail;
	}

	if (bus_setup_intr(dev, sc->irq_res, INTR_TYPE_BIO | INTR_MPSAFE,
	    NULL, fsl_sdhci_intr, sc, &sc->intr_cookie)) {
		device_printf(dev, "cannot setup interrupt handler\n");
		err = ENXIO;
		goto fail;
	}

	sc->slot.quirks |= SDHCI_QUIRK_DATA_TIMEOUT_USES_SDCLK;

	/*
	 * DMA is not really broken, I just haven't implemented it yet.
	 */
	sc->slot.quirks |= SDHCI_QUIRK_BROKEN_DMA;

	/*
	 * Set the buffer watermark level to 128 words (512 bytes) for both read
	 * and write.  The hardware has a restriction that when the read or
	 * write ready status is asserted, that means you can read exactly the
	 * number of words set in the watermark register before you have to
	 * re-check the status and potentially wait for more data.  The main
	 * sdhci driver provides no hook for doing status checking on less than
	 * a full block boundary, so we set the watermark level to be a full
	 * block.  Reads and writes where the block size is less than the
	 * watermark size will work correctly too, no need to change the
	 * watermark for different size blocks.  However, 128 is the maximum
	 * allowed for the watermark, so PIO is limitted to 512 byte blocks
	 * (which works fine for SD cards, may be a problem for SDIO some day).
	 *
	 * XXX need named constants for this stuff.
	 */
	/* P1022 has the '*_BRST_LEN' fields as reserved, always reading 0x10 */
	if (ofw_bus_is_compatible(dev, "fsl,p1022-esdhc"))
		WR4(sc, SDHC_WTMK_LVL, 0x10801080);
	else
		WR4(sc, SDHC_WTMK_LVL, 0x08800880);

	/*
	 * We read in native byte order in the main driver, but the register
	 * defaults to little endian.
	 */
#ifdef __powerpc__
	sc->baseclk_hz = fsl_sdhci_get_platform_clock(dev);
#else
	sc->baseclk_hz = imx_ccm_sdhci_hz();
#endif
	sc->slot.max_clk = sc->baseclk_hz;

	/*
	 * Set up any gpio pin handling described in the FDT data. This cannot
	 * fail; see comments in sdhci_fdt_gpio.h for details.
	 */
	sc->gpio = sdhci_fdt_gpio_setup(dev, &sc->slot);

#ifdef __powerpc__
	node = ofw_bus_get_node(dev);
	/* Default to big-endian on powerpc */
	protctl = RD4(sc, SDHC_PROT_CTRL);
	protctl &= ~SDHC_PROT_EMODE_MASK;
	if (OF_hasprop(node, "little-endian"))
		protctl |= SDHC_PROT_EMODE_LITTLE;
	else
		protctl |= SDHC_PROT_EMODE_BIG;
	WR4(sc, SDHC_PROT_CTRL, protctl);
#endif

	sdhci_init_slot(dev, &sc->slot, 0);
	sc->slot_init_done = true;

	bus_generic_probe(dev);
	bus_generic_attach(dev);

	sdhci_start_slot(&sc->slot);

	return (0);

fail:
	fsl_sdhci_detach(dev);
	return (err);
}