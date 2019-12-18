#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct ti_status {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  ti_rx_mini_sparemap; int /*<<< orphan*/  ti_rx_mini_tag; int /*<<< orphan*/ * ti_rx_mini_maps; int /*<<< orphan*/  ti_parent_tag; int /*<<< orphan*/  ti_rx_mini_ring_map; int /*<<< orphan*/  ti_rx_mini_ring_tag; int /*<<< orphan*/  ti_tx_ring_map; int /*<<< orphan*/  ti_tx_ring_tag; TYPE_1__* ti_txdesc; int /*<<< orphan*/  ti_tx_tag; int /*<<< orphan*/  ti_rx_jumbo_sparemap; int /*<<< orphan*/  ti_rx_jumbo_tag; int /*<<< orphan*/ * ti_rx_jumbo_maps; int /*<<< orphan*/  ti_rx_std_sparemap; int /*<<< orphan*/  ti_rx_std_tag; int /*<<< orphan*/ * ti_rx_std_maps; int /*<<< orphan*/  ti_rx_return_ring_map; int /*<<< orphan*/  ti_rx_return_ring_tag; int /*<<< orphan*/  ti_rx_jumbo_ring_map; int /*<<< orphan*/  ti_rx_jumbo_ring_tag; int /*<<< orphan*/  ti_rx_std_ring_map; int /*<<< orphan*/  ti_rx_std_ring_tag; int /*<<< orphan*/  ti_event_ring_map; int /*<<< orphan*/  ti_event_ring_tag; int /*<<< orphan*/  ti_status_map; int /*<<< orphan*/  ti_status_tag; int /*<<< orphan*/  ti_gib_map; int /*<<< orphan*/  ti_gib_tag; } ;
struct TYPE_6__ {int /*<<< orphan*/  ti_rx_mini_ring_paddr; int /*<<< orphan*/  ti_rx_mini_ring; int /*<<< orphan*/  ti_tx_ring_paddr; int /*<<< orphan*/  ti_tx_ring; int /*<<< orphan*/  ti_rx_return_ring_paddr; int /*<<< orphan*/  ti_rx_return_ring; int /*<<< orphan*/  ti_rx_jumbo_ring_paddr; int /*<<< orphan*/  ti_rx_jumbo_ring; int /*<<< orphan*/  ti_rx_std_ring_paddr; int /*<<< orphan*/  ti_rx_std_ring; int /*<<< orphan*/  ti_event_ring_paddr; int /*<<< orphan*/  ti_event_ring; int /*<<< orphan*/  ti_status_paddr; int /*<<< orphan*/  ti_status; int /*<<< orphan*/  ti_info_paddr; int /*<<< orphan*/  ti_info; } ;
struct ti_softc {scalar_t__ ti_dac; scalar_t__ ti_hwrev; int /*<<< orphan*/  ti_dev; TYPE_2__ ti_cdata; TYPE_3__ ti_rdata; } ;
struct ti_gib {int dummy; } ;
typedef  int /*<<< orphan*/  bus_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  tx_dmamap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int BUS_SPACE_MAXSIZE_32BIT ; 
 int ENOMEM ; 
 int MCLBYTES ; 
 int MHLEN ; 
 int MJUM9BYTES ; 
 int PAGE_SIZE ; 
 int TI_EVENT_RING_SZ ; 
 scalar_t__ TI_HWREV_TIGON ; 
 int /*<<< orphan*/  TI_JUMBO_RING_ALIGN ; 
 int TI_JUMBO_RX_RING_CNT ; 
 int TI_JUMBO_RX_RING_SZ ; 
 int TI_MAXTXSEGS ; 
 int TI_MINI_RX_RING_CNT ; 
 int TI_MINI_RX_RING_SZ ; 
 int /*<<< orphan*/  TI_RING_ALIGN ; 
 int TI_RX_RETURN_RING_SZ ; 
 int TI_STD_RX_RING_CNT ; 
 int TI_STD_RX_RING_SZ ; 
 int TI_TX_RING_CNT ; 
 int TI_TX_RING_SZ ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int ti_dma_ring_alloc (struct ti_softc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
ti_dma_alloc(struct ti_softc *sc)
{
	bus_addr_t lowaddr;
	int i, error;

	lowaddr = BUS_SPACE_MAXADDR;
	if (sc->ti_dac == 0)
		lowaddr = BUS_SPACE_MAXADDR_32BIT;

	error = bus_dma_tag_create(bus_get_dma_tag(sc->ti_dev), 1, 0, lowaddr,
	    BUS_SPACE_MAXADDR, NULL, NULL, BUS_SPACE_MAXSIZE_32BIT, 0,
	    BUS_SPACE_MAXSIZE_32BIT, 0, NULL, NULL,
	    &sc->ti_cdata.ti_parent_tag);
	if (error != 0) {
		device_printf(sc->ti_dev,
		    "could not allocate parent dma tag\n");
		return (ENOMEM);
	}

	error = ti_dma_ring_alloc(sc, TI_RING_ALIGN, sizeof(struct ti_gib),
	    &sc->ti_cdata.ti_gib_tag, (uint8_t **)&sc->ti_rdata.ti_info,
	    &sc->ti_cdata.ti_gib_map, &sc->ti_rdata.ti_info_paddr, "GIB");
	if (error)
		return (error);

	/* Producer/consumer status */
	error = ti_dma_ring_alloc(sc, TI_RING_ALIGN, sizeof(struct ti_status),
	    &sc->ti_cdata.ti_status_tag, (uint8_t **)&sc->ti_rdata.ti_status,
	    &sc->ti_cdata.ti_status_map, &sc->ti_rdata.ti_status_paddr,
	    "event ring");
	if (error)
		return (error);

	/* Event ring */
	error = ti_dma_ring_alloc(sc, TI_RING_ALIGN, TI_EVENT_RING_SZ,
	    &sc->ti_cdata.ti_event_ring_tag,
	    (uint8_t **)&sc->ti_rdata.ti_event_ring,
	    &sc->ti_cdata.ti_event_ring_map, &sc->ti_rdata.ti_event_ring_paddr,
	    "event ring");
	if (error)
		return (error);

	/* Command ring lives in shared memory so no need to create DMA area. */

	/* Standard RX ring */
	error = ti_dma_ring_alloc(sc, TI_RING_ALIGN, TI_STD_RX_RING_SZ,
	    &sc->ti_cdata.ti_rx_std_ring_tag,
	    (uint8_t **)&sc->ti_rdata.ti_rx_std_ring,
	    &sc->ti_cdata.ti_rx_std_ring_map,
	    &sc->ti_rdata.ti_rx_std_ring_paddr, "RX ring");
	if (error)
		return (error);

	/* Jumbo RX ring */
	error = ti_dma_ring_alloc(sc, TI_JUMBO_RING_ALIGN, TI_JUMBO_RX_RING_SZ,
	    &sc->ti_cdata.ti_rx_jumbo_ring_tag,
	    (uint8_t **)&sc->ti_rdata.ti_rx_jumbo_ring,
	    &sc->ti_cdata.ti_rx_jumbo_ring_map,
	    &sc->ti_rdata.ti_rx_jumbo_ring_paddr, "jumbo RX ring");
	if (error)
		return (error);

	/* RX return ring */
	error = ti_dma_ring_alloc(sc, TI_RING_ALIGN, TI_RX_RETURN_RING_SZ,
	    &sc->ti_cdata.ti_rx_return_ring_tag,
	    (uint8_t **)&sc->ti_rdata.ti_rx_return_ring,
	    &sc->ti_cdata.ti_rx_return_ring_map,
	    &sc->ti_rdata.ti_rx_return_ring_paddr, "RX return ring");
	if (error)
		return (error);

	/* Create DMA tag for standard RX mbufs. */
	error = bus_dma_tag_create(sc->ti_cdata.ti_parent_tag, 1, 0,
	    BUS_SPACE_MAXADDR, BUS_SPACE_MAXADDR, NULL, NULL, MCLBYTES, 1,
	    MCLBYTES, 0, NULL, NULL, &sc->ti_cdata.ti_rx_std_tag);
	if (error) {
		device_printf(sc->ti_dev, "could not allocate RX dma tag\n");
		return (error);
	}

	/* Create DMA tag for jumbo RX mbufs. */
#ifdef TI_SF_BUF_JUMBO
	/*
	 * The VM system will take care of providing aligned pages.  Alignment
	 * is set to 1 here so that busdma resources won't be wasted.
	 */
	error = bus_dma_tag_create(sc->ti_cdata.ti_parent_tag, 1, 0,
	    BUS_SPACE_MAXADDR, BUS_SPACE_MAXADDR, NULL, NULL, PAGE_SIZE * 4, 4,
	    PAGE_SIZE, 0, NULL, NULL, &sc->ti_cdata.ti_rx_jumbo_tag);
#else
	error = bus_dma_tag_create(sc->ti_cdata.ti_parent_tag, 1, 0,
	    BUS_SPACE_MAXADDR, BUS_SPACE_MAXADDR, NULL, NULL, MJUM9BYTES, 1,
	    MJUM9BYTES, 0, NULL, NULL, &sc->ti_cdata.ti_rx_jumbo_tag);
#endif
	if (error) {
		device_printf(sc->ti_dev,
		    "could not allocate jumbo RX dma tag\n");
		return (error);
	}

	/* Create DMA tag for TX mbufs. */
	error = bus_dma_tag_create(sc->ti_cdata.ti_parent_tag, 1,
	    0, BUS_SPACE_MAXADDR, BUS_SPACE_MAXADDR, NULL, NULL,
	    MCLBYTES * TI_MAXTXSEGS, TI_MAXTXSEGS, MCLBYTES, 0, NULL, NULL,
	    &sc->ti_cdata.ti_tx_tag);
	if (error) {
		device_printf(sc->ti_dev, "could not allocate TX dma tag\n");
		return (ENOMEM);
	}

	/* Create DMA maps for RX buffers. */
	for (i = 0; i < TI_STD_RX_RING_CNT; i++) {
		error = bus_dmamap_create(sc->ti_cdata.ti_rx_std_tag, 0,
		    &sc->ti_cdata.ti_rx_std_maps[i]);
		if (error) {
			device_printf(sc->ti_dev,
			    "could not create DMA map for RX\n");
			return (error);
		}
	}
	error = bus_dmamap_create(sc->ti_cdata.ti_rx_std_tag, 0,
	    &sc->ti_cdata.ti_rx_std_sparemap);
	if (error) {
		device_printf(sc->ti_dev,
		    "could not create spare DMA map for RX\n");
		return (error);
	}

	/* Create DMA maps for jumbo RX buffers. */
	for (i = 0; i < TI_JUMBO_RX_RING_CNT; i++) {
		error = bus_dmamap_create(sc->ti_cdata.ti_rx_jumbo_tag, 0,
		    &sc->ti_cdata.ti_rx_jumbo_maps[i]);
		if (error) {
			device_printf(sc->ti_dev,
			    "could not create DMA map for jumbo RX\n");
			return (error);
		}
	}
	error = bus_dmamap_create(sc->ti_cdata.ti_rx_jumbo_tag, 0,
	    &sc->ti_cdata.ti_rx_jumbo_sparemap);
	if (error) {
		device_printf(sc->ti_dev,
		    "could not create spare DMA map for jumbo RX\n");
		return (error);
	}

	/* Create DMA maps for TX buffers. */
	for (i = 0; i < TI_TX_RING_CNT; i++) {
		error = bus_dmamap_create(sc->ti_cdata.ti_tx_tag, 0,
		    &sc->ti_cdata.ti_txdesc[i].tx_dmamap);
		if (error) {
			device_printf(sc->ti_dev,
			    "could not create DMA map for TX\n");
			return (ENOMEM);
		}
	}

	/* Mini ring and TX ring is not available on Tigon 1. */
	if (sc->ti_hwrev == TI_HWREV_TIGON)
		return (0);

	/* TX ring */
	error = ti_dma_ring_alloc(sc, TI_RING_ALIGN, TI_TX_RING_SZ,
	    &sc->ti_cdata.ti_tx_ring_tag, (uint8_t **)&sc->ti_rdata.ti_tx_ring,
	    &sc->ti_cdata.ti_tx_ring_map, &sc->ti_rdata.ti_tx_ring_paddr,
	    "TX ring");
	if (error)
		return (error);

	/* Mini RX ring */
	error = ti_dma_ring_alloc(sc, TI_RING_ALIGN, TI_MINI_RX_RING_SZ,
	    &sc->ti_cdata.ti_rx_mini_ring_tag,
	    (uint8_t **)&sc->ti_rdata.ti_rx_mini_ring,
	    &sc->ti_cdata.ti_rx_mini_ring_map,
	    &sc->ti_rdata.ti_rx_mini_ring_paddr, "mini RX ring");
	if (error)
		return (error);

	/* Create DMA tag for mini RX mbufs. */
	error = bus_dma_tag_create(sc->ti_cdata.ti_parent_tag, 1, 0,
	    BUS_SPACE_MAXADDR, BUS_SPACE_MAXADDR, NULL, NULL, MHLEN, 1,
	    MHLEN, 0, NULL, NULL, &sc->ti_cdata.ti_rx_mini_tag);
	if (error) {
		device_printf(sc->ti_dev,
		    "could not allocate mini RX dma tag\n");
		return (error);
	}

	/* Create DMA maps for mini RX buffers. */
	for (i = 0; i < TI_MINI_RX_RING_CNT; i++) {
		error = bus_dmamap_create(sc->ti_cdata.ti_rx_mini_tag, 0,
		    &sc->ti_cdata.ti_rx_mini_maps[i]);
		if (error) {
			device_printf(sc->ti_dev,
			    "could not create DMA map for mini RX\n");
			return (error);
		}
	}
	error = bus_dmamap_create(sc->ti_cdata.ti_rx_mini_tag, 0,
	    &sc->ti_cdata.ti_rx_mini_sparemap);
	if (error) {
		device_printf(sc->ti_dev,
		    "could not create spare DMA map for mini RX\n");
		return (error);
	}

	return (0);
}