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
struct TYPE_2__ {int src_width; int dst_width; int block_len; int block_num; int /*<<< orphan*/  dst_addr; int /*<<< orphan*/  src_addr; int /*<<< orphan*/  direction; int /*<<< orphan*/  type; } ;
struct xdmatest_softc {int len; int* src; int /*<<< orphan*/ * xchan; int /*<<< orphan*/  dev; int /*<<< orphan*/  dst_phys; int /*<<< orphan*/  src_phys; TYPE_1__ req; scalar_t__* dst; int /*<<< orphan*/  dst_dma_map; int /*<<< orphan*/  dst_dma_tag; int /*<<< orphan*/  src_dma_map; int /*<<< orphan*/  src_dma_tag; int /*<<< orphan*/  ih; int /*<<< orphan*/ * xdma; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  XDMA_MEM_TO_MEM ; 
 int /*<<< orphan*/  XR_TYPE_PHYS_ADDR ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xdma_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xdma_channel_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xdma_ofw_get (int /*<<< orphan*/ ,char*) ; 
 int xdma_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int xdma_setup_intr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct xdmatest_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdmatest_intr ; 

__attribute__((used)) static int
xdmatest_test(struct xdmatest_softc *sc)
{
	int err;
	int i;

	/* Get xDMA controller. */
	sc->xdma = xdma_ofw_get(sc->dev, "test");
	if (sc->xdma == NULL) {
		device_printf(sc->dev, "Can't find xDMA controller.\n");
		return (-1);
	}

	/* Alloc xDMA virtual channel. */
	sc->xchan = xdma_channel_alloc(sc->xdma);
	if (sc->xchan == NULL) {
		device_printf(sc->dev, "Can't alloc virtual DMA channel.\n");
		return (-1);
	}

	/* Setup callback. */
	err = xdma_setup_intr(sc->xchan, xdmatest_intr, sc, &sc->ih);
	if (err) {
		device_printf(sc->dev, "Can't setup xDMA interrupt handler.\n");
		return (-1);
	}

	/* We are going to fill memory. */
	bus_dmamap_sync(sc->src_dma_tag, sc->src_dma_map, BUS_DMASYNC_PREWRITE);
	bus_dmamap_sync(sc->dst_dma_tag, sc->dst_dma_map, BUS_DMASYNC_PREWRITE);

	/* Fill memory. */
	for (i = 0; i < sc->len; i++) {
		sc->src[i] = (i & 0xff);
		sc->dst[i] = 0;
	}

	sc->req.type = XR_TYPE_PHYS_ADDR;
	sc->req.direction = XDMA_MEM_TO_MEM;
	sc->req.src_addr = sc->src_phys;
	sc->req.dst_addr = sc->dst_phys;
	sc->req.src_width = 4;
	sc->req.dst_width = 4;
	sc->req.block_len = sc->len;
	sc->req.block_num = 1;

	err = xdma_request(sc->xchan, sc->src_phys, sc->dst_phys, sc->len);
	if (err != 0) {
		device_printf(sc->dev, "Can't configure virtual channel.\n");
		return (-1);
	}

	/* Start operation. */
	xdma_begin(sc->xchan);

	return (0);
}