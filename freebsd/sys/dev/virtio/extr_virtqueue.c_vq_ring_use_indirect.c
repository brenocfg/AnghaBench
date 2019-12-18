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
struct virtqueue {int vq_flags; int vq_max_indirect_size; } ;

/* Variables and functions */
 int VIRTQUEUE_FLAG_INDIRECT ; 

__attribute__((used)) static int
vq_ring_use_indirect(struct virtqueue *vq, int needed)
{

	if ((vq->vq_flags & VIRTQUEUE_FLAG_INDIRECT) == 0)
		return (0);

	if (vq->vq_max_indirect_size < needed)
		return (0);

	if (needed < 2)
		return (0);

	return (1);
}