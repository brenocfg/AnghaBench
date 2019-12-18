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
typedef  int u32 ;
struct virtio_uml_device {int protocol_features; } ;
struct TYPE_5__ {int offset; int size; int /*<<< orphan*/  payload; } ;
struct TYPE_6__ {TYPE_2__ config; } ;
struct TYPE_4__ {size_t size; int /*<<< orphan*/  request; } ;
struct vhost_user_msg {TYPE_3__ payload; TYPE_1__ header; } ;

/* Variables and functions */
 int BIT_ULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  VHOST_USER_PROTOCOL_F_CONFIG ; 
 int /*<<< orphan*/  VHOST_USER_SET_CONFIG ; 
 int /*<<< orphan*/  kfree (struct vhost_user_msg*) ; 
 struct vhost_user_msg* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int) ; 
 int vhost_user_send (struct virtio_uml_device*,int,struct vhost_user_msg*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vu_err (struct virtio_uml_device*,char*,int) ; 

__attribute__((used)) static void vhost_user_set_config(struct virtio_uml_device *vu_dev,
				  u32 offset, const void *buf, u32 len)
{
	struct vhost_user_msg *msg;
	size_t payload_size = sizeof(msg->payload.config) + len;
	size_t msg_size = sizeof(msg->header) + payload_size;
	int rc;

	if (!(vu_dev->protocol_features &
	      BIT_ULL(VHOST_USER_PROTOCOL_F_CONFIG)))
		return;

	msg = kzalloc(msg_size, GFP_KERNEL);
	if (!msg)
		return;
	msg->header.request = VHOST_USER_SET_CONFIG;
	msg->header.size = payload_size;
	msg->payload.config.offset = offset;
	msg->payload.config.size = len;
	memcpy(msg->payload.config.payload, buf, len);

	rc = vhost_user_send(vu_dev, false, msg, NULL, 0);
	if (rc)
		vu_err(vu_dev, "sending VHOST_USER_SET_CONFIG failed: %d\n",
		       rc);

	kfree(msg);
}