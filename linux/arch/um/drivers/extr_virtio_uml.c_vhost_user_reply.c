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
struct virtio_uml_device {int /*<<< orphan*/  req_fd; } ;
struct TYPE_4__ {int size; int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int integer; } ;
struct vhost_user_msg {TYPE_2__ header; TYPE_1__ payload; } ;

/* Variables and functions */
 int /*<<< orphan*/  VHOST_USER_FLAG_NEED_REPLY ; 
 int /*<<< orphan*/  VHOST_USER_FLAG_REPLY ; 
 int full_sendmsg_fds (int /*<<< orphan*/ ,struct vhost_user_msg*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vu_err (struct virtio_uml_device*,char*,int,size_t) ; 

__attribute__((used)) static void vhost_user_reply(struct virtio_uml_device *vu_dev,
			     struct vhost_user_msg *msg, int response)
{
	struct vhost_user_msg reply = {
		.payload.integer = response,
	};
	size_t size = sizeof(reply.header) + sizeof(reply.payload.integer);
	int rc;

	reply.header = msg->header;
	reply.header.flags &= ~VHOST_USER_FLAG_NEED_REPLY;
	reply.header.flags |= VHOST_USER_FLAG_REPLY;
	reply.header.size = sizeof(reply.payload.integer);

	rc = full_sendmsg_fds(vu_dev->req_fd, &reply, size, NULL, 0);

	if (rc)
		vu_err(vu_dev,
		       "sending reply to slave request failed: %d (size %zu)\n",
		       rc, size);
}