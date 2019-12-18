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
struct msghdr32 {int /*<<< orphan*/  msg_flags; int /*<<< orphan*/  msg_controllen; int /*<<< orphan*/  msg_control; int /*<<< orphan*/  msg_iovlen; int /*<<< orphan*/  msg_iov; int /*<<< orphan*/  msg_namelen; int /*<<< orphan*/  msg_name; } ;
struct msghdr {int /*<<< orphan*/  msg_flags; int /*<<< orphan*/  msg_controllen; void* msg_control; int /*<<< orphan*/  msg_iovlen; void* msg_iov; int /*<<< orphan*/  msg_namelen; void* msg_name; } ;
typedef  int /*<<< orphan*/  m32 ;

/* Variables and functions */
 void* PTRIN (int /*<<< orphan*/ ) ; 
 int copyin (struct msghdr32*,struct msghdr32*,int) ; 

__attribute__((used)) static int
freebsd32_copyinmsghdr(struct msghdr32 *msg32, struct msghdr *msg)
{
	struct msghdr32 m32;
	int error;

	error = copyin(msg32, &m32, sizeof(m32));
	if (error)
		return (error);
	msg->msg_name = PTRIN(m32.msg_name);
	msg->msg_namelen = m32.msg_namelen;
	msg->msg_iov = PTRIN(m32.msg_iov);
	msg->msg_iovlen = m32.msg_iovlen;
	msg->msg_control = PTRIN(m32.msg_control);
	msg->msg_controllen = m32.msg_controllen;
	msg->msg_flags = m32.msg_flags;
	return (0);
}