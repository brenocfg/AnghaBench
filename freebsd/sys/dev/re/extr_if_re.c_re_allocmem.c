#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct rl_stats {int dummy; } ;
struct TYPE_8__ {int rl_rx_desc_cnt; int rl_tx_desc_cnt; scalar_t__ rl_tx_list_addr; scalar_t__ rl_rx_list_addr; scalar_t__ rl_stats_addr; int /*<<< orphan*/  rl_stats; int /*<<< orphan*/  rl_smap; int /*<<< orphan*/  rl_stag; TYPE_3__* rl_rx_desc; int /*<<< orphan*/  rl_rx_mtag; int /*<<< orphan*/  rl_rx_sparemap; TYPE_2__* rl_jrx_desc; int /*<<< orphan*/  rl_jrx_mtag; int /*<<< orphan*/  rl_jrx_sparemap; int /*<<< orphan*/  rl_rx_list; int /*<<< orphan*/  rl_rx_list_map; int /*<<< orphan*/  rl_rx_list_tag; TYPE_1__* rl_tx_desc; int /*<<< orphan*/  rl_tx_mtag; int /*<<< orphan*/  rl_tx_list; int /*<<< orphan*/  rl_tx_list_map; int /*<<< orphan*/  rl_tx_list_tag; } ;
struct rl_softc {int rl_flags; TYPE_4__ rl_ldata; int /*<<< orphan*/  rl_parent_tag; } ;
struct rl_desc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int bus_size_t ;
typedef  int /*<<< orphan*/  bus_addr_t ;
struct TYPE_7__ {int /*<<< orphan*/  rx_dmamap; } ;
struct TYPE_6__ {int /*<<< orphan*/  rx_dmamap; } ;
struct TYPE_5__ {int /*<<< orphan*/  tx_dmamap; } ;

/* Variables and functions */
 int BUS_DMA_COHERENT ; 
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int BUS_DMA_WAITOK ; 
 int BUS_DMA_ZERO ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int BUS_SPACE_MAXSIZE_32BIT ; 
 int ENOMEM ; 
 int MCLBYTES ; 
 int MJUM9BYTES ; 
 int RL_DUMP_ALIGN ; 
 int RL_FLAG_JUMBOV2 ; 
 int RL_FLAG_PCIE ; 
 int RL_NTXSEGS ; 
 int RL_RING_ALIGN ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  re_dma_map_addr ; 

__attribute__((used)) static int
re_allocmem(device_t dev, struct rl_softc *sc)
{
	bus_addr_t		lowaddr;
	bus_size_t		rx_list_size, tx_list_size;
	int			error;
	int			i;

	rx_list_size = sc->rl_ldata.rl_rx_desc_cnt * sizeof(struct rl_desc);
	tx_list_size = sc->rl_ldata.rl_tx_desc_cnt * sizeof(struct rl_desc);

	/*
	 * Allocate the parent bus DMA tag appropriate for PCI.
	 * In order to use DAC, RL_CPLUSCMD_PCI_DAC bit of RL_CPLUS_CMD
	 * register should be set. However some RealTek chips are known
	 * to be buggy on DAC handling, therefore disable DAC by limiting
	 * DMA address space to 32bit. PCIe variants of RealTek chips
	 * may not have the limitation.
	 */
	lowaddr = BUS_SPACE_MAXADDR;
	if ((sc->rl_flags & RL_FLAG_PCIE) == 0)
		lowaddr = BUS_SPACE_MAXADDR_32BIT;
	error = bus_dma_tag_create(bus_get_dma_tag(dev), 1, 0,
	    lowaddr, BUS_SPACE_MAXADDR, NULL, NULL,
	    BUS_SPACE_MAXSIZE_32BIT, 0, BUS_SPACE_MAXSIZE_32BIT, 0,
	    NULL, NULL, &sc->rl_parent_tag);
	if (error) {
		device_printf(dev, "could not allocate parent DMA tag\n");
		return (error);
	}

	/*
	 * Allocate map for TX mbufs.
	 */
	error = bus_dma_tag_create(sc->rl_parent_tag, 1, 0,
	    BUS_SPACE_MAXADDR, BUS_SPACE_MAXADDR, NULL,
	    NULL, MCLBYTES * RL_NTXSEGS, RL_NTXSEGS, 4096, 0,
	    NULL, NULL, &sc->rl_ldata.rl_tx_mtag);
	if (error) {
		device_printf(dev, "could not allocate TX DMA tag\n");
		return (error);
	}

	/*
	 * Allocate map for RX mbufs.
	 */

	if ((sc->rl_flags & RL_FLAG_JUMBOV2) != 0) {
		error = bus_dma_tag_create(sc->rl_parent_tag, sizeof(uint64_t),
		    0, BUS_SPACE_MAXADDR, BUS_SPACE_MAXADDR, NULL, NULL,
		    MJUM9BYTES, 1, MJUM9BYTES, 0, NULL, NULL,
		    &sc->rl_ldata.rl_jrx_mtag);
		if (error) {
			device_printf(dev,
			    "could not allocate jumbo RX DMA tag\n");
			return (error);
		}
	}
	error = bus_dma_tag_create(sc->rl_parent_tag, sizeof(uint64_t), 0,
	    BUS_SPACE_MAXADDR, BUS_SPACE_MAXADDR, NULL, NULL,
	    MCLBYTES, 1, MCLBYTES, 0, NULL, NULL, &sc->rl_ldata.rl_rx_mtag);
	if (error) {
		device_printf(dev, "could not allocate RX DMA tag\n");
		return (error);
	}

	/*
	 * Allocate map for TX descriptor list.
	 */
	error = bus_dma_tag_create(sc->rl_parent_tag, RL_RING_ALIGN,
	    0, BUS_SPACE_MAXADDR_32BIT, BUS_SPACE_MAXADDR, NULL,
	    NULL, tx_list_size, 1, tx_list_size, 0,
	    NULL, NULL, &sc->rl_ldata.rl_tx_list_tag);
	if (error) {
		device_printf(dev, "could not allocate TX DMA ring tag\n");
		return (error);
	}

	/* Allocate DMA'able memory for the TX ring */

	error = bus_dmamem_alloc(sc->rl_ldata.rl_tx_list_tag,
	    (void **)&sc->rl_ldata.rl_tx_list,
	    BUS_DMA_WAITOK | BUS_DMA_COHERENT | BUS_DMA_ZERO,
	    &sc->rl_ldata.rl_tx_list_map);
	if (error) {
		device_printf(dev, "could not allocate TX DMA ring\n");
		return (error);
	}

	/* Load the map for the TX ring. */

	sc->rl_ldata.rl_tx_list_addr = 0;
	error = bus_dmamap_load(sc->rl_ldata.rl_tx_list_tag,
	     sc->rl_ldata.rl_tx_list_map, sc->rl_ldata.rl_tx_list,
	     tx_list_size, re_dma_map_addr,
	     &sc->rl_ldata.rl_tx_list_addr, BUS_DMA_NOWAIT);
	if (error != 0 || sc->rl_ldata.rl_tx_list_addr == 0) {
		device_printf(dev, "could not load TX DMA ring\n");
		return (ENOMEM);
	}

	/* Create DMA maps for TX buffers */

	for (i = 0; i < sc->rl_ldata.rl_tx_desc_cnt; i++) {
		error = bus_dmamap_create(sc->rl_ldata.rl_tx_mtag, 0,
		    &sc->rl_ldata.rl_tx_desc[i].tx_dmamap);
		if (error) {
			device_printf(dev, "could not create DMA map for TX\n");
			return (error);
		}
	}

	/*
	 * Allocate map for RX descriptor list.
	 */
	error = bus_dma_tag_create(sc->rl_parent_tag, RL_RING_ALIGN,
	    0, BUS_SPACE_MAXADDR_32BIT, BUS_SPACE_MAXADDR, NULL,
	    NULL, rx_list_size, 1, rx_list_size, 0,
	    NULL, NULL, &sc->rl_ldata.rl_rx_list_tag);
	if (error) {
		device_printf(dev, "could not create RX DMA ring tag\n");
		return (error);
	}

	/* Allocate DMA'able memory for the RX ring */

	error = bus_dmamem_alloc(sc->rl_ldata.rl_rx_list_tag,
	    (void **)&sc->rl_ldata.rl_rx_list,
	    BUS_DMA_WAITOK | BUS_DMA_COHERENT | BUS_DMA_ZERO,
	    &sc->rl_ldata.rl_rx_list_map);
	if (error) {
		device_printf(dev, "could not allocate RX DMA ring\n");
		return (error);
	}

	/* Load the map for the RX ring. */

	sc->rl_ldata.rl_rx_list_addr = 0;
	error = bus_dmamap_load(sc->rl_ldata.rl_rx_list_tag,
	     sc->rl_ldata.rl_rx_list_map, sc->rl_ldata.rl_rx_list,
	     rx_list_size, re_dma_map_addr,
	     &sc->rl_ldata.rl_rx_list_addr, BUS_DMA_NOWAIT);
	if (error != 0 || sc->rl_ldata.rl_rx_list_addr == 0) {
		device_printf(dev, "could not load RX DMA ring\n");
		return (ENOMEM);
	}

	/* Create DMA maps for RX buffers */

	if ((sc->rl_flags & RL_FLAG_JUMBOV2) != 0) {
		error = bus_dmamap_create(sc->rl_ldata.rl_jrx_mtag, 0,
		    &sc->rl_ldata.rl_jrx_sparemap);
		if (error) {
			device_printf(dev,
			    "could not create spare DMA map for jumbo RX\n");
			return (error);
		}
		for (i = 0; i < sc->rl_ldata.rl_rx_desc_cnt; i++) {
			error = bus_dmamap_create(sc->rl_ldata.rl_jrx_mtag, 0,
			    &sc->rl_ldata.rl_jrx_desc[i].rx_dmamap);
			if (error) {
				device_printf(dev,
				    "could not create DMA map for jumbo RX\n");
				return (error);
			}
		}
	}
	error = bus_dmamap_create(sc->rl_ldata.rl_rx_mtag, 0,
	    &sc->rl_ldata.rl_rx_sparemap);
	if (error) {
		device_printf(dev, "could not create spare DMA map for RX\n");
		return (error);
	}
	for (i = 0; i < sc->rl_ldata.rl_rx_desc_cnt; i++) {
		error = bus_dmamap_create(sc->rl_ldata.rl_rx_mtag, 0,
		    &sc->rl_ldata.rl_rx_desc[i].rx_dmamap);
		if (error) {
			device_printf(dev, "could not create DMA map for RX\n");
			return (error);
		}
	}

	/* Create DMA map for statistics. */
	error = bus_dma_tag_create(sc->rl_parent_tag, RL_DUMP_ALIGN, 0,
	    BUS_SPACE_MAXADDR, BUS_SPACE_MAXADDR, NULL, NULL,
	    sizeof(struct rl_stats), 1, sizeof(struct rl_stats), 0, NULL, NULL,
	    &sc->rl_ldata.rl_stag);
	if (error) {
		device_printf(dev, "could not create statistics DMA tag\n");
		return (error);
	}
	/* Allocate DMA'able memory for statistics. */
	error = bus_dmamem_alloc(sc->rl_ldata.rl_stag,
	    (void **)&sc->rl_ldata.rl_stats,
	    BUS_DMA_WAITOK | BUS_DMA_COHERENT | BUS_DMA_ZERO,
	    &sc->rl_ldata.rl_smap);
	if (error) {
		device_printf(dev,
		    "could not allocate statistics DMA memory\n");
		return (error);
	}
	/* Load the map for statistics. */
	sc->rl_ldata.rl_stats_addr = 0;
	error = bus_dmamap_load(sc->rl_ldata.rl_stag, sc->rl_ldata.rl_smap,
	    sc->rl_ldata.rl_stats, sizeof(struct rl_stats), re_dma_map_addr,
	     &sc->rl_ldata.rl_stats_addr, BUS_DMA_NOWAIT);
	if (error != 0 || sc->rl_ldata.rl_stats_addr == 0) {
		device_printf(dev, "could not load statistics DMA memory\n");
		return (ENOMEM);
	}

	return (0);
}