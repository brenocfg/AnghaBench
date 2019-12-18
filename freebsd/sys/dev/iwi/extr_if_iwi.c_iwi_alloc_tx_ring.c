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
struct iwi_tx_ring {int count; TYPE_1__* data; int /*<<< orphan*/  data_dmat; int /*<<< orphan*/  physaddr; int /*<<< orphan*/  desc; int /*<<< orphan*/  desc_map; int /*<<< orphan*/  desc_dmat; void* csr_widx; void* csr_ridx; scalar_t__ next; scalar_t__ cur; scalar_t__ queued; } ;
struct iwi_tx_data {int dummy; } ;
struct iwi_softc {int /*<<< orphan*/  sc_dev; } ;
typedef  void* bus_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int BUS_DMA_NOWAIT ; 
 int BUS_DMA_ZERO ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int ENOMEM ; 
 int IWI_MAX_NSEG ; 
 int IWI_TX_DESC_SIZE ; 
 int MCLBYTES ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  iwi_dma_map_addr ; 
 int /*<<< orphan*/  iwi_free_tx_ring (struct iwi_softc*,struct iwi_tx_ring*) ; 
 TYPE_1__* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
iwi_alloc_tx_ring(struct iwi_softc *sc, struct iwi_tx_ring *ring, int count,
    bus_addr_t csr_ridx, bus_addr_t csr_widx)
{
	int i, error;

	ring->count = count;
	ring->queued = 0;
	ring->cur = ring->next = 0;
	ring->csr_ridx = csr_ridx;
	ring->csr_widx = csr_widx;

	error = bus_dma_tag_create(bus_get_dma_tag(sc->sc_dev), 4, 0,
	    BUS_SPACE_MAXADDR_32BIT, BUS_SPACE_MAXADDR, NULL, NULL,
	    count * IWI_TX_DESC_SIZE, 1, count * IWI_TX_DESC_SIZE, 0, NULL, 
	    NULL, &ring->desc_dmat);
	if (error != 0) {
		device_printf(sc->sc_dev, "could not create desc DMA tag\n");
		goto fail;
	}

	error = bus_dmamem_alloc(ring->desc_dmat, (void **)&ring->desc,
	    BUS_DMA_NOWAIT | BUS_DMA_ZERO, &ring->desc_map);
	if (error != 0) {
		device_printf(sc->sc_dev, "could not allocate DMA memory\n");
		goto fail;
	}

	error = bus_dmamap_load(ring->desc_dmat, ring->desc_map, ring->desc,
	    count * IWI_TX_DESC_SIZE, iwi_dma_map_addr, &ring->physaddr, 0);
	if (error != 0) {
		device_printf(sc->sc_dev, "could not load desc DMA map\n");
		goto fail;
	}

	ring->data = malloc(count * sizeof (struct iwi_tx_data), M_DEVBUF,
	    M_NOWAIT | M_ZERO);
	if (ring->data == NULL) {
		device_printf(sc->sc_dev, "could not allocate soft data\n");
		error = ENOMEM;
		goto fail;
	}

	error = bus_dma_tag_create(bus_get_dma_tag(sc->sc_dev), 1, 0,
	BUS_SPACE_MAXADDR_32BIT, BUS_SPACE_MAXADDR, NULL, NULL, MCLBYTES,
	IWI_MAX_NSEG, MCLBYTES, 0, NULL, NULL, &ring->data_dmat);
	if (error != 0) {
		device_printf(sc->sc_dev, "could not create data DMA tag\n");
		goto fail;
	}

	for (i = 0; i < count; i++) {
		error = bus_dmamap_create(ring->data_dmat, 0,
		    &ring->data[i].map);
		if (error != 0) {
			device_printf(sc->sc_dev, "could not create DMA map\n");
			goto fail;
		}
	}

	return 0;

fail:	iwi_free_tx_ring(sc, ring);
	return error;
}