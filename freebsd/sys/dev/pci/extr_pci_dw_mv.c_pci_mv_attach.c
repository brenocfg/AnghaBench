#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * dbi_res; } ;
struct pci_mv_softc {int /*<<< orphan*/  intr_cookie; int /*<<< orphan*/ * irq_res; int /*<<< orphan*/  dev; int /*<<< orphan*/  clk_reg; int /*<<< orphan*/  clk_core; TYPE_1__ dw_sc; int /*<<< orphan*/  node; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pci_mv_softc*,int /*<<< orphan*/ *) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int clk_get_by_ofw_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 struct pci_mv_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int pci_dw_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_mv_init (struct pci_mv_softc*) ; 
 int /*<<< orphan*/  pci_mv_intr ; 
 int pci_mv_phy_init (struct pci_mv_softc*) ; 

__attribute__((used)) static int
pci_mv_attach(device_t dev)
{
	struct pci_mv_softc *sc;
	phandle_t node;
	int rv;
	int rid;

	sc = device_get_softc(dev);
	node = ofw_bus_get_node(dev);
	sc->dev = dev;
	sc->node = node;
	
	rid = 0;
	sc->dw_sc.dbi_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (sc->dw_sc.dbi_res == NULL) {
		device_printf(dev, "Cannot allocate DBI memory\n");
		rv = ENXIO;
		goto out;
	}

	/* PCI interrupt */
	rid = 0;
	sc->irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
	    RF_ACTIVE | RF_SHAREABLE);
	if (sc->irq_res == NULL) {
		device_printf(dev, "Cannot allocate IRQ resources\n");
		rv = ENXIO;
		goto out;
	}

	/* Clocks */
	rv = clk_get_by_ofw_name(sc->dev, 0, "core", &sc->clk_core);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot get 'core' clock\n");
		rv = ENXIO;
		goto out;
	}

	rv = clk_get_by_ofw_name(sc->dev, 0, "reg", &sc->clk_reg);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot get 'reg' clock\n");
		rv = ENXIO;
		goto out;
	}


	rv = clk_enable(sc->clk_core);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot enable 'core' clock\n");
		rv = ENXIO;
		goto out;
	}

	rv = clk_enable(sc->clk_reg);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot enable 'reg' clock\n");
		rv = ENXIO;
		goto out;
	}

	rv = pci_mv_phy_init(sc);
	if (rv)
		goto out;

	rv = pci_dw_init(dev);
	if (rv != 0)
		goto out;

	pci_mv_init(sc);

	/* Setup interrupt  */
	if (bus_setup_intr(dev, sc->irq_res, INTR_TYPE_MISC | INTR_MPSAFE,
		    pci_mv_intr, NULL, sc, &sc->intr_cookie)) {
		device_printf(dev, "cannot setup interrupt handler\n");
		rv = ENXIO;
		goto out;
	}

	return (bus_generic_attach(dev));
out:
	/* XXX Cleanup */
	return (rv);
}