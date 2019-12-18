#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cgem_tx_desc {int dummy; } ;
struct cgem_softc {scalar_t__ txring_queued; scalar_t__ txring_tl_ptr; scalar_t__ txring_hd_ptr; TYPE_2__* txring; int /*<<< orphan*/ ** txring_m_dmamap; int /*<<< orphan*/ ** txring_m; int /*<<< orphan*/  txring_physaddr; int /*<<< orphan*/  txring_dma_map; int /*<<< orphan*/  desc_dma_tag; scalar_t__ rxring_queued; scalar_t__ rxring_tl_ptr; scalar_t__ rxring_hd_ptr; TYPE_1__* rxring; int /*<<< orphan*/ ** rxring_m_dmamap; int /*<<< orphan*/ ** rxring_m; int /*<<< orphan*/  rxring_physaddr; int /*<<< orphan*/  rxring_dma_map; int /*<<< orphan*/  mbuf_dma_tag; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  dev; } ;
struct cgem_rx_desc {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  ctl; scalar_t__ addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  addr; scalar_t__ ctl; } ;

/* Variables and functions */
 int BUS_DMA_COHERENT ; 
 int BUS_DMA_NOWAIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int CGEM_NUM_RX_DESCS ; 
 int CGEM_NUM_TX_DESCS ; 
 int /*<<< orphan*/  CGEM_RXDESC_OWN ; 
 int /*<<< orphan*/  CGEM_RXDESC_WRAP ; 
 int /*<<< orphan*/  CGEM_TXDESC_USED ; 
 int /*<<< orphan*/  CGEM_TXDESC_WRAP ; 
 int /*<<< orphan*/  MAX_DESC_RING_SIZE ; 
 int /*<<< orphan*/  MCLBYTES ; 
 int TX_MAX_DMA_SEGS ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  busdma_lock_mutex ; 
 int /*<<< orphan*/  cgem_getaddr ; 

__attribute__((used)) static int
cgem_setup_descs(struct cgem_softc *sc)
{
	int i, err;

	sc->txring = NULL;
	sc->rxring = NULL;

	/* Allocate non-cached DMA space for RX and TX descriptors.
	 */
	err = bus_dma_tag_create(bus_get_dma_tag(sc->dev), 1, 0,
				 BUS_SPACE_MAXADDR_32BIT,
				 BUS_SPACE_MAXADDR,
				 NULL, NULL,
				 MAX_DESC_RING_SIZE,
				 1,
				 MAX_DESC_RING_SIZE,
				 0,
				 busdma_lock_mutex,
				 &sc->sc_mtx,
				 &sc->desc_dma_tag);
	if (err)
		return (err);

	/* Set up a bus_dma_tag for mbufs. */
	err = bus_dma_tag_create(bus_get_dma_tag(sc->dev), 1, 0,
				 BUS_SPACE_MAXADDR_32BIT,
				 BUS_SPACE_MAXADDR,
				 NULL, NULL,
				 MCLBYTES,
				 TX_MAX_DMA_SEGS,
				 MCLBYTES,
				 0,
				 busdma_lock_mutex,
				 &sc->sc_mtx,
				 &sc->mbuf_dma_tag);
	if (err)
		return (err);

	/* Allocate DMA memory in non-cacheable space. */
	err = bus_dmamem_alloc(sc->desc_dma_tag,
			       (void **)&sc->rxring,
			       BUS_DMA_NOWAIT | BUS_DMA_COHERENT,
			       &sc->rxring_dma_map);
	if (err)
		return (err);

	/* Load descriptor DMA memory. */
	err = bus_dmamap_load(sc->desc_dma_tag, sc->rxring_dma_map,
			      (void *)sc->rxring,
			      CGEM_NUM_RX_DESCS*sizeof(struct cgem_rx_desc),
			      cgem_getaddr, &sc->rxring_physaddr,
			      BUS_DMA_NOWAIT);
	if (err)
		return (err);

	/* Initialize RX descriptors. */
	for (i = 0; i < CGEM_NUM_RX_DESCS; i++) {
		sc->rxring[i].addr = CGEM_RXDESC_OWN;
		sc->rxring[i].ctl = 0;
		sc->rxring_m[i] = NULL;
		sc->rxring_m_dmamap[i] = NULL;
	}
	sc->rxring[CGEM_NUM_RX_DESCS - 1].addr |= CGEM_RXDESC_WRAP;

	sc->rxring_hd_ptr = 0;
	sc->rxring_tl_ptr = 0;
	sc->rxring_queued = 0;

	/* Allocate DMA memory for TX descriptors in non-cacheable space. */
	err = bus_dmamem_alloc(sc->desc_dma_tag,
			       (void **)&sc->txring,
			       BUS_DMA_NOWAIT | BUS_DMA_COHERENT,
			       &sc->txring_dma_map);
	if (err)
		return (err);

	/* Load TX descriptor DMA memory. */
	err = bus_dmamap_load(sc->desc_dma_tag, sc->txring_dma_map,
			      (void *)sc->txring,
			      CGEM_NUM_TX_DESCS*sizeof(struct cgem_tx_desc),
			      cgem_getaddr, &sc->txring_physaddr, 
			      BUS_DMA_NOWAIT);
	if (err)
		return (err);

	/* Initialize TX descriptor ring. */
	for (i = 0; i < CGEM_NUM_TX_DESCS; i++) {
		sc->txring[i].addr = 0;
		sc->txring[i].ctl = CGEM_TXDESC_USED;
		sc->txring_m[i] = NULL;
		sc->txring_m_dmamap[i] = NULL;
	}
	sc->txring[CGEM_NUM_TX_DESCS - 1].ctl |= CGEM_TXDESC_WRAP;

	sc->txring_hd_ptr = 0;
	sc->txring_tl_ptr = 0;
	sc->txring_queued = 0;

	return (0);
}