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
struct glxsb_dma_map {int dma_nsegs; int dma_size; int /*<<< orphan*/  dma_map; int /*<<< orphan*/  dma_vaddr; int /*<<< orphan*/  dma_paddr; } ;
struct glxsb_softc {int /*<<< orphan*/  sc_dmat; int /*<<< orphan*/  sc_dev; struct glxsb_dma_map sc_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_ALLOCNOW ; 
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int GLXSB_MAX_AES_LEN ; 
 int /*<<< orphan*/  SB_AES_ALIGN ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  glxsb_dmamap_cb ; 

__attribute__((used)) static int
glxsb_dma_alloc(struct glxsb_softc *sc)
{
	struct glxsb_dma_map *dma = &sc->sc_dma;
	int rc;

	dma->dma_nsegs = 1;
	dma->dma_size = GLXSB_MAX_AES_LEN * 2;

	/* Setup DMA descriptor area */
	rc = bus_dma_tag_create(bus_get_dma_tag(sc->sc_dev),	/* parent */
				SB_AES_ALIGN, 0,	/* alignments, bounds */
				BUS_SPACE_MAXADDR_32BIT,/* lowaddr */
				BUS_SPACE_MAXADDR,	/* highaddr */
				NULL, NULL,		/* filter, filterarg */
				dma->dma_size,		/* maxsize */
				dma->dma_nsegs,		/* nsegments */
				dma->dma_size,		/* maxsegsize */
				BUS_DMA_ALLOCNOW,	/* flags */
				NULL, NULL,		/* lockfunc, lockarg */
				&sc->sc_dmat);
	if (rc != 0) {
		device_printf(sc->sc_dev,
		    "cannot allocate DMA tag (%d)\n", rc);
		return (rc);
	}

	rc = bus_dmamem_alloc(sc->sc_dmat, (void **)&dma->dma_vaddr,
	    BUS_DMA_NOWAIT, &dma->dma_map);
	if (rc != 0) {
		device_printf(sc->sc_dev,
		    "cannot allocate DMA memory of %d bytes (%d)\n",
			dma->dma_size, rc);
		goto fail0;
	}

	rc = bus_dmamap_load(sc->sc_dmat, dma->dma_map, dma->dma_vaddr,
	    dma->dma_size, glxsb_dmamap_cb, &dma->dma_paddr, BUS_DMA_NOWAIT);
	if (rc != 0) {
		device_printf(sc->sc_dev,
		    "cannot load DMA memory for %d bytes (%d)\n",
		   dma->dma_size, rc);
		goto fail1;
	}

	return (0);

fail1:
	bus_dmamem_free(sc->sc_dmat, dma->dma_vaddr, dma->dma_map);
fail0:
	bus_dma_tag_destroy(sc->sc_dmat);
	return (rc);
}