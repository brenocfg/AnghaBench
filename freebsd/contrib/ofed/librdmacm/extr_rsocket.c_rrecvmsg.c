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
struct msghdr {int /*<<< orphan*/  msg_flags; scalar_t__ msg_iovlen; int /*<<< orphan*/  msg_iov; scalar_t__ msg_controllen; scalar_t__ msg_control; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOTSUP ; 
 int /*<<< orphan*/  ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrecvv (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

ssize_t rrecvmsg(int socket, struct msghdr *msg, int flags)
{
	if (msg->msg_control && msg->msg_controllen)
		return ERR(ENOTSUP);

	return rrecvv(socket, msg->msg_iov, (int) msg->msg_iovlen, msg->msg_flags);
}