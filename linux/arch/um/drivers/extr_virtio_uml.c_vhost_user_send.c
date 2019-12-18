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
typedef  scalar_t__ uint64_t ;
struct virtio_uml_device {int protocol_features; int /*<<< orphan*/  sock; } ;
struct TYPE_2__ {int size; int /*<<< orphan*/  flags; } ;
struct vhost_user_msg {TYPE_1__ header; } ;

/* Variables and functions */
 int BIT_ULL (int /*<<< orphan*/ ) ; 
 int EIO ; 
 int /*<<< orphan*/  VHOST_USER_FLAG_NEED_REPLY ; 
 int /*<<< orphan*/  VHOST_USER_PROTOCOL_F_REPLY_ACK ; 
 int /*<<< orphan*/  VHOST_USER_VERSION ; 
 int full_sendmsg_fds (int /*<<< orphan*/ ,struct vhost_user_msg*,size_t,int*,size_t) ; 
 int vhost_user_recv_u64 (struct virtio_uml_device*,scalar_t__*) ; 
 int /*<<< orphan*/  vu_err (struct virtio_uml_device*,char*,scalar_t__) ; 

__attribute__((used)) static int vhost_user_send(struct virtio_uml_device *vu_dev,
			   bool need_response, struct vhost_user_msg *msg,
			   int *fds, size_t num_fds)
{
	size_t size = sizeof(msg->header) + msg->header.size;
	bool request_ack;
	int rc;

	msg->header.flags |= VHOST_USER_VERSION;

	/*
	 * The need_response flag indicates that we already need a response,
	 * e.g. to read the features. In these cases, don't request an ACK as
	 * it is meaningless. Also request an ACK only if supported.
	 */
	request_ack = !need_response;
	if (!(vu_dev->protocol_features &
			BIT_ULL(VHOST_USER_PROTOCOL_F_REPLY_ACK)))
		request_ack = false;

	if (request_ack)
		msg->header.flags |= VHOST_USER_FLAG_NEED_REPLY;

	rc = full_sendmsg_fds(vu_dev->sock, msg, size, fds, num_fds);
	if (rc < 0)
		return rc;

	if (request_ack) {
		uint64_t status;

		rc = vhost_user_recv_u64(vu_dev, &status);
		if (rc)
			return rc;

		if (status) {
			vu_err(vu_dev, "slave reports error: %llu\n", status);
			return -EIO;
		}
	}

	return 0;
}