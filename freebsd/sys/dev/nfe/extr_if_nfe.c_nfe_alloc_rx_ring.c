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
struct TYPE_2__ {struct nfe_rx_data* data; } ;
struct nfe_softc {int nfe_flags; int /*<<< orphan*/  nfe_dev; TYPE_1__ rxq; int /*<<< orphan*/  nfe_parent_tag; } ;
struct nfe_rx_ring {int /*<<< orphan*/  rx_data_tag; int /*<<< orphan*/ * rx_spare_map; scalar_t__ physaddr; int /*<<< orphan*/  rx_desc_map; int /*<<< orphan*/  rx_desc_tag; void* desc32; void* desc64; scalar_t__ next; scalar_t__ cur; } ;
struct nfe_rx_data {int /*<<< orphan*/ * rx_data_map; int /*<<< orphan*/ * m; } ;
struct nfe_dmamap_arg {scalar_t__ nfe_busaddr; } ;
struct nfe_desc64 {int dummy; } ;
struct nfe_desc32 {int dummy; } ;

/* Variables and functions */
 int BUS_DMA_COHERENT ; 
 int BUS_DMA_WAITOK ; 
 int BUS_DMA_ZERO ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int MCLBYTES ; 
 int NFE_40BIT_ADDR ; 
 int NFE_RING_ALIGN ; 
 int NFE_RX_RING_COUNT ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ,struct nfe_dmamap_arg*,int /*<<< orphan*/ ) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nfe_dma_map_segs ; 

__attribute__((used)) static int
nfe_alloc_rx_ring(struct nfe_softc *sc, struct nfe_rx_ring *ring)
{
	struct nfe_dmamap_arg ctx;
	struct nfe_rx_data *data;
	void *desc;
	int i, error, descsize;

	if (sc->nfe_flags & NFE_40BIT_ADDR) {
		desc = ring->desc64;
		descsize = sizeof (struct nfe_desc64);
	} else {
		desc = ring->desc32;
		descsize = sizeof (struct nfe_desc32);
	}

	ring->cur = ring->next = 0;

	error = bus_dma_tag_create(sc->nfe_parent_tag,
	    NFE_RING_ALIGN, 0,			/* alignment, boundary */
	    BUS_SPACE_MAXADDR,			/* lowaddr */
	    BUS_SPACE_MAXADDR,			/* highaddr */
	    NULL, NULL,				/* filter, filterarg */
	    NFE_RX_RING_COUNT * descsize, 1,	/* maxsize, nsegments */
	    NFE_RX_RING_COUNT * descsize,	/* maxsegsize */
	    0,					/* flags */
	    NULL, NULL,				/* lockfunc, lockarg */
	    &ring->rx_desc_tag);
	if (error != 0) {
		device_printf(sc->nfe_dev, "could not create desc DMA tag\n");
		goto fail;
	}

	/* allocate memory to desc */
	error = bus_dmamem_alloc(ring->rx_desc_tag, &desc, BUS_DMA_WAITOK |
	    BUS_DMA_COHERENT | BUS_DMA_ZERO, &ring->rx_desc_map);
	if (error != 0) {
		device_printf(sc->nfe_dev, "could not create desc DMA map\n");
		goto fail;
	}
	if (sc->nfe_flags & NFE_40BIT_ADDR)
		ring->desc64 = desc;
	else
		ring->desc32 = desc;

	/* map desc to device visible address space */
	ctx.nfe_busaddr = 0;
	error = bus_dmamap_load(ring->rx_desc_tag, ring->rx_desc_map, desc,
	    NFE_RX_RING_COUNT * descsize, nfe_dma_map_segs, &ctx, 0);
	if (error != 0) {
		device_printf(sc->nfe_dev, "could not load desc DMA map\n");
		goto fail;
	}
	ring->physaddr = ctx.nfe_busaddr;

	error = bus_dma_tag_create(sc->nfe_parent_tag,
	    1, 0,			/* alignment, boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    MCLBYTES, 1,		/* maxsize, nsegments */
	    MCLBYTES,			/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockarg */
	    &ring->rx_data_tag);
	if (error != 0) {
		device_printf(sc->nfe_dev, "could not create Rx DMA tag\n");
		goto fail;
	}

	error = bus_dmamap_create(ring->rx_data_tag, 0, &ring->rx_spare_map);
	if (error != 0) {
		device_printf(sc->nfe_dev,
		    "could not create Rx DMA spare map\n");
		goto fail;
	}

	/*
	 * Pre-allocate Rx buffers and populate Rx ring.
	 */
	for (i = 0; i < NFE_RX_RING_COUNT; i++) {
		data = &sc->rxq.data[i];
		data->rx_data_map = NULL;
		data->m = NULL;
		error = bus_dmamap_create(ring->rx_data_tag, 0,
		    &data->rx_data_map);
		if (error != 0) {
			device_printf(sc->nfe_dev,
			    "could not create Rx DMA map\n");
			goto fail;
		}
	}

fail:
	return (error);
}