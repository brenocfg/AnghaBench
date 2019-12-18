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
struct ubsec_softc {int /*<<< orphan*/  sc_dev; } ;
struct ubsec_dma_alloc {int /*<<< orphan*/ * dma_tag; int /*<<< orphan*/  dma_map; int /*<<< orphan*/  dma_vaddr; scalar_t__ dma_size; int /*<<< orphan*/  dma_paddr; } ;
typedef  int /*<<< orphan*/  intmax_t ;
typedef  scalar_t__ bus_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_ALLOCNOW ; 
 int BUS_DMA_NOWAIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int bus_dmamap_load (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ *,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  ubsec_dmamap_cb ; 

__attribute__((used)) static int
ubsec_dma_malloc(
	struct ubsec_softc *sc,
	bus_size_t size,
	struct ubsec_dma_alloc *dma,
	int mapflags
)
{
	int r;

	/* XXX could specify sc_dmat as parent but that just adds overhead */
	r = bus_dma_tag_create(bus_get_dma_tag(sc->sc_dev),	/* parent */
			       1, 0,			/* alignment, bounds */
			       BUS_SPACE_MAXADDR_32BIT,	/* lowaddr */
			       BUS_SPACE_MAXADDR,	/* highaddr */
			       NULL, NULL,		/* filter, filterarg */
			       size,			/* maxsize */
			       1,			/* nsegments */
			       size,			/* maxsegsize */
			       BUS_DMA_ALLOCNOW,	/* flags */
			       NULL, NULL,		/* lockfunc, lockarg */
			       &dma->dma_tag);
	if (r != 0) {
		device_printf(sc->sc_dev, "ubsec_dma_malloc: "
			"bus_dma_tag_create failed; error %u\n", r);
		goto fail_1;
	}

	r = bus_dmamem_alloc(dma->dma_tag, (void**) &dma->dma_vaddr,
			     BUS_DMA_NOWAIT, &dma->dma_map);
	if (r != 0) {
		device_printf(sc->sc_dev, "ubsec_dma_malloc: "
			"bus_dmammem_alloc failed; size %ju, error %u\n",
			(intmax_t)size, r);
		goto fail_2;
	}

	r = bus_dmamap_load(dma->dma_tag, dma->dma_map, dma->dma_vaddr,
		            size,
			    ubsec_dmamap_cb,
			    &dma->dma_paddr,
			    mapflags | BUS_DMA_NOWAIT);
	if (r != 0) {
		device_printf(sc->sc_dev, "ubsec_dma_malloc: "
			"bus_dmamap_load failed; error %u\n", r);
		goto fail_3;
	}

	dma->dma_size = size;
	return (0);

fail_3:
	bus_dmamap_unload(dma->dma_tag, dma->dma_map);
fail_2:
	bus_dmamem_free(dma->dma_tag, dma->dma_vaddr, dma->dma_map);
fail_1:
	bus_dma_tag_destroy(dma->dma_tag);
	dma->dma_tag = NULL;
	return (r);
}