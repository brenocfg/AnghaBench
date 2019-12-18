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
struct mge_softc {int /*<<< orphan*/  mge_desc_dtag; int /*<<< orphan*/  mge_rx_dtag; int /*<<< orphan*/  mge_tx_dtag; int /*<<< orphan*/  mge_tx_desc; int /*<<< orphan*/  mge_rx_desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  MGE_RX_DESC_NUM ; 
 int /*<<< orphan*/  MGE_TX_DESC_NUM ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mge_free_desc (struct mge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mge_free_dma(struct mge_softc *sc)
{

	/* Free desciptors and mbufs */
	mge_free_desc(sc, sc->mge_rx_desc, MGE_RX_DESC_NUM, sc->mge_rx_dtag, 1);
	mge_free_desc(sc, sc->mge_tx_desc, MGE_TX_DESC_NUM, sc->mge_tx_dtag, 0);

	/* Destroy mbuf dma tag */
	bus_dma_tag_destroy(sc->mge_tx_dtag);
	bus_dma_tag_destroy(sc->mge_rx_dtag);
	/* Destroy descriptors tag */
	bus_dma_tag_destroy(sc->mge_desc_dtag);
}