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
struct edma_softc {int device_id; int /*<<< orphan*/  err_ih; int /*<<< orphan*/ * res; int /*<<< orphan*/  tc_ih; void* bsh_tcd; void* bst_tcd; void* bsh; void* bst; int /*<<< orphan*/  channel_free; int /*<<< orphan*/  channel_configure; int /*<<< orphan*/  dma_request; int /*<<< orphan*/  dma_setup; int /*<<< orphan*/  dma_stop; int /*<<< orphan*/  dev; } ;
typedef  int phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_BIO ; 
 int /*<<< orphan*/  OF_getencprop (int,char*,int*,int) ; 
 int OF_getproplen (int,char*) ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct edma_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  channel_configure ; 
 int /*<<< orphan*/  channel_free ; 
 struct edma_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_request ; 
 int /*<<< orphan*/  dma_setup ; 
 int /*<<< orphan*/  dma_stop ; 
 int /*<<< orphan*/  edma_err_intr ; 
 int /*<<< orphan*/  edma_spec ; 
 int /*<<< orphan*/  edma_transfer_complete_intr ; 
 int ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 void* rman_get_bushandle (int /*<<< orphan*/ ) ; 
 void* rman_get_bustag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
edma_attach(device_t dev)
{
	struct edma_softc *sc;
	phandle_t node;
	int dts_value;
	int len;

	sc = device_get_softc(dev);
	sc->dev = dev;

	if ((node = ofw_bus_get_node(sc->dev)) == -1)
		return (ENXIO);

	if ((len = OF_getproplen(node, "device-id")) <= 0)
		return (ENXIO);

	OF_getencprop(node, "device-id", &dts_value, len);
	sc->device_id = dts_value;

	sc->dma_stop = dma_stop;
	sc->dma_setup = dma_setup;
	sc->dma_request = dma_request;
	sc->channel_configure = channel_configure;
	sc->channel_free = channel_free;

	if (bus_alloc_resources(dev, edma_spec, sc->res)) {
		device_printf(dev, "could not allocate resources\n");
		return (ENXIO);
	}

	/* Memory interface */
	sc->bst = rman_get_bustag(sc->res[0]);
	sc->bsh = rman_get_bushandle(sc->res[0]);
	sc->bst_tcd = rman_get_bustag(sc->res[1]);
	sc->bsh_tcd = rman_get_bushandle(sc->res[1]);

	/* Setup interrupt handlers */
	if (bus_setup_intr(dev, sc->res[2], INTR_TYPE_BIO | INTR_MPSAFE,
		NULL, edma_transfer_complete_intr, sc, &sc->tc_ih)) {
		device_printf(dev, "Unable to alloc DMA intr resource.\n");
		return (ENXIO);
	}

	if (bus_setup_intr(dev, sc->res[3], INTR_TYPE_BIO | INTR_MPSAFE,
		NULL, edma_err_intr, sc, &sc->err_ih)) {
		device_printf(dev, "Unable to alloc DMA Err intr resource.\n");
		return (ENXIO);
	}

	return (0);
}