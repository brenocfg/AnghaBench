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
typedef  int /*<<< orphan*/  uint32_t ;
struct tegra124_pmc_softc {scalar_t__ sysclkreq_high; int /*<<< orphan*/ * mem_res; int /*<<< orphan*/  dev; int /*<<< orphan*/  clk; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  PMC_CNTRL ; 
 int /*<<< orphan*/  PMC_CNTRL_CPU_PWRREQ_OE ; 
 int /*<<< orphan*/  PMC_CNTRL_SYSCLK_OE ; 
 int /*<<< orphan*/  PMC_CNTRL_SYSCLK_POLARITY ; 
 int /*<<< orphan*/  PMC_IO_DPD2_STATUS ; 
 int /*<<< orphan*/  PMC_IO_DPD2_STATUS_HV ; 
 int /*<<< orphan*/  PMC_IO_DPD_STATUS ; 
 int /*<<< orphan*/  PMC_IO_DPD_STATUS_HDMI ; 
 int /*<<< orphan*/  PMC_LOCK_INIT (struct tegra124_pmc_softc*) ; 
 int /*<<< orphan*/  RD4 (struct tegra124_pmc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  WR4 (struct tegra124_pmc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int clk_get_by_ofw_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 struct tegra124_pmc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 struct tegra124_pmc_softc* pmc_sc ; 
 int tegra124_pmc_parse_fdt (struct tegra124_pmc_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tegra124_pmc_attach(device_t dev)
{
	struct tegra124_pmc_softc *sc;
	int rid, rv;
	uint32_t reg;
	phandle_t node;

	sc = device_get_softc(dev);
	sc->dev = dev;
	node = ofw_bus_get_node(dev);

	rv = tegra124_pmc_parse_fdt(sc, node);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot parse FDT data\n");
		return (rv);
	}

	rv = clk_get_by_ofw_name(sc->dev, 0, "pclk", &sc->clk);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot get \"pclk\" clock\n");
		return (ENXIO);
	}

	rid = 0;
	sc->mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (sc->mem_res == NULL) {
		device_printf(dev, "Cannot allocate memory resources\n");
		return (ENXIO);
	}

	PMC_LOCK_INIT(sc);

	/* Enable CPU power request. */
	reg = RD4(sc, PMC_CNTRL);
	reg |= PMC_CNTRL_CPU_PWRREQ_OE;
	WR4(sc, PMC_CNTRL, reg);

	/* Set sysclk output polarity */
	reg = RD4(sc, PMC_CNTRL);
	if (sc->sysclkreq_high)
		reg &= ~PMC_CNTRL_SYSCLK_POLARITY;
	else
		reg |= PMC_CNTRL_SYSCLK_POLARITY;
	WR4(sc, PMC_CNTRL, reg);

	/* Enable sysclk request. */
	reg = RD4(sc, PMC_CNTRL);
	reg |= PMC_CNTRL_SYSCLK_OE;
	WR4(sc, PMC_CNTRL, reg);

	/*
	 * Remove HDMI from deep power down mode.
	 * XXX mote this to HDMI driver
	 */
	reg = RD4(sc, PMC_IO_DPD_STATUS);
	reg &= ~ PMC_IO_DPD_STATUS_HDMI;
	WR4(sc, PMC_IO_DPD_STATUS, reg);

	reg = RD4(sc, PMC_IO_DPD2_STATUS);
	reg &= ~ PMC_IO_DPD2_STATUS_HV;
	WR4(sc, PMC_IO_DPD2_STATUS, reg);

	if (pmc_sc != NULL)
		panic("tegra124_pmc: double driver attach");
	pmc_sc = sc;
	return (0);
}