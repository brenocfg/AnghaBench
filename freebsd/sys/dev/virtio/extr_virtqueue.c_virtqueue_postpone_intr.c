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
typedef  int vq_postpone_t ;
typedef  int uint16_t ;
struct TYPE_4__ {TYPE_1__* avail; } ;
struct virtqueue {int vq_used_cons_idx; TYPE_2__ vq_ring; } ;
struct TYPE_3__ {int idx; } ;

/* Variables and functions */
#define  VQ_POSTPONE_EMPTIED 130 
#define  VQ_POSTPONE_LONG 129 
#define  VQ_POSTPONE_SHORT 128 
 int vq_ring_enable_interrupt (struct virtqueue*,int) ; 

int
virtqueue_postpone_intr(struct virtqueue *vq, vq_postpone_t hint)
{
	uint16_t ndesc, avail_idx;

	avail_idx = vq->vq_ring.avail->idx;
	ndesc = (uint16_t)(avail_idx - vq->vq_used_cons_idx);

	switch (hint) {
	case VQ_POSTPONE_SHORT:
		ndesc = ndesc / 4;
		break;
	case VQ_POSTPONE_LONG:
		ndesc = (ndesc * 3) / 4;
		break;
	case VQ_POSTPONE_EMPTIED:
		break;
	}

	return (vq_ring_enable_interrupt(vq, ndesc));
}