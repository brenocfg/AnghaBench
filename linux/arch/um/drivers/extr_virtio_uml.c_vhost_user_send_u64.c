#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct virtio_uml_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  integer; } ;
struct TYPE_3__ {int size; int /*<<< orphan*/  request; } ;
struct vhost_user_msg {TYPE_2__ payload; TYPE_1__ header; } ;

/* Variables and functions */
 int vhost_user_send (struct virtio_uml_device*,int,struct vhost_user_msg*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vhost_user_send_u64(struct virtio_uml_device *vu_dev,
			       u32 request, u64 value)
{
	struct vhost_user_msg msg = {
		.header.request = request,
		.header.size = sizeof(msg.payload.integer),
		.payload.integer = value,
	};

	return vhost_user_send(vu_dev, false, &msg, NULL, 0);
}