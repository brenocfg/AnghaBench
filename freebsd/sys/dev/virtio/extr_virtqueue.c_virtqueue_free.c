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
struct virtqueue {scalar_t__ vq_free_cnt; scalar_t__ vq_nentries; int vq_flags; int /*<<< orphan*/ * vq_ring_mem; scalar_t__ vq_ring_size; int /*<<< orphan*/  vq_name; int /*<<< orphan*/  vq_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int VIRTQUEUE_FLAG_INDIRECT ; 
 int /*<<< orphan*/  contigfree (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  free (struct virtqueue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtqueue_free_indirect (struct virtqueue*) ; 

void
virtqueue_free(struct virtqueue *vq)
{

	if (vq->vq_free_cnt != vq->vq_nentries) {
		device_printf(vq->vq_dev, "%s: freeing non-empty virtqueue, "
		    "leaking %d entries\n", vq->vq_name,
		    vq->vq_nentries - vq->vq_free_cnt);
	}

	if (vq->vq_flags & VIRTQUEUE_FLAG_INDIRECT)
		virtqueue_free_indirect(vq);

	if (vq->vq_ring_mem != NULL) {
		contigfree(vq->vq_ring_mem, vq->vq_ring_size, M_DEVBUF);
		vq->vq_ring_size = 0;
		vq->vq_ring_mem = NULL;
	}

	free(vq, M_DEVBUF);
}