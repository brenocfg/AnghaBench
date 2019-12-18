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
struct thread {int dummy; } ;
struct recvfrom_args {int /*<<< orphan*/  fromlenaddr; int /*<<< orphan*/  s; int /*<<< orphan*/  flags; int /*<<< orphan*/  len; int /*<<< orphan*/  buf; int /*<<< orphan*/  from; } ;
struct msghdr {int msg_iovlen; int /*<<< orphan*/  msg_flags; scalar_t__ msg_control; struct iovec* msg_iov; int /*<<< orphan*/  msg_name; scalar_t__ msg_namelen; } ;
struct iovec {int /*<<< orphan*/  iov_len; int /*<<< orphan*/  iov_base; } ;

/* Variables and functions */
 int copyin (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int recvit (struct thread*,int /*<<< orphan*/ ,struct msghdr*,int /*<<< orphan*/ ) ; 

int
sys_recvfrom(struct thread *td, struct recvfrom_args *uap)
{
	struct msghdr msg;
	struct iovec aiov;
	int error;

	if (uap->fromlenaddr) {
		error = copyin(uap->fromlenaddr,
		    &msg.msg_namelen, sizeof (msg.msg_namelen));
		if (error != 0)
			goto done2;
	} else {
		msg.msg_namelen = 0;
	}
	msg.msg_name = uap->from;
	msg.msg_iov = &aiov;
	msg.msg_iovlen = 1;
	aiov.iov_base = uap->buf;
	aiov.iov_len = uap->len;
	msg.msg_control = 0;
	msg.msg_flags = uap->flags;
	error = recvit(td, uap->s, &msg, uap->fromlenaddr);
done2:
	return (error);
}