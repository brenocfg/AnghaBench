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
typedef  int /*<<< orphan*/  uint32_t ;
struct virtqueue {int /*<<< orphan*/  vq_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIRTIO_BUS_POLL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_spinwait () ; 
 void* virtqueue_dequeue (struct virtqueue*,int /*<<< orphan*/ *) ; 

void *
virtqueue_poll(struct virtqueue *vq, uint32_t *len)
{
	void *cookie;

	VIRTIO_BUS_POLL(vq->vq_dev);
	while ((cookie = virtqueue_dequeue(vq, len)) == NULL) {
		cpu_spinwait();
		VIRTIO_BUS_POLL(vq->vq_dev);
	}

	return (cookie);
}