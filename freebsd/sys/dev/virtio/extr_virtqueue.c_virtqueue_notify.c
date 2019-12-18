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
struct virtqueue {scalar_t__ vq_queued_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  mb () ; 
 scalar_t__ vq_ring_must_notify_host (struct virtqueue*) ; 
 int /*<<< orphan*/  vq_ring_notify_host (struct virtqueue*) ; 

void
virtqueue_notify(struct virtqueue *vq)
{

	/* Ensure updated avail->idx is visible to host. */
	mb();

	if (vq_ring_must_notify_host(vq))
		vq_ring_notify_host(vq);
	vq->vq_queued_cnt = 0;
}