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
struct timespec {int /*<<< orphan*/  tv_nsec; scalar_t__ tv_sec; } ;
struct sbbc_softc {int /*<<< orphan*/ * sc_res; } ;
typedef  int phandle_t ;
typedef  int /*<<< orphan*/  node ;
typedef  int /*<<< orphan*/ * device_t ;
typedef  int /*<<< orphan*/  bus_space_tag_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;

/* Variables and functions */
 int ENXIO ; 
 int OF_finddevice (char*) ; 
 int OF_getprop (int,char*,int*,int) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int SBBC_PCI_BAR ; 
 int /*<<< orphan*/  SBBC_SRAM_READ_4 (scalar_t__) ; 
 int /*<<< orphan*/  SBBC_TOD_MAGIC ; 
 scalar_t__ SBBC_TOD_OFF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SBBC_TOD_VERSION ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int bus_generic_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clock_register (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct sbbc_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*,...) ; 
 int ofw_bus_get_node (int /*<<< orphan*/ *) ; 
 scalar_t__ pci_get_intpin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_set_intpin (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 
 scalar_t__ sbbc_console ; 
 int sbbc_parse_toc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbbc_tod_gettime (int /*<<< orphan*/ *,struct timespec*) ; 
 scalar_t__ sbbc_toddata ; 
 int /*<<< orphan*/  tod_magic ; 
 int /*<<< orphan*/  tod_version ; 

__attribute__((used)) static int
sbbc_pci_attach(device_t dev)
{
	struct sbbc_softc *sc;
	struct timespec ts;
	device_t child;
	bus_space_tag_t bst;
	bus_space_handle_t bsh;
	phandle_t node;
	int error, rid;
	uint32_t val;

	/* Nothing to do if we're not the chosen one. */
	if ((node = OF_finddevice("/chosen")) == -1) {
		device_printf(dev, "failed to find /chosen\n");
		return (ENXIO);
	}
	if (OF_getprop(node, "iosram", &node, sizeof(node)) == -1) {
		device_printf(dev, "failed to get iosram\n");
		return (ENXIO);
	}
	if (node != ofw_bus_get_node(dev))
		return (0);

	sc = device_get_softc(dev);
	rid = SBBC_PCI_BAR;
	sc->sc_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (sc->sc_res == NULL) {
		device_printf(dev, "failed to allocate resources\n");
		return (ENXIO);
	}
	bst = rman_get_bustag(sc->sc_res);
	bsh = rman_get_bushandle(sc->sc_res);
	if (sbbc_console != 0) {
		/* Once again the interrupt pin isn't set. */
		if (pci_get_intpin(dev) == 0)
			pci_set_intpin(dev, 1);
		child = device_add_child(dev, NULL, -1);
		if (child == NULL)
			device_printf(dev, "failed to add UART device\n");
		error = bus_generic_attach(dev);
		if (error != 0)
			device_printf(dev, "failed to attach UART device\n");
	} else {
		error = sbbc_parse_toc(bst, bsh);
		if (error != 0) {
			device_printf(dev, "failed to parse TOC\n");
			if (sbbc_console != 0) {
				bus_release_resource(dev, SYS_RES_MEMORY, rid,
				    sc->sc_res);
				return (error);
			}
		}
	}
	if (sbbc_toddata != 0) {
		if ((val = SBBC_SRAM_READ_4(sbbc_toddata +
		    SBBC_TOD_OFF(tod_magic))) != SBBC_TOD_MAGIC)
			device_printf(dev, "invalid TOD magic %#x\n", val);
		else if ((val = SBBC_SRAM_READ_4(sbbc_toddata +
		    SBBC_TOD_OFF(tod_version))) < SBBC_TOD_VERSION)
			device_printf(dev, "invalid TOD version %#x\n", val);
		else {
			clock_register(dev, 1000000); /* 1 sec. resolution */
			if (bootverbose) {
				sbbc_tod_gettime(dev, &ts);
				device_printf(dev,
				    "current time: %ld.%09ld\n",
				    (long)ts.tv_sec, ts.tv_nsec);
			}
		}
	}
	return (0);
}