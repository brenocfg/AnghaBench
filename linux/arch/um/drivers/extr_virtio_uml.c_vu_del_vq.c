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
struct virtqueue {struct virtio_uml_vq_info* priv; } ;
struct virtio_uml_vq_info {int /*<<< orphan*/  kick_fd; int /*<<< orphan*/  call_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIRTIO_IRQ ; 
 int /*<<< orphan*/  kfree (struct virtio_uml_vq_info*) ; 
 int /*<<< orphan*/  os_close_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  um_free_irq (int /*<<< orphan*/ ,struct virtqueue*) ; 
 int /*<<< orphan*/  vring_del_virtqueue (struct virtqueue*) ; 

__attribute__((used)) static void vu_del_vq(struct virtqueue *vq)
{
	struct virtio_uml_vq_info *info = vq->priv;

	um_free_irq(VIRTIO_IRQ, vq);

	os_close_file(info->call_fd);
	os_close_file(info->kick_fd);

	vring_del_virtqueue(vq);
	kfree(info);
}