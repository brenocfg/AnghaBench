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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct rtwn_tx_ring {int /*<<< orphan*/  data_dmat; scalar_t__ paddr; scalar_t__ desc; struct rtwn_tx_data* tx_data; int /*<<< orphan*/  desc_map; int /*<<< orphan*/  desc_dmat; } ;
struct rtwn_tx_data {int /*<<< orphan*/ * ni; int /*<<< orphan*/ * m; int /*<<< orphan*/  map; } ;
struct rtwn_softc {int txdesc_len; int /*<<< orphan*/  sc_dev; } ;
struct rtwn_pci_softc {struct rtwn_tx_ring* tx_ring; } ;
typedef  int bus_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int BUS_DMA_NOWAIT ; 
 int BUS_DMA_ZERO ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int MJUMPAGESIZE ; 
 int PAGE_SIZE ; 
 struct rtwn_pci_softc* RTWN_PCI_SOFTC (struct rtwn_softc*) ; 
 int RTWN_PCI_TX_LIST_COUNT ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,scalar_t__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rtwn_pci_dma_map_addr ; 
 int /*<<< orphan*/  rtwn_pci_free_tx_list (struct rtwn_softc*,int) ; 
 int /*<<< orphan*/  rtwn_pci_setup_tx_desc (struct rtwn_pci_softc*,void*,scalar_t__) ; 

__attribute__((used)) static int
rtwn_pci_alloc_tx_list(struct rtwn_softc *sc, int qid)
{
	struct rtwn_pci_softc *pc = RTWN_PCI_SOFTC(sc);
	struct rtwn_tx_ring *tx_ring = &pc->tx_ring[qid];
	bus_size_t size;
	int i, error;

	size = sc->txdesc_len * RTWN_PCI_TX_LIST_COUNT;
	error = bus_dma_tag_create(bus_get_dma_tag(sc->sc_dev), PAGE_SIZE, 0,
	    BUS_SPACE_MAXADDR_32BIT, BUS_SPACE_MAXADDR, NULL, NULL,
	    size, 1, size, 0, NULL, NULL, &tx_ring->desc_dmat);
	if (error != 0) {
		device_printf(sc->sc_dev, "could not create tx ring DMA tag\n");
		goto fail;
	}

	error = bus_dmamem_alloc(tx_ring->desc_dmat, &tx_ring->desc,
	    BUS_DMA_NOWAIT | BUS_DMA_ZERO, &tx_ring->desc_map);
	if (error != 0) {
		device_printf(sc->sc_dev, "can't map tx ring DMA memory\n");
		goto fail;
	}
	error = bus_dmamap_load(tx_ring->desc_dmat, tx_ring->desc_map,
	    tx_ring->desc, size, rtwn_pci_dma_map_addr, &tx_ring->paddr,
	    BUS_DMA_NOWAIT);
	if (error != 0) {
		device_printf(sc->sc_dev, "could not load desc DMA map\n");
		goto fail;
	}
	bus_dmamap_sync(tx_ring->desc_dmat, tx_ring->desc_map,
	    BUS_DMASYNC_PREWRITE);

	error = bus_dma_tag_create(bus_get_dma_tag(sc->sc_dev), 1, 0,
	    BUS_SPACE_MAXADDR_32BIT, BUS_SPACE_MAXADDR, NULL, NULL,
	    MJUMPAGESIZE, 1, MJUMPAGESIZE, 0, NULL, NULL, &tx_ring->data_dmat);
	if (error != 0) {
		device_printf(sc->sc_dev, "could not create tx buf DMA tag\n");
		goto fail;
	}

	for (i = 0; i < RTWN_PCI_TX_LIST_COUNT; i++) {
		struct rtwn_tx_data *tx_data = &tx_ring->tx_data[i];
		void *tx_desc = (uint8_t *)tx_ring->desc + sc->txdesc_len * i;
		uint32_t next_desc_addr = tx_ring->paddr +
		    sc->txdesc_len * ((i + 1) % RTWN_PCI_TX_LIST_COUNT);

		rtwn_pci_setup_tx_desc(pc, tx_desc, next_desc_addr);

		error = bus_dmamap_create(tx_ring->data_dmat, 0, &tx_data->map);
		if (error != 0) {
			device_printf(sc->sc_dev,
			    "could not create tx buf DMA map\n");
			return (error);
		}
		tx_data->m = NULL;
		tx_data->ni = NULL;
	}
	return (0);

fail:
	rtwn_pci_free_tx_list(sc, qid);
	return (error);
}