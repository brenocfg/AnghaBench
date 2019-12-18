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
struct tx_ring {struct ixl_tx_queue* tx_rsq; } ;
struct ixl_vsi {int num_tx_queues; struct ixl_tx_queue* rx_queues; struct ixl_tx_queue* tx_queues; int /*<<< orphan*/  enable_head_writeback; } ;
struct ixl_tx_queue {struct tx_ring txr; } ;
struct ixl_pf {struct ixl_vsi vsi; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_IXL ; 
 int /*<<< orphan*/  free (struct ixl_tx_queue*,int /*<<< orphan*/ ) ; 
 struct ixl_pf* iflib_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ixl_if_queues_free(if_ctx_t ctx)
{
	struct ixl_pf *pf = iflib_get_softc(ctx);
	struct ixl_vsi *vsi = &pf->vsi;

	if (!vsi->enable_head_writeback) {
		struct ixl_tx_queue *que;
		int i = 0;

		for (i = 0, que = vsi->tx_queues; i < vsi->num_tx_queues; i++, que++) {
			struct tx_ring *txr = &que->txr;
			if (txr->tx_rsq != NULL) {
				free(txr->tx_rsq, M_IXL);
				txr->tx_rsq = NULL;
			}
		}
	}

	if (vsi->tx_queues != NULL) {
		free(vsi->tx_queues, M_IXL);
		vsi->tx_queues = NULL;
	}
	if (vsi->rx_queues != NULL) {
		free(vsi->rx_queues, M_IXL);
		vsi->rx_queues = NULL;
	}
}