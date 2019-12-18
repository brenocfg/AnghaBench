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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  size_t uint16_t ;
struct vring_used_elem {int /*<<< orphan*/  len; scalar_t__ id; } ;
struct TYPE_5__ {TYPE_1__* used; } ;
struct virtqueue {scalar_t__ vq_used_cons_idx; int vq_nentries; TYPE_3__* vq_descx; TYPE_2__ vq_ring; } ;
struct TYPE_6__ {int /*<<< orphan*/ * cookie; } ;
struct TYPE_4__ {scalar_t__ idx; struct vring_used_elem* ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  VQASSERT (struct virtqueue*,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  vq_ring_free_chain (struct virtqueue*,size_t) ; 

void *
virtqueue_dequeue(struct virtqueue *vq, uint32_t *len)
{
	struct vring_used_elem *uep;
	void *cookie;
	uint16_t used_idx, desc_idx;

	if (vq->vq_used_cons_idx == vq->vq_ring.used->idx)
		return (NULL);

	used_idx = vq->vq_used_cons_idx++ & (vq->vq_nentries - 1);
	uep = &vq->vq_ring.used->ring[used_idx];

	rmb();
	desc_idx = (uint16_t) uep->id;
	if (len != NULL)
		*len = uep->len;

	vq_ring_free_chain(vq, desc_idx);

	cookie = vq->vq_descx[desc_idx].cookie;
	VQASSERT(vq, cookie != NULL, "no cookie for index %d", desc_idx);
	vq->vq_descx[desc_idx].cookie = NULL;

	return (cookie);
}