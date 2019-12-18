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
struct virtqueue {int /*<<< orphan*/  vq_queue_index; int /*<<< orphan*/  vq_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIRTIO_BUS_NOTIFY_VQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vq_ring_notify_host(struct virtqueue *vq)
{

	VIRTIO_BUS_NOTIFY_VQ(vq->vq_dev, vq->vq_queue_index);
}