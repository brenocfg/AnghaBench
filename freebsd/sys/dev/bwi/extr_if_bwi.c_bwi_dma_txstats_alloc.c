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
typedef  int /*<<< orphan*/  uint32_t ;
struct bwi_txstats_data {void* stats_ring; void* stats; int /*<<< orphan*/  stats_ctrl_base; int /*<<< orphan*/ * stats_dtag; int /*<<< orphan*/  stats_dmap; int /*<<< orphan*/  stats_paddr; int /*<<< orphan*/ * stats_ring_dtag; int /*<<< orphan*/  stats_ring_dmap; int /*<<< orphan*/  stats_ring_paddr; } ;
struct bwi_txstats {int dummy; } ;
struct bwi_softc {int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_parent_dtag; struct bwi_txstats_data* sc_txstats; } ;
typedef  int bus_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int BUS_DMA_WAITOK ; 
 int BUS_DMA_ZERO ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BWI_ALIGN ; 
 int /*<<< orphan*/  BWI_RING_ALIGN ; 
 int BWI_TXSTATS_NDESC ; 
 int ENOMEM ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int bus_dmamap_load (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ *,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwi_dma_ring_addr ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 struct bwi_txstats_data* malloc (int,int /*<<< orphan*/ ,int) ; 
 int roundup (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bwi_dma_txstats_alloc(struct bwi_softc *sc, uint32_t ctrl_base,
		      bus_size_t desc_sz)
{
	struct bwi_txstats_data *st;
	bus_size_t dma_size;
	int error;

	st = malloc(sizeof(*st), M_DEVBUF, M_NOWAIT | M_ZERO);
	if (st == NULL) {
		device_printf(sc->sc_dev, "can't allocate txstats data\n");
		return ENOMEM;
	}
	sc->sc_txstats = st;

	/*
	 * Create TX stats descriptor DMA stuffs
	 */
	dma_size = roundup(desc_sz * BWI_TXSTATS_NDESC, BWI_RING_ALIGN);

	error = bus_dma_tag_create(sc->sc_parent_dtag,
				BWI_RING_ALIGN,
				0,
				BUS_SPACE_MAXADDR,
				BUS_SPACE_MAXADDR,
				NULL, NULL,
				dma_size,
				1,
				dma_size,
				0,
				NULL, NULL,
				&st->stats_ring_dtag);
	if (error) {
		device_printf(sc->sc_dev, "can't create txstats ring "
			      "DMA tag\n");
		return error;
	}

	error = bus_dmamem_alloc(st->stats_ring_dtag, &st->stats_ring,
				 BUS_DMA_WAITOK | BUS_DMA_ZERO,
				 &st->stats_ring_dmap);
	if (error) {
		device_printf(sc->sc_dev, "can't allocate txstats ring "
			      "DMA mem\n");
		bus_dma_tag_destroy(st->stats_ring_dtag);
		st->stats_ring_dtag = NULL;
		return error;
	}

	error = bus_dmamap_load(st->stats_ring_dtag, st->stats_ring_dmap,
				st->stats_ring, dma_size,
				bwi_dma_ring_addr, &st->stats_ring_paddr,
				BUS_DMA_NOWAIT);
	if (error) {
		device_printf(sc->sc_dev, "can't load txstats ring DMA mem\n");
		bus_dmamem_free(st->stats_ring_dtag, st->stats_ring,
				st->stats_ring_dmap);
		bus_dma_tag_destroy(st->stats_ring_dtag);
		st->stats_ring_dtag = NULL;
		return error;
	}

	/*
	 * Create TX stats DMA stuffs
	 */
	dma_size = roundup(sizeof(struct bwi_txstats) * BWI_TXSTATS_NDESC,
			   BWI_ALIGN);

	error = bus_dma_tag_create(sc->sc_parent_dtag,
				BWI_ALIGN,
				0,
				BUS_SPACE_MAXADDR,
				BUS_SPACE_MAXADDR,
				NULL, NULL,
				dma_size,
				1,
				dma_size,
				0,
				NULL, NULL,
				&st->stats_dtag);
	if (error) {
		device_printf(sc->sc_dev, "can't create txstats DMA tag\n");
		return error;
	}

	error = bus_dmamem_alloc(st->stats_dtag, (void **)&st->stats,
				 BUS_DMA_WAITOK | BUS_DMA_ZERO,
				 &st->stats_dmap);
	if (error) {
		device_printf(sc->sc_dev, "can't allocate txstats DMA mem\n");
		bus_dma_tag_destroy(st->stats_dtag);
		st->stats_dtag = NULL;
		return error;
	}

	error = bus_dmamap_load(st->stats_dtag, st->stats_dmap, st->stats,
				dma_size, bwi_dma_ring_addr, &st->stats_paddr,
				BUS_DMA_NOWAIT);
	if (error) {
		device_printf(sc->sc_dev, "can't load txstats DMA mem\n");
		bus_dmamem_free(st->stats_dtag, st->stats, st->stats_dmap);
		bus_dma_tag_destroy(st->stats_dtag);
		st->stats_dtag = NULL;
		return error;
	}

	st->stats_ctrl_base = ctrl_base;
	return 0;
}