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
struct msghdr {int msg_iovlen; scalar_t__ msg_flags; int /*<<< orphan*/ * msg_control; struct iovec* msg_iov; int /*<<< orphan*/  msg_namelen; int /*<<< orphan*/  msg_name; } ;
struct linux_sendto_args {int /*<<< orphan*/  flags; int /*<<< orphan*/  s; int /*<<< orphan*/  len; int /*<<< orphan*/  tolen; int /*<<< orphan*/  to; int /*<<< orphan*/  msg; } ;
struct ip {int /*<<< orphan*/  ip_off; int /*<<< orphan*/  ip_len; } ;
struct iovec {char* iov_base; int /*<<< orphan*/  iov_len; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IP_MAXPACKET ; 
 int /*<<< orphan*/  M_LINUX ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  PTRIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int copyin (int /*<<< orphan*/ ,struct ip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct ip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linux_ip_copysize ; 
 int linux_sendit (struct thread*,int /*<<< orphan*/ ,struct msghdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
linux_sendto_hdrincl(struct thread *td, struct linux_sendto_args *linux_args)
{
/*
 * linux_ip_copysize defines how many bytes we should copy
 * from the beginning of the IP packet before we customize it for BSD.
 * It should include all the fields we modify (ip_len and ip_off).
 */
#define linux_ip_copysize	8

	struct ip *packet;
	struct msghdr msg;
	struct iovec aiov[1];
	int error;

	/* Check that the packet isn't too big or too small. */
	if (linux_args->len < linux_ip_copysize ||
	    linux_args->len > IP_MAXPACKET)
		return (EINVAL);

	packet = (struct ip *)malloc(linux_args->len, M_LINUX, M_WAITOK);

	/* Make kernel copy of the packet to be sent */
	if ((error = copyin(PTRIN(linux_args->msg), packet,
	    linux_args->len)))
		goto goout;

	/* Convert fields from Linux to BSD raw IP socket format */
	packet->ip_len = linux_args->len;
	packet->ip_off = ntohs(packet->ip_off);

	/* Prepare the msghdr and iovec structures describing the new packet */
	msg.msg_name = PTRIN(linux_args->to);
	msg.msg_namelen = linux_args->tolen;
	msg.msg_iov = aiov;
	msg.msg_iovlen = 1;
	msg.msg_control = NULL;
	msg.msg_flags = 0;
	aiov[0].iov_base = (char *)packet;
	aiov[0].iov_len = linux_args->len;
	error = linux_sendit(td, linux_args->s, &msg, linux_args->flags,
	    NULL, UIO_SYSSPACE);
goout:
	free(packet, M_LINUX);
	return (error);
}