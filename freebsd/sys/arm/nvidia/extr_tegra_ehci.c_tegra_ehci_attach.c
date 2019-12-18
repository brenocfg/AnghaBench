#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_7__ {int dma_bits; int /*<<< orphan*/ * bdev; int /*<<< orphan*/  devices_max; int /*<<< orphan*/  devices; void* parent; } ;
struct TYPE_6__ {TYPE_2__ sc_bus; int /*<<< orphan*/  sc_flags; int /*<<< orphan*/  sc_vendor; int /*<<< orphan*/  sc_id_vendor; int /*<<< orphan*/  sc_intr_hdl; int /*<<< orphan*/  sc_io_hdl; int /*<<< orphan*/  sc_io_tag; int /*<<< orphan*/  sc_devices; int /*<<< orphan*/  sc_vendor_post_reset; int /*<<< orphan*/  sc_vendor_get_port_speed; } ;
struct tegra_ehci_softc {void* dev; int usb_alloc_called; int /*<<< orphan*/ * ehci_irq_res; int /*<<< orphan*/ * ehci_mem_res; int /*<<< orphan*/  phy; int /*<<< orphan*/  reset; int /*<<< orphan*/  clk; TYPE_1__ ehci_softc; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  TYPE_1__ ehci_softc_t ;
typedef  int /*<<< orphan*/  driver_intr_t ;
typedef  void* device_t ;

/* Variables and functions */
 int /*<<< orphan*/  EHCI_MAX_DEVICES ; 
 int /*<<< orphan*/  EHCI_SCFLG_DONEINIT ; 
 int /*<<< orphan*/  EHCI_SCFLG_NORESTERM ; 
 int /*<<< orphan*/  EHCI_SCFLG_TT ; 
 int ENOMEM ; 
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_BIO ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  TEGRA_EHCI_REG_OFF ; 
 int /*<<< orphan*/  TEGRA_EHCI_REG_SIZE ; 
 int /*<<< orphan*/  USB_GET_DMA_TAG (void*) ; 
 int /*<<< orphan*/  USB_VENDOR_FREESCALE ; 
 void* bus_alloc_resource_any (void*,int /*<<< orphan*/ ,int*,int) ; 
 int bus_setup_intr (void*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int bus_space_subregion (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int clk_get_by_ofw_index (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int clk_get_freq (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/ * device_add_child (void*,char*,int) ; 
 struct tegra_ehci_softc* device_get_softc (void*) ; 
 int /*<<< orphan*/  device_printf (void*,char*,...) ; 
 int device_probe_and_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  ehci_get_port_speed_hostc ; 
 int ehci_init (TYPE_1__*) ; 
 scalar_t__ ehci_interrupt ; 
 int /*<<< orphan*/  ehci_iterate_hw_softc ; 
 int hwreset_deassert (int /*<<< orphan*/ ) ; 
 int hwreset_get_by_ofw_name (void*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ofw_bus_get_node (void*) ; 
 int phy_enable (int /*<<< orphan*/ ) ; 
 int phy_get_by_ofw_property (void*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  tegra_ehci_detach (void*) ; 
 int /*<<< orphan*/  tegra_ehci_post_reset ; 
 int usb_bus_mem_alloc_all (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
tegra_ehci_attach(device_t dev)
{
	struct tegra_ehci_softc *sc;
	ehci_softc_t *esc;
	int rv, rid;
	uint64_t freq;
	phandle_t node;

	sc = device_get_softc(dev);
	sc->dev = dev;
	node = ofw_bus_get_node(dev);
	esc = &sc->ehci_softc;

	/* Allocate resources. */
	rid = 0;
	sc->ehci_mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE | RF_SHAREABLE);
	if (sc->ehci_mem_res == NULL) {
		device_printf(dev, "Cannot allocate memory resources\n");
		rv = ENXIO;
		goto out;
	}

	rid = 0;
	sc->ehci_irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
	    RF_ACTIVE);
	if (sc->ehci_irq_res == NULL) {
		device_printf(dev, "Cannot allocate IRQ resources\n");
		rv = ENXIO;
		goto out;
	}

	rv = hwreset_get_by_ofw_name(dev, 0, "usb", &sc->reset);
	if (rv != 0) {
		device_printf(dev, "Cannot get reset\n");
		rv = ENXIO;
		goto out;
	}

	rv = phy_get_by_ofw_property(sc->dev, 0, "nvidia,phy", &sc->phy);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot get 'nvidia,phy' phy\n");
		rv = ENXIO;
		goto out;
	}

	rv = clk_get_by_ofw_index(sc->dev, 0, 0, &sc->clk);
	if (rv != 0) {
		device_printf(dev, "Cannot get clock\n");
		goto out;
	}

	rv = clk_enable(sc->clk);
	if (rv != 0) {
		device_printf(dev, "Cannot enable clock\n");
		goto out;
	}

	freq = 0;
	rv = clk_get_freq(sc->clk, &freq);
	if (rv != 0) {
		device_printf(dev, "Cannot get clock frequency\n");
		goto out;
	}

	rv = hwreset_deassert(sc->reset);
	if (rv != 0) {
		device_printf(dev, "Cannot clear reset: %d\n", rv);
		rv = ENXIO;
		goto out;
	}

	rv = phy_enable(sc->phy);
	if (rv != 0) {
		device_printf(dev, "Cannot enable phy: %d\n", rv);
		goto out;
	}

	/* Fill data for EHCI driver. */
	esc->sc_vendor_get_port_speed = ehci_get_port_speed_hostc;
	esc->sc_vendor_post_reset = tegra_ehci_post_reset;
	esc->sc_io_tag = rman_get_bustag(sc->ehci_mem_res);
	esc->sc_bus.parent = dev;
	esc->sc_bus.devices = esc->sc_devices;
	esc->sc_bus.devices_max = EHCI_MAX_DEVICES;
	esc->sc_bus.dma_bits = 32;

	/* Allocate all DMA memory. */
	rv = usb_bus_mem_alloc_all(&esc->sc_bus, USB_GET_DMA_TAG(dev),
	    &ehci_iterate_hw_softc);
	sc->usb_alloc_called = 1;
	if (rv != 0) {
		device_printf(dev, "usb_bus_mem_alloc_all() failed\n");
		rv = ENOMEM;
		goto out;
	}

	/*
	 * Set handle to USB related registers subregion used by
	 * generic EHCI driver.
	 */
	rv = bus_space_subregion(esc->sc_io_tag,
	    rman_get_bushandle(sc->ehci_mem_res),
	    TEGRA_EHCI_REG_OFF, TEGRA_EHCI_REG_SIZE, &esc->sc_io_hdl);
	if (rv != 0) {
		device_printf(dev, "Could not create USB memory subregion\n");
		rv = ENXIO;
		goto out;
	}

	/* Setup interrupt handler. */
	rv = bus_setup_intr(dev, sc->ehci_irq_res, INTR_TYPE_BIO | INTR_MPSAFE,
	    NULL, (driver_intr_t *)ehci_interrupt, esc, &esc->sc_intr_hdl);
	if (rv != 0) {
		device_printf(dev, "Could not setup IRQ\n");
		goto out;
	}

	/* Add USB bus device. */
	esc->sc_bus.bdev = device_add_child(dev, "usbus", -1);
	if (esc->sc_bus.bdev == NULL) {
		device_printf(dev, "Could not add USB device\n");
		goto out;
	}
	device_set_ivars(esc->sc_bus.bdev, &esc->sc_bus);

	esc->sc_id_vendor = USB_VENDOR_FREESCALE;
	strlcpy(esc->sc_vendor, "Nvidia", sizeof(esc->sc_vendor));

	/* Set flags that affect ehci_init() behavior. */
	esc->sc_flags |= EHCI_SCFLG_TT;
	esc->sc_flags |= EHCI_SCFLG_NORESTERM;
	rv = ehci_init(esc);
	if (rv != 0) {
		device_printf(dev, "USB init failed: %d\n",
		    rv);
		goto out;
	}
	esc->sc_flags |= EHCI_SCFLG_DONEINIT;

	/* Probe the bus. */
	rv = device_probe_and_attach(esc->sc_bus.bdev);
	if (rv != 0) {
		device_printf(dev,
		    "device_probe_and_attach() failed\n");
		goto out;
	}
	return (0);

out:
	tegra_ehci_detach(dev);
	return (rv);
}