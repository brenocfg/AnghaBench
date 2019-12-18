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
struct tx_ring {struct ixl_tx_queue* tx_rsq; } ;
struct ixl_vsi {struct ixl_tx_queue* rx_queues; struct ixl_tx_queue* tx_queues; TYPE_1__* shared; int /*<<< orphan*/  enable_head_writeback; } ;
struct ixl_tx_queue {struct tx_ring txr; } ;
struct iavf_sc {struct ixl_vsi vsi; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;
struct TYPE_2__ {int isc_ntxqsets; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_IAVF ; 
 int /*<<< orphan*/  free (struct ixl_tx_queue*,int /*<<< orphan*/ ) ; 
 struct iavf_sc* iflib_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
iavf_if_queues_free(if_ctx_t ctx)
{
	struct iavf_sc *sc = iflib_get_softc(ctx);
	struct ixl_vsi *vsi = &sc->vsi;

	if (!vsi->enable_head_writeback) {
		struct ixl_tx_queue *que;
		int i = 0;

		for (i = 0, que = vsi->tx_queues; i < vsi->shared->isc_ntxqsets; i++, que++) {
			struct tx_ring *txr = &que->txr;
			if (txr->tx_rsq != NULL) {
				free(txr->tx_rsq, M_IAVF);
				txr->tx_rsq = NULL;
			}
		}
	}

	if (vsi->tx_queues != NULL) {
		free(vsi->tx_queues, M_IAVF);
		vsi->tx_queues = NULL;
	}
	if (vsi->rx_queues != NULL) {
		free(vsi->rx_queues, M_IAVF);
		vsi->rx_queues = NULL;
	}
}