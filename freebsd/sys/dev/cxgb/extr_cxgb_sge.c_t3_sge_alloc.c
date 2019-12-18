#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  tx_dmat; int /*<<< orphan*/  parent_dmat; int /*<<< orphan*/  rx_jumbo_dmat; int /*<<< orphan*/  rx_dmat; } ;
typedef  TYPE_1__ adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_ALLOCNOW ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int BUS_SPACE_MAXSIZE_32BIT ; 
 int BUS_SPACE_UNRESTRICTED ; 
 int ENOMEM ; 
 int MCLBYTES ; 
 int MJUM16BYTES ; 
 int TX_MAX_SEGS ; 
 int TX_MAX_SIZE ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

int
t3_sge_alloc(adapter_t *sc)
{

	/* The parent tag. */
	if (bus_dma_tag_create( bus_get_dma_tag(sc->dev),/* PCI parent */
				1, 0,			/* algnmnt, boundary */
				BUS_SPACE_MAXADDR,	/* lowaddr */
				BUS_SPACE_MAXADDR,	/* highaddr */
				NULL, NULL,		/* filter, filterarg */
				BUS_SPACE_MAXSIZE_32BIT,/* maxsize */
				BUS_SPACE_UNRESTRICTED, /* nsegments */
				BUS_SPACE_MAXSIZE_32BIT,/* maxsegsize */
				0,			/* flags */
				NULL, NULL,		/* lock, lockarg */
				&sc->parent_dmat)) {
		device_printf(sc->dev, "Cannot allocate parent DMA tag\n");
		return (ENOMEM);
	}

	/*
	 * DMA tag for normal sized RX frames
	 */
	if (bus_dma_tag_create(sc->parent_dmat, MCLBYTES, 0, BUS_SPACE_MAXADDR,
		BUS_SPACE_MAXADDR, NULL, NULL, MCLBYTES, 1,
		MCLBYTES, BUS_DMA_ALLOCNOW, NULL, NULL, &sc->rx_dmat)) {
		device_printf(sc->dev, "Cannot allocate RX DMA tag\n");
		return (ENOMEM);
	}

	/* 
	 * DMA tag for jumbo sized RX frames.
	 */
	if (bus_dma_tag_create(sc->parent_dmat, MJUM16BYTES, 0, BUS_SPACE_MAXADDR,
		BUS_SPACE_MAXADDR, NULL, NULL, MJUM16BYTES, 1, MJUM16BYTES,
		BUS_DMA_ALLOCNOW, NULL, NULL, &sc->rx_jumbo_dmat)) {
		device_printf(sc->dev, "Cannot allocate RX jumbo DMA tag\n");
		return (ENOMEM);
	}

	/* 
	 * DMA tag for TX frames.
	 */
	if (bus_dma_tag_create(sc->parent_dmat, 1, 0, BUS_SPACE_MAXADDR,
		BUS_SPACE_MAXADDR, NULL, NULL, TX_MAX_SIZE, TX_MAX_SEGS,
		TX_MAX_SIZE, BUS_DMA_ALLOCNOW,
		NULL, NULL, &sc->tx_dmat)) {
		device_printf(sc->dev, "Cannot allocate TX DMA tag\n");
		return (ENOMEM);
	}

	return (0);
}