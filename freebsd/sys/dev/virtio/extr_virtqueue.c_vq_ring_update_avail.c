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
typedef  size_t uint16_t ;
struct TYPE_3__ {TYPE_2__* avail; } ;
struct virtqueue {int vq_nentries; int /*<<< orphan*/  vq_queued_cnt; TYPE_1__ vq_ring; } ;
struct TYPE_4__ {int idx; size_t* ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void
vq_ring_update_avail(struct virtqueue *vq, uint16_t desc_idx)
{
	uint16_t avail_idx;

	/*
	 * Place the head of the descriptor chain into the next slot and make
	 * it usable to the host. The chain is made available now rather than
	 * deferring to virtqueue_notify() in the hopes that if the host is
	 * currently running on another CPU, we can keep it processing the new
	 * descriptor.
	 */
	avail_idx = vq->vq_ring.avail->idx & (vq->vq_nentries - 1);
	vq->vq_ring.avail->ring[avail_idx] = desc_idx;

	wmb();
	vq->vq_ring.avail->idx++;

	/* Keep pending count until virtqueue_notify(). */
	vq->vq_queued_cnt++;
}