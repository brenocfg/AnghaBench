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
struct oce_wq {int /*<<< orphan*/  tx_compl_lock; int /*<<< orphan*/  tx_lock; int /*<<< orphan*/ * br; int /*<<< orphan*/ * tag; TYPE_1__* pckts; int /*<<< orphan*/ * ring; int /*<<< orphan*/  txtask; int /*<<< orphan*/  parent; } ;
struct TYPE_2__ {int /*<<< orphan*/ * map; } ;
typedef  int /*<<< orphan*/  POCE_SOFTC ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK_DESTROY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int OCE_WQ_PACKET_ARRAY_SIZE ; 
 int /*<<< orphan*/  buf_ring_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct oce_wq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oce_destroy_ring_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_swi ; 

__attribute__((used)) static void
oce_wq_free(struct oce_wq *wq)
{
	POCE_SOFTC sc = (POCE_SOFTC) wq->parent;
	int i;

	taskqueue_drain(taskqueue_swi, &wq->txtask);

	if (wq->ring != NULL) {
		oce_destroy_ring_buffer(sc, wq->ring);
		wq->ring = NULL;
	}

	for (i = 0; i < OCE_WQ_PACKET_ARRAY_SIZE; i++) {
		if (wq->pckts[i].map != NULL) {
			bus_dmamap_unload(wq->tag, wq->pckts[i].map);
			bus_dmamap_destroy(wq->tag, wq->pckts[i].map);
			wq->pckts[i].map = NULL;
		}
	}

	if (wq->tag != NULL)
		bus_dma_tag_destroy(wq->tag);
	if (wq->br != NULL)
		buf_ring_free(wq->br, M_DEVBUF);

	LOCK_DESTROY(&wq->tx_lock);
	LOCK_DESTROY(&wq->tx_compl_lock);
	free(wq, M_DEVBUF);
}