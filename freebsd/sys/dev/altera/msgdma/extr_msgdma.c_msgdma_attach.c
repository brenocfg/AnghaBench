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
struct msgdma_softc {int /*<<< orphan*/  ih; int /*<<< orphan*/ * res; void* bsh_d; void* bst_d; void* bsh; void* bst; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL_GIEM ; 
 int /*<<< orphan*/  DMA_CONTROL ; 
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int /*<<< orphan*/  OF_device_register_xref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OF_xref_from_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE4 (struct msgdma_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct msgdma_softc*,int /*<<< orphan*/ *) ; 
 struct msgdma_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msgdma_intr ; 
 scalar_t__ msgdma_reset (struct msgdma_softc*) ; 
 int /*<<< orphan*/  msgdma_spec ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 void* rman_get_bushandle (int /*<<< orphan*/ ) ; 
 void* rman_get_bustag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
msgdma_attach(device_t dev)
{
	struct msgdma_softc *sc;
	phandle_t xref, node;
	int err;

	sc = device_get_softc(dev);
	sc->dev = dev;

	if (bus_alloc_resources(dev, msgdma_spec, sc->res)) {
		device_printf(dev, "could not allocate resources for device\n");
		return (ENXIO);
	}

	/* CSR memory interface */
	sc->bst = rman_get_bustag(sc->res[0]);
	sc->bsh = rman_get_bushandle(sc->res[0]);

	/* Descriptor memory interface */
	sc->bst_d = rman_get_bustag(sc->res[1]);
	sc->bsh_d = rman_get_bushandle(sc->res[1]);

	/* Setup interrupt handler */
	err = bus_setup_intr(dev, sc->res[2], INTR_TYPE_MISC | INTR_MPSAFE,
	    NULL, msgdma_intr, sc, &sc->ih);
	if (err) {
		device_printf(dev, "Unable to alloc interrupt resource.\n");
		return (ENXIO);
	}

	node = ofw_bus_get_node(dev);
	xref = OF_xref_from_node(node);
	OF_device_register_xref(xref, dev);

	if (msgdma_reset(sc) != 0)
		return (-1);

	WRITE4(sc, DMA_CONTROL, CONTROL_GIEM);

	return (0);
}