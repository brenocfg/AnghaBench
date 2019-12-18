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
struct msghdr {int msg_iovlen; scalar_t__ msg_flags; void* msg_control; struct iovec* msg_iov; scalar_t__ msg_namelen; int /*<<< orphan*/ * msg_name; } ;
struct iovec {int /*<<< orphan*/  iov_len; int /*<<< orphan*/  iov_base; } ;
struct TYPE_3__ {int /*<<< orphan*/  buf_size; int /*<<< orphan*/  buf_send; int /*<<< orphan*/  buf_recv; } ;
struct TYPE_4__ {TYPE_1__ ipc_msg; scalar_t__ server_flag; scalar_t__ send_data_flag; } ;

/* Variables and functions */
 TYPE_2__ uc_cfg ; 

__attribute__((used)) static void
uc_msghdr_init_generic(struct msghdr *msghdr, struct iovec *iov, void *cmsg_data)
{
	msghdr->msg_name = NULL;
	msghdr->msg_namelen = 0;
	if (uc_cfg.send_data_flag) {
		iov->iov_base = uc_cfg.server_flag ?
		    uc_cfg.ipc_msg.buf_recv : uc_cfg.ipc_msg.buf_send;
		iov->iov_len = uc_cfg.ipc_msg.buf_size;
		msghdr->msg_iov = iov;
		msghdr->msg_iovlen = 1;
	} else {
		msghdr->msg_iov = NULL;
		msghdr->msg_iovlen = 0;
	}
	msghdr->msg_control = cmsg_data;
	msghdr->msg_flags = 0;
}