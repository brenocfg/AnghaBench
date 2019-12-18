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
struct oce_rq {int /*<<< orphan*/  rx_lock; int /*<<< orphan*/ * tag; TYPE_1__* pckts; int /*<<< orphan*/ * ring; int /*<<< orphan*/  parent; } ;
struct TYPE_2__ {int /*<<< orphan*/ * mbuf; int /*<<< orphan*/ * map; } ;
typedef  int /*<<< orphan*/  POCE_SOFTC ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK_DESTROY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int OCE_RQ_PACKET_ARRAY_SIZE ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct oce_rq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oce_destroy_ring_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
oce_rq_free(struct oce_rq *rq)
{
	POCE_SOFTC sc = (POCE_SOFTC) rq->parent;
	int i = 0 ;

	if (rq->ring != NULL) {
		oce_destroy_ring_buffer(sc, rq->ring);
		rq->ring = NULL;
	}
	for (i = 0; i < OCE_RQ_PACKET_ARRAY_SIZE; i++) {
		if (rq->pckts[i].map != NULL) {
			bus_dmamap_unload(rq->tag, rq->pckts[i].map);
			bus_dmamap_destroy(rq->tag, rq->pckts[i].map);
			rq->pckts[i].map = NULL;
		}
		if (rq->pckts[i].mbuf) {
			m_free(rq->pckts[i].mbuf);
			rq->pckts[i].mbuf = NULL;
		}
	}

	if (rq->tag != NULL)
		bus_dma_tag_destroy(rq->tag);

	LOCK_DESTROY(&rq->rx_lock);
	free(rq, M_DEVBUF);
}