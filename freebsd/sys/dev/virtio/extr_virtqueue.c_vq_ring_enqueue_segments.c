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
typedef  size_t uint16_t ;
struct vring_desc {size_t next; int /*<<< orphan*/  flags; int /*<<< orphan*/  len; int /*<<< orphan*/  addr; } ;
struct virtqueue {int dummy; } ;
struct sglist_seg {int /*<<< orphan*/  ss_len; int /*<<< orphan*/  ss_paddr; } ;
struct sglist {struct sglist_seg* sg_segs; } ;

/* Variables and functions */
 int /*<<< orphan*/  VQASSERT (struct virtqueue*,int,char*) ; 
 size_t VQ_RING_DESC_CHAIN_END ; 
 int /*<<< orphan*/  VRING_DESC_F_NEXT ; 
 int /*<<< orphan*/  VRING_DESC_F_WRITE ; 

__attribute__((used)) static uint16_t
vq_ring_enqueue_segments(struct virtqueue *vq, struct vring_desc *desc,
    uint16_t head_idx, struct sglist *sg, int readable, int writable)
{
	struct sglist_seg *seg;
	struct vring_desc *dp;
	int i, needed;
	uint16_t idx;

	needed = readable + writable;

	for (i = 0, idx = head_idx, seg = sg->sg_segs;
	     i < needed;
	     i++, idx = dp->next, seg++) {
		VQASSERT(vq, idx != VQ_RING_DESC_CHAIN_END,
		    "premature end of free desc chain");

		dp = &desc[idx];
		dp->addr = seg->ss_paddr;
		dp->len = seg->ss_len;
		dp->flags = 0;

		if (i < needed - 1)
			dp->flags |= VRING_DESC_F_NEXT;
		if (i >= readable)
			dp->flags |= VRING_DESC_F_WRITE;
	}

	return (idx);
}