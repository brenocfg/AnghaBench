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
struct virtio_uml_device {int /*<<< orphan*/  req_fd; } ;
struct TYPE_2__ {int flags; } ;
struct vhost_user_msg {TYPE_1__ header; } ;

/* Variables and functions */
 int EPROTO ; 
 int VHOST_USER_FLAG_NEED_REPLY ; 
 int VHOST_USER_VERSION ; 
 int vhost_user_recv (int /*<<< orphan*/ ,struct vhost_user_msg*,size_t) ; 

__attribute__((used)) static int vhost_user_recv_req(struct virtio_uml_device *vu_dev,
			       struct vhost_user_msg *msg,
			       size_t max_payload_size)
{
	int rc = vhost_user_recv(vu_dev->req_fd, msg, max_payload_size);

	if (rc)
		return rc;

	if ((msg->header.flags & ~VHOST_USER_FLAG_NEED_REPLY) !=
			VHOST_USER_VERSION)
		return -EPROTO;

	return 0;
}