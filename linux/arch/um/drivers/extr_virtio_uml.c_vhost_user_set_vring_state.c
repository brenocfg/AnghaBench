#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct virtio_uml_device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  num; int /*<<< orphan*/  index; } ;
struct TYPE_6__ {TYPE_2__ vring_state; } ;
struct TYPE_4__ {int size; int /*<<< orphan*/  request; } ;
struct vhost_user_msg {TYPE_3__ payload; TYPE_1__ header; } ;

/* Variables and functions */
 int vhost_user_send (struct virtio_uml_device*,int,struct vhost_user_msg*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vhost_user_set_vring_state(struct virtio_uml_device *vu_dev,
				      u32 request, u32 index, u32 num)
{
	struct vhost_user_msg msg = {
		.header.request = request,
		.header.size = sizeof(msg.payload.vring_state),
		.payload.vring_state.index = index,
		.payload.vring_state.num = num,
	};

	return vhost_user_send(vu_dev, false, &msg, NULL, 0);
}