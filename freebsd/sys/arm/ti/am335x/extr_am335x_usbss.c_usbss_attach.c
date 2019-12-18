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
struct usbss_softc {int /*<<< orphan*/ * sc_mem_res; int /*<<< orphan*/  sc_mem_rid; } ;
typedef  int phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int ENXIO ; 
 int /*<<< orphan*/  MUSB0_CLK ; 
 int OF_child (int) ; 
 int OF_peer (int) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int USBSS_READ4 (struct usbss_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBSS_REVREG ; 
 int /*<<< orphan*/  USBSS_SYSCONFIG ; 
 int USBSS_SYSCONFIG_SRESET ; 
 int /*<<< orphan*/  USBSS_WRITE4 (struct usbss_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_probe (int /*<<< orphan*/ ) ; 
 struct usbss_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simplebus_add_device (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simplebus_init (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ti_prcm_clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbss_detach (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
usbss_attach(device_t dev)
{
	struct usbss_softc *sc = device_get_softc(dev);
	int i;
	uint32_t rev;
	phandle_t node;

	/* Request the memory resources */
	sc->sc_mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
	    &sc->sc_mem_rid, RF_ACTIVE);
	if (sc->sc_mem_res == NULL) {
		device_printf(dev,
		    "Error: could not allocate mem resources\n");
		return (ENXIO);
	}

	/* Enable device clocks. */
	ti_prcm_clk_enable(MUSB0_CLK);

	/*
	 * Reset USBSS, USB0 and USB1.
	 * The registers of USB subsystem must not be accessed while the
	 * reset pulse is active (200ns).
	 */
	USBSS_WRITE4(sc, USBSS_SYSCONFIG, USBSS_SYSCONFIG_SRESET);
	DELAY(100);
	i = 10;
	while (USBSS_READ4(sc, USBSS_SYSCONFIG) & USBSS_SYSCONFIG_SRESET) {
		DELAY(100);
		if (i-- == 0) {
			device_printf(dev, "reset timeout.\n");
			return (ENXIO);
		}
	}

	/* Read the module revision. */
	rev = USBSS_READ4(sc, USBSS_REVREG);
	device_printf(dev, "TI AM335X USBSS v%d.%d.%d\n",
	    (rev >> 8) & 7, (rev >> 6) & 3, rev & 63);

	node = ofw_bus_get_node(dev);

	if (node == -1) {
		usbss_detach(dev);
		return (ENXIO);
	}

	simplebus_init(dev, node);

	/*
	 * Allow devices to identify.
	 */
	bus_generic_probe(dev);

	/*
	 * Now walk the OFW tree and attach top-level devices.
	 */
	for (node = OF_child(node); node > 0; node = OF_peer(node))
		simplebus_add_device(dev, node, 0, NULL, -1, NULL);

	return (bus_generic_attach(dev));
}