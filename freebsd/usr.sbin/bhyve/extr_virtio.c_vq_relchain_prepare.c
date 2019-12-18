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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  size_t uint16_t ;
struct vring_used {struct virtio_used* vu_ring; } ;
struct vqueue_info {size_t vq_qsize; int /*<<< orphan*/  vq_next_used; struct vring_used* vq_used; } ;
struct virtio_used {size_t vu_idx; int /*<<< orphan*/  vu_tlen; } ;

/* Variables and functions */

void
vq_relchain_prepare(struct vqueue_info *vq, uint16_t idx, uint32_t iolen)
{
	volatile struct vring_used *vuh;
	volatile struct virtio_used *vue;
	uint16_t mask;

	/*
	 * Notes:
	 *  - mask is N-1 where N is a power of 2 so computes x % N
	 *  - vuh points to the "used" data shared with guest
	 *  - vue points to the "used" ring entry we want to update
	 *
	 * (I apologize for the two fields named vu_idx; the
	 * virtio spec calls the one that vue points to, "id"...)
	 */
	mask = vq->vq_qsize - 1;
	vuh = vq->vq_used;

	vue = &vuh->vu_ring[vq->vq_next_used++ & mask];
	vue->vu_idx = idx;
	vue->vu_tlen = iolen;
}