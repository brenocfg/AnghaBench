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
struct ahci_controller {int numirqs; int /*<<< orphan*/ * r_mem; scalar_t__ r_rid; int /*<<< orphan*/  quirks; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AHCI_Q_2CH ; 
 int /*<<< orphan*/  AHCI_Q_MRVL_SR_DEL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int ahci_attach (int /*<<< orphan*/ ) ; 
 int ahci_ctlr_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahci_mv_regret_config (struct ahci_controller*) ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 struct ahci_controller* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ofw_bus_is_compatible (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
ahci_mv_fdt_attach(device_t dev)
{
	struct ahci_controller *ctlr;
	int rc;

	ctlr = device_get_softc(dev);
	ctlr->dev = dev;
	ctlr->r_rid = 0;
	ctlr->quirks = AHCI_Q_2CH;
	ctlr->numirqs = 1;

	if (ofw_bus_is_compatible(dev, "marvell,armada-380-ahci"))
		ctlr->quirks |= AHCI_Q_MRVL_SR_DEL;

	/* Allocate memory for controller */
	ctlr->r_mem = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
	    &ctlr->r_rid, RF_ACTIVE | RF_SHAREABLE);
	if (ctlr->r_mem == NULL) {
		device_printf(dev, "Failed to alloc memory for controller\n");
		return (ENOMEM);
	}

	/* Reset controller */
	rc = ahci_ctlr_reset(dev);
	if (rc != 0) {
		device_printf(dev, "Failed to reset controller\n");
		bus_release_resource(dev, SYS_RES_MEMORY, ctlr->r_rid, ctlr->r_mem);
		return (ENXIO);
	}

	ahci_mv_regret_config(ctlr);

	rc = ahci_attach(dev);
	if (rc != 0) {
		device_printf(dev, "Failed to initialize AHCI, with error %d\n", rc);
		return (ENXIO);
	}

	return (0);
}