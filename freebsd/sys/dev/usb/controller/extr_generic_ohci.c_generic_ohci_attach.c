#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct phy_list {int /*<<< orphan*/  phy; int /*<<< orphan*/  rst; int /*<<< orphan*/  clk; } ;
struct hwrst_list {int /*<<< orphan*/  phy; int /*<<< orphan*/  rst; int /*<<< orphan*/  clk; } ;
struct TYPE_4__ {int dma_bits; scalar_t__ bdev; int /*<<< orphan*/  devices_max; int /*<<< orphan*/  devices; int /*<<< orphan*/  parent; } ;
struct TYPE_5__ {scalar_t__ sc_io_res; scalar_t__ sc_irq_res; TYPE_1__ sc_bus; int /*<<< orphan*/ * sc_intr_hdl; int /*<<< orphan*/  sc_vendor; int /*<<< orphan*/  sc_io_size; int /*<<< orphan*/  sc_io_hdl; int /*<<< orphan*/  sc_io_tag; int /*<<< orphan*/  sc_devices; } ;
struct generic_ohci_softc {TYPE_2__ ohci_sc; int /*<<< orphan*/  phy_list; int /*<<< orphan*/  rst_list; int /*<<< orphan*/  clk_list; } ;
struct clk_list {int /*<<< orphan*/  phy; int /*<<< orphan*/  rst; int /*<<< orphan*/  clk; } ;
typedef  int /*<<< orphan*/  phy_t ;
typedef  int /*<<< orphan*/  hwreset_t ;
typedef  int /*<<< orphan*/  driver_intr_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  clk_t ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 scalar_t__ GENERIC_USB_INIT (int /*<<< orphan*/ ) ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_BIO ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  OHCI_MAX_DEVICES ; 
 int /*<<< orphan*/  PHY_USB_MODE_HOST ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct phy_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_GET_DMA_TAG (int /*<<< orphan*/ ) ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct generic_ohci_softc*,int /*<<< orphan*/ **) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 scalar_t__ clk_get_by_ofw_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_get_name (int /*<<< orphan*/ ) ; 
 scalar_t__ device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 struct generic_ohci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int device_probe_and_attach (scalar_t__) ; 
 int /*<<< orphan*/  device_set_ivars (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  generic_ohci_detach (int /*<<< orphan*/ ) ; 
 int hwreset_deassert (int /*<<< orphan*/ ) ; 
 scalar_t__ hwreset_get_by_ofw_idx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 struct phy_list* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  next ; 
 int ohci_init (TYPE_2__*) ; 
 scalar_t__ ohci_interrupt ; 
 int /*<<< orphan*/  ohci_iterate_hw_softc ; 
 int phy_enable (int /*<<< orphan*/ ) ; 
 scalar_t__ phy_get_by_ofw_idx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int phy_usb_set_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (scalar_t__) ; 
 int /*<<< orphan*/  rman_get_bustag (scalar_t__) ; 
 int /*<<< orphan*/  rman_get_size (scalar_t__) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ usb_bus_mem_alloc_all (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
generic_ohci_attach(device_t dev)
{
	struct generic_ohci_softc *sc = device_get_softc(dev);
	int err, rid;
#ifdef EXT_RESOURCES
	int off;
	struct clk_list *clkp;
	struct phy_list *phyp;
	struct hwrst_list *rstp;
	clk_t clk;
	phy_t phy;
	hwreset_t rst;
#endif

	sc->ohci_sc.sc_bus.parent = dev;
	sc->ohci_sc.sc_bus.devices = sc->ohci_sc.sc_devices;
	sc->ohci_sc.sc_bus.devices_max = OHCI_MAX_DEVICES;
	sc->ohci_sc.sc_bus.dma_bits = 32;

	/* get all DMA memory */
	if (usb_bus_mem_alloc_all(&sc->ohci_sc.sc_bus,
	    USB_GET_DMA_TAG(dev), &ohci_iterate_hw_softc)) {
		return (ENOMEM);
	}

	rid = 0;
	sc->ohci_sc.sc_io_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
	    &rid, RF_ACTIVE);
	if (sc->ohci_sc.sc_io_res == 0) {
		err = ENOMEM;
		goto error;
	}

	sc->ohci_sc.sc_io_tag = rman_get_bustag(sc->ohci_sc.sc_io_res);
	sc->ohci_sc.sc_io_hdl = rman_get_bushandle(sc->ohci_sc.sc_io_res);
	sc->ohci_sc.sc_io_size = rman_get_size(sc->ohci_sc.sc_io_res);

	rid = 0;
	sc->ohci_sc.sc_irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
	    RF_ACTIVE);
	if (sc->ohci_sc.sc_irq_res == 0) {
		err = ENXIO;
		goto error;
	}
	sc->ohci_sc.sc_bus.bdev = device_add_child(dev, "usbus", -1);
	if (sc->ohci_sc.sc_bus.bdev == 0) {
		err = ENXIO;
		goto error;
	}
	device_set_ivars(sc->ohci_sc.sc_bus.bdev, &sc->ohci_sc.sc_bus);

	strlcpy(sc->ohci_sc.sc_vendor, "Generic",
	    sizeof(sc->ohci_sc.sc_vendor));

	err = bus_setup_intr(dev, sc->ohci_sc.sc_irq_res,
	    INTR_TYPE_BIO | INTR_MPSAFE, NULL,
	    (driver_intr_t *)ohci_interrupt, sc, &sc->ohci_sc.sc_intr_hdl);
	if (err) {
		sc->ohci_sc.sc_intr_hdl = NULL;
		goto error;
	}

#ifdef EXT_RESOURCES
	TAILQ_INIT(&sc->clk_list);
	/* Enable clock */
	for (off = 0; clk_get_by_ofw_index(dev, 0, off, &clk) == 0; off++) {
		err = clk_enable(clk);
		if (err != 0) {
			device_printf(dev, "Could not enable clock %s\n",
			    clk_get_name(clk));
			goto error;
		}
		clkp = malloc(sizeof(*clkp), M_DEVBUF, M_WAITOK | M_ZERO);
		clkp->clk = clk;
		TAILQ_INSERT_TAIL(&sc->clk_list, clkp, next);
	}

	/* De-assert reset */
	TAILQ_INIT(&sc->rst_list);
	for (off = 0; hwreset_get_by_ofw_idx(dev, 0, off, &rst) == 0; off++) {
		err = hwreset_deassert(rst);
		if (err != 0) {
			device_printf(dev, "Could not de-assert reset\n");
			goto error;
		}
		rstp = malloc(sizeof(*rstp), M_DEVBUF, M_WAITOK | M_ZERO);
		rstp->rst = rst;
		TAILQ_INSERT_TAIL(&sc->rst_list, rstp, next);
	}

	/* Enable phy */
	TAILQ_INIT(&sc->phy_list);
	for (off = 0; phy_get_by_ofw_idx(dev, 0, off, &phy) == 0; off++) {
		err = phy_usb_set_mode(phy, PHY_USB_MODE_HOST);
		if (err != 0) {
			device_printf(dev, "Could not set phy to host mode\n");
			goto error;
		}
		err = phy_enable(phy);
		if (err != 0) {
			device_printf(dev, "Could not enable phy\n");
			goto error;
		}
		phyp = malloc(sizeof(*phyp), M_DEVBUF, M_WAITOK | M_ZERO);
		phyp->phy = phy;
		TAILQ_INSERT_TAIL(&sc->phy_list, phyp, next);
	}
#endif

	if (GENERIC_USB_INIT(dev) != 0) {
		err = ENXIO;
		goto error;
	}

	err = ohci_init(&sc->ohci_sc);
	if (err == 0)
		err = device_probe_and_attach(sc->ohci_sc.sc_bus.bdev);
	if (err)
		goto error;

	return (0);
error:
	generic_ohci_detach(dev);
	return (err);
}