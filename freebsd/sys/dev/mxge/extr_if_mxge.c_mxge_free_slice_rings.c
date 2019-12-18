#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int mask; TYPE_5__* info; int /*<<< orphan*/ * dmat; int /*<<< orphan*/  extra_map; TYPE_5__* shadow; } ;
struct TYPE_8__ {int mask; TYPE_5__* info; int /*<<< orphan*/ * dmat; int /*<<< orphan*/  extra_map; TYPE_5__* shadow; } ;
struct TYPE_7__ {int mask; TYPE_5__* info; int /*<<< orphan*/ * dmat; TYPE_5__* seg_list; TYPE_5__* req_bytes; } ;
struct TYPE_6__ {int /*<<< orphan*/ * entry; int /*<<< orphan*/  dma; } ;
struct mxge_slice_state {TYPE_4__ rx_big; TYPE_3__ rx_small; TYPE_2__ tx; TYPE_1__ rx_done; } ;
struct TYPE_10__ {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxge_dma_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mxge_free_slice_rings(struct mxge_slice_state *ss)
{
	int i;


	if (ss->rx_done.entry != NULL)
		mxge_dma_free(&ss->rx_done.dma);
	ss->rx_done.entry = NULL;

	if (ss->tx.req_bytes != NULL)
		free(ss->tx.req_bytes, M_DEVBUF);
	ss->tx.req_bytes = NULL;

	if (ss->tx.seg_list != NULL)
		free(ss->tx.seg_list, M_DEVBUF);
	ss->tx.seg_list = NULL;

	if (ss->rx_small.shadow != NULL)
		free(ss->rx_small.shadow, M_DEVBUF);
	ss->rx_small.shadow = NULL;

	if (ss->rx_big.shadow != NULL)
		free(ss->rx_big.shadow, M_DEVBUF);
	ss->rx_big.shadow = NULL;

	if (ss->tx.info != NULL) {
		if (ss->tx.dmat != NULL) {
			for (i = 0; i <= ss->tx.mask; i++) {
				bus_dmamap_destroy(ss->tx.dmat,
						   ss->tx.info[i].map);
			}
			bus_dma_tag_destroy(ss->tx.dmat);
		}
		free(ss->tx.info, M_DEVBUF);
	}
	ss->tx.info = NULL;

	if (ss->rx_small.info != NULL) {
		if (ss->rx_small.dmat != NULL) {
			for (i = 0; i <= ss->rx_small.mask; i++) {
				bus_dmamap_destroy(ss->rx_small.dmat,
						   ss->rx_small.info[i].map);
			}
			bus_dmamap_destroy(ss->rx_small.dmat,
					   ss->rx_small.extra_map);
			bus_dma_tag_destroy(ss->rx_small.dmat);
		}
		free(ss->rx_small.info, M_DEVBUF);
	}
	ss->rx_small.info = NULL;

	if (ss->rx_big.info != NULL) {
		if (ss->rx_big.dmat != NULL) {
			for (i = 0; i <= ss->rx_big.mask; i++) {
				bus_dmamap_destroy(ss->rx_big.dmat,
						   ss->rx_big.info[i].map);
			}
			bus_dmamap_destroy(ss->rx_big.dmat,
					   ss->rx_big.extra_map);
			bus_dma_tag_destroy(ss->rx_big.dmat);
		}
		free(ss->rx_big.info, M_DEVBUF);
	}
	ss->rx_big.info = NULL;
}