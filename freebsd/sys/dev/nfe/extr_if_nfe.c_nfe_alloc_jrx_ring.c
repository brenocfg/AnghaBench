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
struct TYPE_2__ {struct nfe_rx_data* jdata; } ;
struct nfe_softc {int nfe_flags; int nfe_jumbo_disable; int /*<<< orphan*/  nfe_dev; TYPE_1__ jrxq; int /*<<< orphan*/  nfe_parent_tag; } ;
struct nfe_rx_data {int /*<<< orphan*/ * rx_data_map; int /*<<< orphan*/ * m; } ;
struct nfe_jrx_ring {int /*<<< orphan*/  jrx_data_tag; int /*<<< orphan*/ * jrx_spare_map; scalar_t__ jphysaddr; int /*<<< orphan*/  jrx_desc_map; int /*<<< orphan*/  jrx_desc_tag; void* jdesc32; void* jdesc64; scalar_t__ jnext; scalar_t__ jcur; } ;
struct nfe_dmamap_arg {scalar_t__ nfe_busaddr; } ;
struct nfe_desc64 {int dummy; } ;
struct nfe_desc32 {int dummy; } ;

/* Variables and functions */
 int BUS_DMA_COHERENT ; 
 int BUS_DMA_WAITOK ; 
 int BUS_DMA_ZERO ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int MJUM9BYTES ; 
 int NFE_40BIT_ADDR ; 
 int NFE_JUMBO_RX_RING_COUNT ; 
 int NFE_JUMBO_SUP ; 
 int NFE_RING_ALIGN ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ,struct nfe_dmamap_arg*,int /*<<< orphan*/ ) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ jumbo_disable ; 
 int /*<<< orphan*/  nfe_dma_map_segs ; 
 int /*<<< orphan*/  nfe_free_jrx_ring (struct nfe_softc*,struct nfe_jrx_ring*) ; 

__attribute__((used)) static void
nfe_alloc_jrx_ring(struct nfe_softc *sc, struct nfe_jrx_ring *ring)
{
	struct nfe_dmamap_arg ctx;
	struct nfe_rx_data *data;
	void *desc;
	int i, error, descsize;

	if ((sc->nfe_flags & NFE_JUMBO_SUP) == 0)
		return;
	if (jumbo_disable != 0) {
		device_printf(sc->nfe_dev, "disabling jumbo frame support\n");
		sc->nfe_jumbo_disable = 1;
		return;
	}

	if (sc->nfe_flags & NFE_40BIT_ADDR) {
		desc = ring->jdesc64;
		descsize = sizeof (struct nfe_desc64);
	} else {
		desc = ring->jdesc32;
		descsize = sizeof (struct nfe_desc32);
	}

	ring->jcur = ring->jnext = 0;

	/* Create DMA tag for jumbo Rx ring. */
	error = bus_dma_tag_create(sc->nfe_parent_tag,
	    NFE_RING_ALIGN, 0,			/* alignment, boundary */
	    BUS_SPACE_MAXADDR,			/* lowaddr */
	    BUS_SPACE_MAXADDR,			/* highaddr */
	    NULL, NULL,				/* filter, filterarg */
	    NFE_JUMBO_RX_RING_COUNT * descsize,	/* maxsize */
	    1, 					/* nsegments */
	    NFE_JUMBO_RX_RING_COUNT * descsize,	/* maxsegsize */
	    0,					/* flags */
	    NULL, NULL,				/* lockfunc, lockarg */
	    &ring->jrx_desc_tag);
	if (error != 0) {
		device_printf(sc->nfe_dev,
		    "could not create jumbo ring DMA tag\n");
		goto fail;
	}

	/* Create DMA tag for jumbo Rx buffers. */
	error = bus_dma_tag_create(sc->nfe_parent_tag,
	    1, 0,				/* alignment, boundary */
	    BUS_SPACE_MAXADDR,			/* lowaddr */
	    BUS_SPACE_MAXADDR,			/* highaddr */
	    NULL, NULL,				/* filter, filterarg */
	    MJUM9BYTES,				/* maxsize */
	    1,					/* nsegments */
	    MJUM9BYTES,				/* maxsegsize */
	    0,					/* flags */
	    NULL, NULL,				/* lockfunc, lockarg */
	    &ring->jrx_data_tag);
	if (error != 0) {
		device_printf(sc->nfe_dev,
		    "could not create jumbo Rx buffer DMA tag\n");
		goto fail;
	}

	/* Allocate DMA'able memory and load the DMA map for jumbo Rx ring. */
	error = bus_dmamem_alloc(ring->jrx_desc_tag, &desc, BUS_DMA_WAITOK |
	    BUS_DMA_COHERENT | BUS_DMA_ZERO, &ring->jrx_desc_map);
	if (error != 0) {
		device_printf(sc->nfe_dev,
		    "could not allocate DMA'able memory for jumbo Rx ring\n");
		goto fail;
	}
	if (sc->nfe_flags & NFE_40BIT_ADDR)
		ring->jdesc64 = desc;
	else
		ring->jdesc32 = desc;

	ctx.nfe_busaddr = 0;
	error = bus_dmamap_load(ring->jrx_desc_tag, ring->jrx_desc_map, desc,
	    NFE_JUMBO_RX_RING_COUNT * descsize, nfe_dma_map_segs, &ctx, 0);
	if (error != 0) {
		device_printf(sc->nfe_dev,
		    "could not load DMA'able memory for jumbo Rx ring\n");
		goto fail;
	}
	ring->jphysaddr = ctx.nfe_busaddr;

	/* Create DMA maps for jumbo Rx buffers. */
	error = bus_dmamap_create(ring->jrx_data_tag, 0, &ring->jrx_spare_map);
	if (error != 0) {
		device_printf(sc->nfe_dev,
		    "could not create jumbo Rx DMA spare map\n");
		goto fail;
	}

	for (i = 0; i < NFE_JUMBO_RX_RING_COUNT; i++) {
		data = &sc->jrxq.jdata[i];
		data->rx_data_map = NULL;
		data->m = NULL;
		error = bus_dmamap_create(ring->jrx_data_tag, 0,
		    &data->rx_data_map);
		if (error != 0) {
			device_printf(sc->nfe_dev,
			    "could not create jumbo Rx DMA map\n");
			goto fail;
		}
	}

	return;

fail:
	/*
	 * Running without jumbo frame support is ok for most cases
	 * so don't fail on creating dma tag/map for jumbo frame.
	 */
	nfe_free_jrx_ring(sc, ring);
	device_printf(sc->nfe_dev, "disabling jumbo frame support due to "
	    "resource shortage\n");
	sc->nfe_jumbo_disable = 1;
}