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
struct virtrng_info {int /*<<< orphan*/  have_data; int /*<<< orphan*/  data_avail; int /*<<< orphan*/  vq; } ;
struct virtqueue {TYPE_1__* vdev; } ;
struct TYPE_2__ {struct virtrng_info* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virtqueue_get_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void random_recv_done(struct virtqueue *vq)
{
	struct virtrng_info *vi = vq->vdev->priv;

	/* We can get spurious callbacks, e.g. shared IRQs + virtio_pci. */
	if (!virtqueue_get_buf(vi->vq, &vi->data_avail))
		return;

	complete(&vi->have_data);
}