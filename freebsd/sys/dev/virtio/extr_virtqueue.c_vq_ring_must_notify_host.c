#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_6__ {TYPE_1__* used; TYPE_2__* avail; } ;
struct virtqueue {int vq_flags; TYPE_3__ vq_ring; scalar_t__ vq_queued_cnt; } ;
struct TYPE_5__ {scalar_t__ idx; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int VIRTQUEUE_FLAG_EVENT_IDX ; 
 int VRING_USED_F_NO_NOTIFY ; 
 scalar_t__ vring_avail_event (TYPE_3__*) ; 
 scalar_t__ vring_need_event (scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
vq_ring_must_notify_host(struct virtqueue *vq)
{
	uint16_t new_idx, prev_idx, event_idx;

	if (vq->vq_flags & VIRTQUEUE_FLAG_EVENT_IDX) {
		new_idx = vq->vq_ring.avail->idx;
		prev_idx = new_idx - vq->vq_queued_cnt;
		event_idx = vring_avail_event(&vq->vq_ring);

		return (vring_need_event(event_idx, new_idx, prev_idx) != 0);
	}

	return ((vq->vq_ring.used->flags & VRING_USED_F_NO_NOTIFY) == 0);
}