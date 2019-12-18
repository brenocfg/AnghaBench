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
struct sis_txdesc {int /*<<< orphan*/  tx_dmamap; int /*<<< orphan*/ * tx_m; } ;
struct sis_softc {int /*<<< orphan*/  sis_dev; int /*<<< orphan*/  sis_tx_tag; struct sis_txdesc* sis_txdesc; int /*<<< orphan*/  sis_rx_tag; struct sis_rxdesc* sis_rxdesc; int /*<<< orphan*/  sis_rx_sparemap; int /*<<< orphan*/  sis_parent_tag; int /*<<< orphan*/  sis_tx_paddr; int /*<<< orphan*/  sis_tx_list_map; int /*<<< orphan*/  sis_tx_list; int /*<<< orphan*/  sis_tx_list_tag; int /*<<< orphan*/  sis_rx_paddr; int /*<<< orphan*/  sis_rx_list_map; int /*<<< orphan*/  sis_rx_list; int /*<<< orphan*/  sis_rx_list_tag; } ;
struct sis_rxdesc {int /*<<< orphan*/  rx_dmamap; int /*<<< orphan*/ * rx_m; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int BUS_SPACE_MAXSIZE_32BIT ; 
 int ENOMEM ; 
 int MCLBYTES ; 
 int /*<<< orphan*/  SIS_DESC_ALIGN ; 
 int SIS_MAXTXSEGS ; 
 int SIS_RX_BUF_ALIGN ; 
 int SIS_RX_LIST_CNT ; 
 int /*<<< orphan*/  SIS_RX_LIST_SZ ; 
 int SIS_TX_LIST_CNT ; 
 int /*<<< orphan*/  SIS_TX_LIST_SZ ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int sis_dma_ring_alloc (struct sis_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
sis_dma_alloc(struct sis_softc *sc)
{
	struct sis_rxdesc	*rxd;
	struct sis_txdesc	*txd;
	int			error, i;

	/* Allocate the parent bus DMA tag appropriate for PCI. */
	error = bus_dma_tag_create(bus_get_dma_tag(sc->sis_dev),
	    1, 0, BUS_SPACE_MAXADDR_32BIT, BUS_SPACE_MAXADDR, NULL,
	    NULL, BUS_SPACE_MAXSIZE_32BIT, 0, BUS_SPACE_MAXSIZE_32BIT,
	    0, NULL, NULL, &sc->sis_parent_tag);
	if (error != 0) {
		device_printf(sc->sis_dev,
		    "could not allocate parent dma tag\n");
		return (ENOMEM);
	}

	/* Create RX ring. */
	error = sis_dma_ring_alloc(sc, SIS_DESC_ALIGN, SIS_RX_LIST_SZ,
	    &sc->sis_rx_list_tag, (uint8_t **)&sc->sis_rx_list,
	    &sc->sis_rx_list_map, &sc->sis_rx_paddr, "RX ring");
	if (error)
		return (error);

	/* Create TX ring. */
	error = sis_dma_ring_alloc(sc, SIS_DESC_ALIGN, SIS_TX_LIST_SZ,
	    &sc->sis_tx_list_tag, (uint8_t **)&sc->sis_tx_list,
	    &sc->sis_tx_list_map, &sc->sis_tx_paddr, "TX ring");
	if (error)
		return (error);

	/* Create tag for RX mbufs. */
	error = bus_dma_tag_create(sc->sis_parent_tag, SIS_RX_BUF_ALIGN, 0,
	    BUS_SPACE_MAXADDR, BUS_SPACE_MAXADDR, NULL, NULL, MCLBYTES, 1,
	    MCLBYTES, 0, NULL, NULL, &sc->sis_rx_tag);
	if (error) {
		device_printf(sc->sis_dev, "could not allocate RX dma tag\n");
		return (error);
	}

	/* Create tag for TX mbufs. */
	error = bus_dma_tag_create(sc->sis_parent_tag, 1, 0,
	    BUS_SPACE_MAXADDR, BUS_SPACE_MAXADDR, NULL, NULL,
	    MCLBYTES * SIS_MAXTXSEGS, SIS_MAXTXSEGS, MCLBYTES, 0, NULL, NULL,
	    &sc->sis_tx_tag);
	if (error) {
		device_printf(sc->sis_dev, "could not allocate TX dma tag\n");
		return (error);
	}

	/* Create DMA maps for RX buffers. */
	error = bus_dmamap_create(sc->sis_rx_tag, 0, &sc->sis_rx_sparemap);
	if (error) {
		device_printf(sc->sis_dev,
		    "can't create spare DMA map for RX\n");
		return (error);
	}
	for (i = 0; i < SIS_RX_LIST_CNT; i++) {
		rxd = &sc->sis_rxdesc[i];
		rxd->rx_m = NULL;
		error = bus_dmamap_create(sc->sis_rx_tag, 0, &rxd->rx_dmamap);
		if (error) {
			device_printf(sc->sis_dev,
			    "can't create DMA map for RX\n");
			return (error);
		}
	}

	/* Create DMA maps for TX buffers. */
	for (i = 0; i < SIS_TX_LIST_CNT; i++) {
		txd = &sc->sis_txdesc[i];
		txd->tx_m = NULL;
		error = bus_dmamap_create(sc->sis_tx_tag, 0, &txd->tx_dmamap);
		if (error) {
			device_printf(sc->sis_dev,
			    "can't create DMA map for TX\n");
			return (error);
		}
	}

	return (0);
}