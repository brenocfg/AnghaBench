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
struct vring {TYPE_1__* desc; } ;
struct virtqueue {char* vq_ring_mem; int vq_nentries; int /*<<< orphan*/  vq_alignment; struct vring vq_ring; } ;
struct TYPE_2__ {int next; } ;

/* Variables and functions */
 int VQ_RING_DESC_CHAIN_END ; 
 int /*<<< orphan*/  vring_init (struct vring*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vq_ring_init(struct virtqueue *vq)
{
	struct vring *vr;
	char *ring_mem;
	int i, size;

	ring_mem = vq->vq_ring_mem;
	size = vq->vq_nentries;
	vr = &vq->vq_ring;

	vring_init(vr, size, ring_mem, vq->vq_alignment);

	for (i = 0; i < size - 1; i++)
		vr->desc[i].next = i + 1;
	vr->desc[i].next = VQ_RING_DESC_CHAIN_END;
}