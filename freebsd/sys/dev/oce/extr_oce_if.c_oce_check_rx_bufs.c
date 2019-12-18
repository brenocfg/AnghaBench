#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct oce_rq {int pending; TYPE_1__* cq; } ;
struct TYPE_6__ {int /*<<< orphan*/  enable_hwlro; } ;
struct TYPE_5__ {int /*<<< orphan*/  cq_id; } ;
typedef  TYPE_2__* POCE_SOFTC ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int OCE_RQ_PACKET_ARRAY_SIZE ; 
 int /*<<< orphan*/  oce_alloc_rx_bufs (struct oce_rq*,int) ; 
 int /*<<< orphan*/  oce_arm_cq (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
oce_check_rx_bufs(POCE_SOFTC sc, uint32_t num_cqes, struct oce_rq *rq)
{
        if (num_cqes) {
                oce_arm_cq(sc, rq->cq->cq_id, num_cqes, FALSE);
		if(!sc->enable_hwlro) {
			if((OCE_RQ_PACKET_ARRAY_SIZE - rq->pending) > 1)
				oce_alloc_rx_bufs(rq, ((OCE_RQ_PACKET_ARRAY_SIZE - rq->pending) - 1));
		}else {
                	if ((OCE_RQ_PACKET_ARRAY_SIZE -1 - rq->pending) > 64)
                        	oce_alloc_rx_bufs(rq, 64);
        	}
	}

        return;
}