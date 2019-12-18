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
typedef  int /*<<< orphan*/  vmem_t ;
struct xae_softc {int /*<<< orphan*/ * xchan_rx; int /*<<< orphan*/ * xchan_tx; int /*<<< orphan*/  dev; int /*<<< orphan*/  ih_rx; int /*<<< orphan*/ * xdma_rx; int /*<<< orphan*/  ih_tx; int /*<<< orphan*/ * xdma_tx; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int ENXIO ; 
 int /*<<< orphan*/  MCLBYTES ; 
 int /*<<< orphan*/  RX_QUEUE_SIZE ; 
 int /*<<< orphan*/  TX_QUEUE_SIZE ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xae_xdma_rx_intr ; 
 int /*<<< orphan*/  xae_xdma_tx_intr ; 
 int /*<<< orphan*/  xchan_set_memory (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* xdma_channel_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdma_get_memory (int /*<<< orphan*/ ) ; 
 void* xdma_ofw_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xdma_prep_sg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xdma_setup_intr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct xae_softc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
setup_xdma(struct xae_softc *sc)
{
	device_t dev;
	vmem_t *vmem;
	int error;

	dev = sc->dev;

	/* Get xDMA controller */   
	sc->xdma_tx = xdma_ofw_get(sc->dev, "tx");
	if (sc->xdma_tx == NULL) {
		device_printf(dev, "Could not find DMA controller.\n");
		return (ENXIO);
	}

	sc->xdma_rx = xdma_ofw_get(sc->dev, "rx");
	if (sc->xdma_rx == NULL) {
		device_printf(dev, "Could not find DMA controller.\n");
		return (ENXIO);
	}

	/* Alloc xDMA TX virtual channel. */
	sc->xchan_tx = xdma_channel_alloc(sc->xdma_tx, 0);
	if (sc->xchan_tx == NULL) {
		device_printf(dev, "Can't alloc virtual DMA TX channel.\n");
		return (ENXIO);
	}

	/* Setup interrupt handler. */
	error = xdma_setup_intr(sc->xchan_tx,
	    xae_xdma_tx_intr, sc, &sc->ih_tx);
	if (error) {
		device_printf(sc->dev,
		    "Can't setup xDMA TX interrupt handler.\n");
		return (ENXIO);
	}

	/* Alloc xDMA RX virtual channel. */
	sc->xchan_rx = xdma_channel_alloc(sc->xdma_rx, 0);
	if (sc->xchan_rx == NULL) {
		device_printf(dev, "Can't alloc virtual DMA RX channel.\n");
		return (ENXIO);
	}

	/* Setup interrupt handler. */
	error = xdma_setup_intr(sc->xchan_rx,
	    xae_xdma_rx_intr, sc, &sc->ih_rx);
	if (error) {
		device_printf(sc->dev,
		    "Can't setup xDMA RX interrupt handler.\n");
		return (ENXIO);
	}

	/* Setup bounce buffer */
	vmem = xdma_get_memory(dev);
	if (vmem) {
		xchan_set_memory(sc->xchan_tx, vmem);
		xchan_set_memory(sc->xchan_rx, vmem);
	}

	xdma_prep_sg(sc->xchan_tx,
	    TX_QUEUE_SIZE,	/* xchan requests queue size */
	    MCLBYTES,	/* maxsegsize */
	    8,		/* maxnsegs */
	    16,		/* alignment */
	    0,		/* boundary */
	    BUS_SPACE_MAXADDR_32BIT,
	    BUS_SPACE_MAXADDR);

	xdma_prep_sg(sc->xchan_rx,
	    RX_QUEUE_SIZE,	/* xchan requests queue size */
	    MCLBYTES,	/* maxsegsize */
	    1,		/* maxnsegs */
	    16,		/* alignment */
	    0,		/* boundary */
	    BUS_SPACE_MAXADDR_32BIT,
	    BUS_SPACE_MAXADDR);

	return (0);
}