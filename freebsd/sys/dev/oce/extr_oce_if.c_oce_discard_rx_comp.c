#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct oce_rq {int /*<<< orphan*/  pending; TYPE_2__* ring; int /*<<< orphan*/  tag; struct oce_packet_desc* pckts; int /*<<< orphan*/  parent; } ;
struct oce_packet_desc {int /*<<< orphan*/ * mbuf; int /*<<< orphan*/  map; } ;
struct TYPE_4__ {size_t cidx; size_t pidx; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__* POCE_SOFTC ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  RING_GET (TYPE_2__*,int) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

void
oce_discard_rx_comp(struct oce_rq *rq, int num_frags)
{
	uint32_t i = 0;
	struct oce_packet_desc *pd;
	POCE_SOFTC sc = (POCE_SOFTC) rq->parent;

	for (i = 0; i < num_frags; i++) {
                if (rq->ring->cidx == rq->ring->pidx) {
                        device_printf(sc->dev,
                                "oce_discard_rx_comp: Invalid RX completion - Queue is empty\n");
                        return;
                }
                pd = &rq->pckts[rq->ring->cidx];
                bus_dmamap_sync(rq->tag, pd->map, BUS_DMASYNC_POSTWRITE);
                bus_dmamap_unload(rq->tag, pd->map);
                if (pd->mbuf != NULL) {
                        m_freem(pd->mbuf);
                        pd->mbuf = NULL;
                }

		RING_GET(rq->ring, 1);
                rq->pending--;
	}
}