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
struct bnxt_softc {int /*<<< orphan*/ * rx_cp_rings; int /*<<< orphan*/ * rx_rings; int /*<<< orphan*/ * ag_rings; int /*<<< orphan*/ * grp_info; int /*<<< orphan*/  hw_rx_port_stats; int /*<<< orphan*/  hw_tx_port_stats; int /*<<< orphan*/  rx_stats; scalar_t__ ntxqsets; int /*<<< orphan*/ * tx_cp_rings; int /*<<< orphan*/ * tx_rings; int /*<<< orphan*/  tx_stats; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_dma_free (int /*<<< orphan*/ *) ; 
 struct bnxt_softc* iflib_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bnxt_queues_free(if_ctx_t ctx)
{
	struct bnxt_softc *softc = iflib_get_softc(ctx);

	// Free TX queues
	iflib_dma_free(&softc->tx_stats);
	free(softc->tx_rings, M_DEVBUF);
	softc->tx_rings = NULL;
	free(softc->tx_cp_rings, M_DEVBUF);
	softc->tx_cp_rings = NULL;
	softc->ntxqsets = 0;

	// Free RX queues
	iflib_dma_free(&softc->rx_stats);
	iflib_dma_free(&softc->hw_tx_port_stats);
	iflib_dma_free(&softc->hw_rx_port_stats);
	free(softc->grp_info, M_DEVBUF);
	free(softc->ag_rings, M_DEVBUF);
	free(softc->rx_rings, M_DEVBUF);
	free(softc->rx_cp_rings, M_DEVBUF);
}