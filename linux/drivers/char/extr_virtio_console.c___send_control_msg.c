#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct virtqueue {int dummy; } ;
struct virtio_console_control {int dummy; } ;
struct scatterlist {int dummy; } ;
struct TYPE_3__ {void* value; void* event; int /*<<< orphan*/  id; } ;
struct ports_device {int /*<<< orphan*/  c_ovq_lock; TYPE_1__ cpkt; int /*<<< orphan*/  vdev; struct virtqueue* c_ovq; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  cpu_relax () ; 
 void* cpu_to_virtio16 (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  cpu_to_virtio32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  use_multiport (struct ports_device*) ; 
 scalar_t__ virtqueue_add_outbuf (struct virtqueue*,struct scatterlist*,int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtqueue_get_buf (struct virtqueue*,unsigned int*) ; 
 int /*<<< orphan*/  virtqueue_is_broken (struct virtqueue*) ; 
 int /*<<< orphan*/  virtqueue_kick (struct virtqueue*) ; 

__attribute__((used)) static ssize_t __send_control_msg(struct ports_device *portdev, u32 port_id,
				  unsigned int event, unsigned int value)
{
	struct scatterlist sg[1];
	struct virtqueue *vq;
	unsigned int len;

	if (!use_multiport(portdev))
		return 0;

	vq = portdev->c_ovq;

	spin_lock(&portdev->c_ovq_lock);

	portdev->cpkt.id = cpu_to_virtio32(portdev->vdev, port_id);
	portdev->cpkt.event = cpu_to_virtio16(portdev->vdev, event);
	portdev->cpkt.value = cpu_to_virtio16(portdev->vdev, value);

	sg_init_one(sg, &portdev->cpkt, sizeof(struct virtio_console_control));

	if (virtqueue_add_outbuf(vq, sg, 1, &portdev->cpkt, GFP_ATOMIC) == 0) {
		virtqueue_kick(vq);
		while (!virtqueue_get_buf(vq, &len)
			&& !virtqueue_is_broken(vq))
			cpu_relax();
	}

	spin_unlock(&portdev->c_ovq_lock);
	return 0;
}