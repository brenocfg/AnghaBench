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
struct ahci_controller {int r_rid; int numirqs; int /*<<< orphan*/ * r_mem; scalar_t__ ccc; scalar_t__ msi; } ;
struct tegra_ahci_sc {int /*<<< orphan*/ * sata_mem; int /*<<< orphan*/  dev; struct ahci_controller ctlr; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int ahci_attach (int /*<<< orphan*/ ) ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 struct tegra_ahci_sc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int enable_fdt_resources (struct tegra_ahci_sc*) ; 
 int get_fdt_resources (struct tegra_ahci_sc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int tegra_ahci_ctlr_reset (int /*<<< orphan*/ ) ; 
 int tegra_ahci_ctrl_init (struct tegra_ahci_sc*) ; 

__attribute__((used)) static int
tegra_ahci_attach(device_t dev)
{
	struct tegra_ahci_sc *sc;
	struct ahci_controller *ctlr;
	phandle_t node;
	int rv, rid;

	sc = device_get_softc(dev);
	sc->dev = dev;
	ctlr = &sc->ctlr;
	node = ofw_bus_get_node(dev);

	ctlr->r_rid = 0;
	ctlr->r_mem = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
	    &ctlr->r_rid, RF_ACTIVE);
	if (ctlr->r_mem == NULL)
		return (ENXIO);

	rid = 1;
	sc->sata_mem = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
	    &rid, RF_ACTIVE);
	if (sc->sata_mem == NULL) {
		rv = ENXIO;
		goto fail;
	}
	rv = get_fdt_resources(sc, node);
	if (rv != 0) {
		device_printf(sc->dev, "Failed to allocate FDT resource(s)\n");
		goto fail;
	}

	rv = enable_fdt_resources(sc);
	if (rv != 0) {
		device_printf(sc->dev, "Failed to enable FDT resource(s)\n");
		goto fail;
	}
	rv = tegra_ahci_ctrl_init(sc);
	if (rv != 0) {
		device_printf(sc->dev, "Failed to initialize controller)\n");
		goto fail;
	}

	/* Setup controller defaults. */
	ctlr->msi = 0;
	ctlr->numirqs = 1;
	ctlr->ccc = 0;

	/* Reset controller. */
	rv = tegra_ahci_ctlr_reset(dev);
	if (rv != 0)
		goto fail;
	rv = ahci_attach(dev);
	return (rv);

fail:
	/* XXX FDT  stuff */
	if (sc->sata_mem != NULL)
		bus_release_resource(dev, SYS_RES_MEMORY, 1, sc->sata_mem);
	if (ctlr->r_mem != NULL)
		bus_release_resource(dev, SYS_RES_MEMORY, ctlr->r_rid,
		    ctlr->r_mem);
	return (rv);
}