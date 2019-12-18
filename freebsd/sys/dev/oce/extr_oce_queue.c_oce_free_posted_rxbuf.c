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
struct oce_rq {scalar_t__ pending; TYPE_1__* ring; int /*<<< orphan*/  tag; struct oce_packet_desc* pckts; } ;
struct oce_packet_desc {int /*<<< orphan*/ * mbuf; int /*<<< orphan*/  map; } ;
struct TYPE_2__ {size_t cidx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  RING_GET (TYPE_1__*,int) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

void
oce_free_posted_rxbuf(struct oce_rq *rq)
{
	struct oce_packet_desc *pd;
	
	while (rq->pending) {

		pd = &rq->pckts[rq->ring->cidx];
		bus_dmamap_sync(rq->tag, pd->map, BUS_DMASYNC_POSTWRITE);
		bus_dmamap_unload(rq->tag, pd->map);
		if (pd->mbuf != NULL) {
			m_freem(pd->mbuf);
			pd->mbuf = NULL;
		}

		RING_GET(rq->ring,1);
                rq->pending--;
	}

}