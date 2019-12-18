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
struct vring_desc {int next; } ;
struct virtqueue {int vq_max_indirect_size; int /*<<< orphan*/  vq_indirect_mem_size; } ;

/* Variables and functions */
 int VQ_RING_DESC_CHAIN_END ; 
 int /*<<< orphan*/  bzero (struct vring_desc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
virtqueue_init_indirect_list(struct virtqueue *vq,
    struct vring_desc *indirect)
{
	int i;

	bzero(indirect, vq->vq_indirect_mem_size);

	for (i = 0; i < vq->vq_max_indirect_size - 1; i++)
		indirect[i].next = i + 1;
	indirect[i].next = VQ_RING_DESC_CHAIN_END;
}