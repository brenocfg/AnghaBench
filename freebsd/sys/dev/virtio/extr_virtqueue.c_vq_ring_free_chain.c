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
typedef  size_t uint16_t ;
struct vring_desc {int flags; size_t next; } ;
struct vq_desc_extra {scalar_t__ ndescs; } ;
struct TYPE_2__ {struct vring_desc* desc; } ;
struct virtqueue {scalar_t__ vq_free_cnt; size_t vq_desc_head_idx; TYPE_1__ vq_ring; struct vq_desc_extra* vq_descx; } ;

/* Variables and functions */
 int /*<<< orphan*/  VQASSERT (struct virtqueue*,int,char*,scalar_t__) ; 
 int /*<<< orphan*/  VQ_RING_ASSERT_CHAIN_TERM (struct virtqueue*) ; 
 int /*<<< orphan*/  VQ_RING_ASSERT_VALID_IDX (struct virtqueue*,size_t) ; 
 int VRING_DESC_F_INDIRECT ; 
 int VRING_DESC_F_NEXT ; 

__attribute__((used)) static void
vq_ring_free_chain(struct virtqueue *vq, uint16_t desc_idx)
{
	struct vring_desc *dp;
	struct vq_desc_extra *dxp;

	VQ_RING_ASSERT_VALID_IDX(vq, desc_idx);
	dp = &vq->vq_ring.desc[desc_idx];
	dxp = &vq->vq_descx[desc_idx];

	if (vq->vq_free_cnt == 0)
		VQ_RING_ASSERT_CHAIN_TERM(vq);

	vq->vq_free_cnt += dxp->ndescs;
	dxp->ndescs--;

	if ((dp->flags & VRING_DESC_F_INDIRECT) == 0) {
		while (dp->flags & VRING_DESC_F_NEXT) {
			VQ_RING_ASSERT_VALID_IDX(vq, dp->next);
			dp = &vq->vq_ring.desc[dp->next];
			dxp->ndescs--;
		}
	}

	VQASSERT(vq, dxp->ndescs == 0,
	    "failed to free entire desc chain, remaining: %d", dxp->ndescs);

	/*
	 * We must append the existing free chain, if any, to the end of
	 * newly freed chain. If the virtqueue was completely used, then
	 * head would be VQ_RING_DESC_CHAIN_END (ASSERTed above).
	 */
	dp->next = vq->vq_desc_head_idx;
	vq->vq_desc_head_idx = desc_idx;
}