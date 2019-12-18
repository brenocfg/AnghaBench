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
struct msghdr {int msg_iovlen; scalar_t__ msg_flags; scalar_t__ msg_controllen; int /*<<< orphan*/ * msg_control; struct iovec* msg_iov; int /*<<< orphan*/  msg_namelen; int /*<<< orphan*/ * msg_name; } ;
struct mc_request {int /*<<< orphan*/  originating_fd; int /*<<< orphan*/  originlen; int /*<<< orphan*/  origin; } ;
struct iovec {char* iov_base; int /*<<< orphan*/  iov_len; } ;

/* Variables and functions */
 int sendmsg (int /*<<< orphan*/ ,struct msghdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static int mconsole_reply_v0(struct mc_request *req, char *reply)
{
	struct iovec iov;
	struct msghdr msg;

	iov.iov_base = reply;
	iov.iov_len = strlen(reply);

	msg.msg_name = &(req->origin);
	msg.msg_namelen = req->originlen;
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	msg.msg_control = NULL;
	msg.msg_controllen = 0;
	msg.msg_flags = 0;

	return sendmsg(req->originating_fd, &msg, 0);
}