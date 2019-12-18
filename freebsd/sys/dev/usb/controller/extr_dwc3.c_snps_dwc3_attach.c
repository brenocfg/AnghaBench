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
struct snps_dwc3_softc {int /*<<< orphan*/  usb3_phy; int /*<<< orphan*/  node; int /*<<< orphan*/  usb2_phy; int /*<<< orphan*/ * mem_res; int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_GSNPSID ; 
 int /*<<< orphan*/  DWC3_READ (struct snps_dwc3_softc*,int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 struct snps_dwc3_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  phy_get_by_ofw_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snps_dwc3_attach_xhci (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snps_dwc3_configure_host (struct snps_dwc3_softc*) ; 
 int /*<<< orphan*/  snps_dwc3_configure_phy (struct snps_dwc3_softc*) ; 
 int /*<<< orphan*/  snps_dwc3_do_quirks (struct snps_dwc3_softc*) ; 
 int /*<<< orphan*/  snps_dwc3_reset (struct snps_dwc3_softc*) ; 
 int /*<<< orphan*/  snsp_dwc3_dump_regs (struct snps_dwc3_softc*) ; 

__attribute__((used)) static int
snps_dwc3_attach(device_t dev)
{
	struct snps_dwc3_softc *sc;
	int rid = 0;

	sc = device_get_softc(dev);
	sc->dev = dev;

	sc->mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (sc->mem_res == NULL) {
		device_printf(dev, "Failed to map memory\n");
		return (ENXIO);
	}
	sc->bst = rman_get_bustag(sc->mem_res);
	sc->bsh = rman_get_bushandle(sc->mem_res);

	if (bootverbose)
		device_printf(dev, "snps id: %x\n", DWC3_READ(sc, DWC3_GSNPSID));

	/* Get the phys */
	phy_get_by_ofw_name(dev, sc->node, "usb2-phy", &sc->usb2_phy);
	phy_get_by_ofw_name(dev, sc->node, "usb3-phy", &sc->usb3_phy);

	snps_dwc3_reset(sc);
	snps_dwc3_configure_host(sc);
	snps_dwc3_configure_phy(sc);
	snps_dwc3_do_quirks(sc);
#if 0
	snsp_dwc3_dump_regs(sc);
#endif
	snps_dwc3_attach_xhci(dev);

	return (0);
}