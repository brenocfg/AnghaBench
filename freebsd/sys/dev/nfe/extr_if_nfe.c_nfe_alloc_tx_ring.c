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
struct nfe_tx_ring {TYPE_1__* data; int /*<<< orphan*/  tx_data_tag; scalar_t__ physaddr; int /*<<< orphan*/  tx_desc_map; int /*<<< orphan*/  tx_desc_tag; void* desc32; void* desc64; scalar_t__ next; scalar_t__ cur; scalar_t__ queued; } ;
struct nfe_softc {int nfe_flags; int /*<<< orphan*/  nfe_dev; int /*<<< orphan*/  nfe_parent_tag; } ;
struct nfe_dmamap_arg {scalar_t__ nfe_busaddr; } ;
struct nfe_desc64 {int dummy; } ;
struct nfe_desc32 {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_data_map; } ;

/* Variables and functions */
 int BUS_DMA_COHERENT ; 
 int BUS_DMA_WAITOK ; 
 int BUS_DMA_ZERO ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int NFE_40BIT_ADDR ; 
 int NFE_MAX_SCATTER ; 
 int NFE_RING_ALIGN ; 
 int NFE_TSO_MAXSGSIZE ; 
 int NFE_TSO_MAXSIZE ; 
 int NFE_TX_RING_COUNT ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ,struct nfe_dmamap_arg*,int /*<<< orphan*/ ) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nfe_dma_map_segs ; 

__attribute__((used)) static int
nfe_alloc_tx_ring(struct nfe_softc *sc, struct nfe_tx_ring *ring)
{
	struct nfe_dmamap_arg ctx;
	int i, error;
	void *desc;
	int descsize;

	if (sc->nfe_flags & NFE_40BIT_ADDR) {
		desc = ring->desc64;
		descsize = sizeof (struct nfe_desc64);
	} else {
		desc = ring->desc32;
		descsize = sizeof (struct nfe_desc32);
	}

	ring->queued = 0;
	ring->cur = ring->next = 0;

	error = bus_dma_tag_create(sc->nfe_parent_tag,
	    NFE_RING_ALIGN, 0,			/* alignment, boundary */
	    BUS_SPACE_MAXADDR,			/* lowaddr */
	    BUS_SPACE_MAXADDR,			/* highaddr */
	    NULL, NULL,				/* filter, filterarg */
	    NFE_TX_RING_COUNT * descsize, 1,	/* maxsize, nsegments */
	    NFE_TX_RING_COUNT * descsize,	/* maxsegsize */
	    0,					/* flags */
	    NULL, NULL,				/* lockfunc, lockarg */
	    &ring->tx_desc_tag);
	if (error != 0) {
		device_printf(sc->nfe_dev, "could not create desc DMA tag\n");
		goto fail;
	}

	error = bus_dmamem_alloc(ring->tx_desc_tag, &desc, BUS_DMA_WAITOK |
	    BUS_DMA_COHERENT | BUS_DMA_ZERO, &ring->tx_desc_map);
	if (error != 0) {
		device_printf(sc->nfe_dev, "could not create desc DMA map\n");
		goto fail;
	}
	if (sc->nfe_flags & NFE_40BIT_ADDR)
		ring->desc64 = desc;
	else
		ring->desc32 = desc;

	ctx.nfe_busaddr = 0;
	error = bus_dmamap_load(ring->tx_desc_tag, ring->tx_desc_map, desc,
	    NFE_TX_RING_COUNT * descsize, nfe_dma_map_segs, &ctx, 0);
	if (error != 0) {
		device_printf(sc->nfe_dev, "could not load desc DMA map\n");
		goto fail;
	}
	ring->physaddr = ctx.nfe_busaddr;

	error = bus_dma_tag_create(sc->nfe_parent_tag,
	    1, 0,
	    BUS_SPACE_MAXADDR,
	    BUS_SPACE_MAXADDR,
	    NULL, NULL,
	    NFE_TSO_MAXSIZE,
	    NFE_MAX_SCATTER,
	    NFE_TSO_MAXSGSIZE,
	    0,
	    NULL, NULL,
	    &ring->tx_data_tag);
	if (error != 0) {
		device_printf(sc->nfe_dev, "could not create Tx DMA tag\n");
		goto fail;
	}

	for (i = 0; i < NFE_TX_RING_COUNT; i++) {
		error = bus_dmamap_create(ring->tx_data_tag, 0,
		    &ring->data[i].tx_data_map);
		if (error != 0) {
			device_printf(sc->nfe_dev,
			    "could not create Tx DMA map\n");
			goto fail;
		}
	}

fail:
	return (error);
}