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
struct TYPE_2__ {scalar_t__ rl_rx_buf_paddr; int /*<<< orphan*/ * rl_tx_tag; int /*<<< orphan*/ ** rl_tx_dmamap; int /*<<< orphan*/ * rl_rx_tag; int /*<<< orphan*/ * rl_rx_buf; int /*<<< orphan*/ * rl_rx_buf_ptr; int /*<<< orphan*/  rl_rx_dmamap; } ;
struct rl_softc {int /*<<< orphan*/ * rl_parent_tag; TYPE_1__ rl_cdata; } ;

/* Variables and functions */
 int RL_TX_LIST_CNT ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rl_dma_free(struct rl_softc *sc)
{
	int			i;

	/* Rx memory block. */
	if (sc->rl_cdata.rl_rx_tag != NULL) {
		if (sc->rl_cdata.rl_rx_buf_paddr != 0)
			bus_dmamap_unload(sc->rl_cdata.rl_rx_tag,
			    sc->rl_cdata.rl_rx_dmamap);
		if (sc->rl_cdata.rl_rx_buf_ptr != NULL)
			bus_dmamem_free(sc->rl_cdata.rl_rx_tag,
			    sc->rl_cdata.rl_rx_buf_ptr,
			    sc->rl_cdata.rl_rx_dmamap);
		sc->rl_cdata.rl_rx_buf_ptr = NULL;
		sc->rl_cdata.rl_rx_buf = NULL;
		sc->rl_cdata.rl_rx_buf_paddr = 0;
		bus_dma_tag_destroy(sc->rl_cdata.rl_rx_tag);
		sc->rl_cdata.rl_tx_tag = NULL;
	}

	/* Tx buffers. */
	if (sc->rl_cdata.rl_tx_tag != NULL) {
		for (i = 0; i < RL_TX_LIST_CNT; i++) {
			if (sc->rl_cdata.rl_tx_dmamap[i] != NULL) {
				bus_dmamap_destroy(
				    sc->rl_cdata.rl_tx_tag,
				    sc->rl_cdata.rl_tx_dmamap[i]);
				sc->rl_cdata.rl_tx_dmamap[i] = NULL;
			}
		}
		bus_dma_tag_destroy(sc->rl_cdata.rl_tx_tag);
		sc->rl_cdata.rl_tx_tag = NULL;
	}

	if (sc->rl_parent_tag != NULL) {
		bus_dma_tag_destroy(sc->rl_parent_tag);
		sc->rl_parent_tag = NULL;
	}
}