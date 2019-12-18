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
struct mge_softc {struct mge_desc_wrapper* mge_rx_desc; int /*<<< orphan*/  rx_desc_start; struct mge_desc_wrapper* mge_tx_desc; int /*<<< orphan*/  tx_desc_start; int /*<<< orphan*/  mge_rx_dtag; int /*<<< orphan*/  mge_tx_dtag; int /*<<< orphan*/  mge_desc_dtag; int /*<<< orphan*/  dev; } ;
struct mge_desc_wrapper {int /*<<< orphan*/  mge_desc_paddr; TYPE_1__* mge_desc; int /*<<< orphan*/  buffer; int /*<<< orphan*/  buffer_dmap; } ;
struct mge_desc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int MGE_RX_DESC_NUM ; 
 int MGE_TX_DESC_NUM ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mge_alloc_desc_dma (struct mge_softc*,struct mge_desc_wrapper*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mge_new_rxbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mge_allocate_dma(struct mge_softc *sc)
{
	int error;
	struct mge_desc_wrapper *dw;
	int i;

	/* Allocate a busdma tag and DMA safe memory for TX/RX descriptors. */
	error = bus_dma_tag_create(bus_get_dma_tag(sc->dev),	/* parent */
	    16, 0,				/* alignment, boundary */
	    BUS_SPACE_MAXADDR_32BIT,		/* lowaddr */
	    BUS_SPACE_MAXADDR,			/* highaddr */
	    NULL, NULL,				/* filtfunc, filtfuncarg */
	    sizeof(struct mge_desc), 1,		/* maxsize, nsegments */
	    sizeof(struct mge_desc), 0,		/* maxsegsz, flags */
	    NULL, NULL,				/* lockfunc, lockfuncarg */
	    &sc->mge_desc_dtag);		/* dmat */


	mge_alloc_desc_dma(sc, sc->mge_tx_desc, MGE_TX_DESC_NUM,
	    &sc->mge_tx_dtag);
	mge_alloc_desc_dma(sc, sc->mge_rx_desc, MGE_RX_DESC_NUM,
	    &sc->mge_rx_dtag);

	for (i = 0; i < MGE_RX_DESC_NUM; i++) {
		dw = &(sc->mge_rx_desc[i]);
		mge_new_rxbuf(sc->mge_rx_dtag, dw->buffer_dmap, &dw->buffer,
		    &dw->mge_desc->buffer);
	}

	sc->tx_desc_start = sc->mge_tx_desc[0].mge_desc_paddr;
	sc->rx_desc_start = sc->mge_rx_desc[0].mge_desc_paddr;

	return (0);
}