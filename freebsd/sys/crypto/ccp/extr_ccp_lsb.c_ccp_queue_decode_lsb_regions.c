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
typedef  int uint64_t ;
struct ccp_softc {struct ccp_queue* queues; } ;
struct ccp_queue {int lsb_mask; } ;

/* Variables and functions */
 int MAX_HW_QUEUES ; 
 unsigned int MAX_LSB_REGIONS ; 

void
ccp_queue_decode_lsb_regions(struct ccp_softc *sc, uint64_t lsbmask,
    unsigned queue)
{
	struct ccp_queue *qp;
	unsigned i;

	qp = &sc->queues[queue];

	qp->lsb_mask = 0;

	for (i = 0; i < MAX_LSB_REGIONS; i++) {
		if (((1 << queue) & lsbmask) != 0)
			qp->lsb_mask |= (1 << i);
		lsbmask >>= MAX_HW_QUEUES;
	}

	/*
	 * Ignore region 0, which has special entries that cannot be used
	 * generally.
	 */
	qp->lsb_mask &= ~(1 << 0);
}