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
typedef  int /*<<< orphan*/  uint32_t ;
struct lsi64854_softc {int sc_burst; int /*<<< orphan*/ * sc_res; int /*<<< orphan*/ * sc_dev; int /*<<< orphan*/  sc_parent_dmat; int /*<<< orphan*/  sc_channel; } ;
struct dma_softc {int /*<<< orphan*/  sc_slot; int /*<<< orphan*/  sc_ign; struct lsi64854_softc sc_lsi64854; } ;
struct TYPE_2__ {int /*<<< orphan*/  obd_name; } ;
struct dma_devinfo {TYPE_1__ ddi_obdinfo; } ;
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXSIZE ; 
 int /*<<< orphan*/  BUS_SPACE_UNRESTRICTED ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ENXIO ; 
 int /*<<< orphan*/  E_TP_AUI ; 
 int /*<<< orphan*/  L64854_CHANNEL_ENET ; 
 int /*<<< orphan*/  L64854_CHANNEL_SCSI ; 
 int /*<<< orphan*/  L64854_GCSR (struct lsi64854_softc*) ; 
 int /*<<< orphan*/  L64854_SCSR (struct lsi64854_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ OF_child (scalar_t__) ; 
 int OF_getprop_alloc (scalar_t__,char*,void**) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 int /*<<< orphan*/  OF_prop_free (char*) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int SBUS_BURST_16 ; 
 int SBUS_BURST_32 ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bus_generic_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct dma_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,struct dma_devinfo*) ; 
 int /*<<< orphan*/  dma_destroy_dinfo (struct dma_devinfo*) ; 
 struct dma_devinfo* dma_setup_dinfo (int /*<<< orphan*/ *,struct dma_softc*,scalar_t__) ; 
 char* ofw_bus_get_name (int /*<<< orphan*/ *) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_rid (int /*<<< orphan*/ *) ; 
 int sbus_get_burstsz (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sbus_get_ign (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sbus_get_slot (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
dma_attach(device_t dev)
{
	struct dma_softc *dsc;
	struct lsi64854_softc *lsc;
	struct dma_devinfo *ddi;
	device_t cdev;
	const char *name;
	char *cabletype;
	uint32_t csr;
	phandle_t child, node;
	int error, i;

	dsc = device_get_softc(dev);
	lsc = &dsc->sc_lsi64854;

	name = ofw_bus_get_name(dev);
	node = ofw_bus_get_node(dev);
	dsc->sc_ign = sbus_get_ign(dev);
	dsc->sc_slot = sbus_get_slot(dev);

	i = 0;
	lsc->sc_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &i,
	    RF_ACTIVE);
	if (lsc->sc_res == NULL) {
		device_printf(dev, "cannot allocate resources\n");
		return (ENXIO);
	}

	if (strcmp(name, "espdma") == 0 || strcmp(name, "dma") == 0)
		lsc->sc_channel = L64854_CHANNEL_SCSI;
	else if (strcmp(name, "ledma") == 0) {
		/*
		 * Check to see which cable type is currently active and
		 * set the appropriate bit in the ledma csr so that it
		 * gets used. If we didn't netboot, the PROM won't have
		 * the "cable-selection" property; default to TP and then
		 * the user can change it via a "media" option to ifconfig.
		 */
		csr = L64854_GCSR(lsc);
		if ((OF_getprop_alloc(node, "cable-selection",
		    (void **)&cabletype)) == -1) {
			/* assume TP if nothing there */
			csr |= E_TP_AUI;
		} else {
			if (strcmp(cabletype, "aui") == 0)
				csr &= ~E_TP_AUI;
			else
				csr |= E_TP_AUI;
			OF_prop_free(cabletype);
		}
		L64854_SCSR(lsc, csr);
		DELAY(20000);	/* manual says we need a 20ms delay */
		lsc->sc_channel = L64854_CHANNEL_ENET;
	} else {
		device_printf(dev, "unsupported DMA channel\n");
		error = ENXIO;
		goto fail_lres;
	}

	error = bus_dma_tag_create(
	    bus_get_dma_tag(dev),	/* parent */
	    1, 0,			/* alignment, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    BUS_SPACE_MAXSIZE,		/* maxsize */
	    BUS_SPACE_UNRESTRICTED,	/* nsegments */
	    BUS_SPACE_MAXSIZE,		/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* no locking */
	    &lsc->sc_parent_dmat);
	if (error != 0) {
		device_printf(dev, "cannot allocate parent DMA tag\n");
		goto fail_lres;
	}

	i = sbus_get_burstsz(dev);
	lsc->sc_burst = (i & SBUS_BURST_32) ? 32 :
	    (i & SBUS_BURST_16) ? 16 : 0;
	lsc->sc_dev = dev;

	/* Attach children. */
	i = 0;
	for (child = OF_child(node); child != 0; child = OF_peer(child)) {
		if ((ddi = dma_setup_dinfo(dev, dsc, child)) == NULL)
			continue;
		if (i != 0) {
			device_printf(dev,
			    "<%s>: only one child per DMA channel supported\n",
			    ddi->ddi_obdinfo.obd_name);
			dma_destroy_dinfo(ddi);
			continue;
		}
		if ((cdev = device_add_child(dev, NULL, -1)) == NULL) {
			device_printf(dev, "<%s>: device_add_child failed\n",
			    ddi->ddi_obdinfo.obd_name);
			dma_destroy_dinfo(ddi);
			continue;
		}
		device_set_ivars(cdev, ddi);
		i++;
	}
	return (bus_generic_attach(dev));

 fail_lres:
	bus_release_resource(dev, SYS_RES_MEMORY, rman_get_rid(lsc->sc_res),
	    lsc->sc_res);
	return (error);
}