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
struct vq_desc_extra {int ndescs; int /*<<< orphan*/ * cookie; } ;
struct TYPE_2__ {int /*<<< orphan*/  desc; } ;
struct virtqueue {int vq_nentries; int vq_max_indirect_size; int vq_free_cnt; size_t vq_desc_head_idx; TYPE_1__ vq_ring; struct vq_desc_extra* vq_descx; } ;
struct sglist {int sg_nseg; } ;

/* Variables and functions */
 int EINVAL ; 
 int EMSGSIZE ; 
 int ENOSPC ; 
 int /*<<< orphan*/  VQASSERT (struct virtqueue*,int,char*,...) ; 
 int /*<<< orphan*/  VQ_RING_ASSERT_CHAIN_TERM (struct virtqueue*) ; 
 int /*<<< orphan*/  VQ_RING_ASSERT_VALID_IDX (struct virtqueue*,size_t) ; 
 int /*<<< orphan*/  vq_ring_enqueue_indirect (struct virtqueue*,void*,struct sglist*,int,int) ; 
 size_t vq_ring_enqueue_segments (struct virtqueue*,int /*<<< orphan*/ ,size_t,struct sglist*,int,int) ; 
 int /*<<< orphan*/  vq_ring_update_avail (struct virtqueue*,size_t) ; 
 scalar_t__ vq_ring_use_indirect (struct virtqueue*,int) ; 

int
virtqueue_enqueue(struct virtqueue *vq, void *cookie, struct sglist *sg,
    int readable, int writable)
{
	struct vq_desc_extra *dxp;
	int needed;
	uint16_t head_idx, idx;

	needed = readable + writable;

	VQASSERT(vq, cookie != NULL, "enqueuing with no cookie");
	VQASSERT(vq, needed == sg->sg_nseg,
	    "segment count mismatch, %d, %d", needed, sg->sg_nseg);
	VQASSERT(vq,
	    needed <= vq->vq_nentries || needed <= vq->vq_max_indirect_size,
	    "too many segments to enqueue: %d, %d/%d", needed,
	    vq->vq_nentries, vq->vq_max_indirect_size);

	if (needed < 1)
		return (EINVAL);
	if (vq->vq_free_cnt == 0)
		return (ENOSPC);

	if (vq_ring_use_indirect(vq, needed)) {
		vq_ring_enqueue_indirect(vq, cookie, sg, readable, writable);
		return (0);
	} else if (vq->vq_free_cnt < needed)
		return (EMSGSIZE);

	head_idx = vq->vq_desc_head_idx;
	VQ_RING_ASSERT_VALID_IDX(vq, head_idx);
	dxp = &vq->vq_descx[head_idx];

	VQASSERT(vq, dxp->cookie == NULL,
	    "cookie already exists for index %d", head_idx);
	dxp->cookie = cookie;
	dxp->ndescs = needed;

	idx = vq_ring_enqueue_segments(vq, vq->vq_ring.desc, head_idx,
	    sg, readable, writable);

	vq->vq_desc_head_idx = idx;
	vq->vq_free_cnt -= needed;
	if (vq->vq_free_cnt == 0)
		VQ_RING_ASSERT_CHAIN_TERM(vq);
	else
		VQ_RING_ASSERT_VALID_IDX(vq, idx);

	vq_ring_update_avail(vq, head_idx);

	return (0);
}