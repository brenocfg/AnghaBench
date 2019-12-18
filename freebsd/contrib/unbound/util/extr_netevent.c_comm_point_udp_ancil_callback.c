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
struct sockaddr {int dummy; } ;
struct msghdr {int msg_iovlen; char* msg_control; int msg_controllen; void* msg_namelen; scalar_t__ msg_flags; struct iovec* msg_iov; int /*<<< orphan*/ * msg_name; } ;
struct iovec {scalar_t__ iov_len; int /*<<< orphan*/  iov_base; } ;
struct in_pktinfo {int dummy; } ;
struct in_addr {int dummy; } ;
struct in6_pktinfo {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  v4addr; int /*<<< orphan*/  v4info; int /*<<< orphan*/  v6info; } ;
struct comm_reply {int srctype; struct comm_point* c; void* addrlen; int /*<<< orphan*/  addr; TYPE_2__ pktinfo; } ;
struct comm_point {scalar_t__ type; int fd; scalar_t__ buffer; int /*<<< orphan*/  cb_arg; scalar_t__ (* callback ) (struct comm_point*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct comm_reply*) ;TYPE_1__* ev; } ;
struct cmsghdr {scalar_t__ cmsg_level; scalar_t__ cmsg_type; } ;
typedef  int ssize_t ;
typedef  void* socklen_t ;
typedef  int /*<<< orphan*/  ancil ;
struct TYPE_3__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMSG_DATA (struct cmsghdr*) ; 
 struct cmsghdr* CMSG_FIRSTHDR (struct msghdr*) ; 
 struct cmsghdr* CMSG_NXTHDR (struct msghdr*,struct cmsghdr*) ; 
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ IPPROTO_IP ; 
 scalar_t__ IPPROTO_IPV6 ; 
 scalar_t__ IPV6_PKTINFO ; 
 scalar_t__ IP_PKTINFO ; 
 scalar_t__ IP_RECVDSTADDR ; 
 int /*<<< orphan*/  NETEVENT_NOERROR ; 
 int NUM_UDP_PER_SELECT ; 
 short UB_EV_READ ; 
 scalar_t__ VERB_ALGO ; 
 int /*<<< orphan*/  comm_point_send_udp_msg_if (struct comm_point*,scalar_t__,struct sockaddr*,void*,struct comm_reply*) ; 
 scalar_t__ comm_udp ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fatal_exit (char*) ; 
 int /*<<< orphan*/  fptr_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fptr_whitelist_comm_point (scalar_t__ (*) (struct comm_point*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct comm_reply*)) ; 
 int /*<<< orphan*/  log_assert (int) ; 
 int /*<<< orphan*/  log_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  p_ancil (char*,struct comm_reply*) ; 
 int recvmsg (int,struct msghdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_begin (scalar_t__) ; 
 int /*<<< orphan*/  sldns_buffer_clear (scalar_t__) ; 
 int /*<<< orphan*/  sldns_buffer_flip (scalar_t__) ; 
 scalar_t__ sldns_buffer_remaining (scalar_t__) ; 
 int /*<<< orphan*/  sldns_buffer_skip (scalar_t__,int) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 scalar_t__ stub1 (struct comm_point*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct comm_reply*) ; 
 int /*<<< orphan*/  ub_comm_base_now (int /*<<< orphan*/ ) ; 
 scalar_t__ verbosity ; 

void 
comm_point_udp_ancil_callback(int fd, short event, void* arg)
{
#if defined(AF_INET6) && defined(IPV6_PKTINFO) && defined(HAVE_RECVMSG)
	struct comm_reply rep;
	struct msghdr msg;
	struct iovec iov[1];
	ssize_t rcv;
	char ancil[256];
	int i;
#ifndef S_SPLINT_S
	struct cmsghdr* cmsg;
#endif /* S_SPLINT_S */

	rep.c = (struct comm_point*)arg;
	log_assert(rep.c->type == comm_udp);

	if(!(event&UB_EV_READ))
		return;
	log_assert(rep.c && rep.c->buffer && rep.c->fd == fd);
	ub_comm_base_now(rep.c->ev->base);
	for(i=0; i<NUM_UDP_PER_SELECT; i++) {
		sldns_buffer_clear(rep.c->buffer);
		rep.addrlen = (socklen_t)sizeof(rep.addr);
		log_assert(fd != -1);
		log_assert(sldns_buffer_remaining(rep.c->buffer) > 0);
		msg.msg_name = &rep.addr;
		msg.msg_namelen = (socklen_t)sizeof(rep.addr);
		iov[0].iov_base = sldns_buffer_begin(rep.c->buffer);
		iov[0].iov_len = sldns_buffer_remaining(rep.c->buffer);
		msg.msg_iov = iov;
		msg.msg_iovlen = 1;
		msg.msg_control = ancil;
#ifndef S_SPLINT_S
		msg.msg_controllen = sizeof(ancil);
#endif /* S_SPLINT_S */
		msg.msg_flags = 0;
		rcv = recvmsg(fd, &msg, 0);
		if(rcv == -1) {
			if(errno != EAGAIN && errno != EINTR) {
				log_err("recvmsg failed: %s", strerror(errno));
			}
			return;
		}
		rep.addrlen = msg.msg_namelen;
		sldns_buffer_skip(rep.c->buffer, rcv);
		sldns_buffer_flip(rep.c->buffer);
		rep.srctype = 0;
#ifndef S_SPLINT_S
		for(cmsg = CMSG_FIRSTHDR(&msg); cmsg != NULL;
			cmsg = CMSG_NXTHDR(&msg, cmsg)) {
			if( cmsg->cmsg_level == IPPROTO_IPV6 &&
				cmsg->cmsg_type == IPV6_PKTINFO) {
				rep.srctype = 6;
				memmove(&rep.pktinfo.v6info, CMSG_DATA(cmsg),
					sizeof(struct in6_pktinfo));
				break;
#ifdef IP_PKTINFO
			} else if( cmsg->cmsg_level == IPPROTO_IP &&
				cmsg->cmsg_type == IP_PKTINFO) {
				rep.srctype = 4;
				memmove(&rep.pktinfo.v4info, CMSG_DATA(cmsg),
					sizeof(struct in_pktinfo));
				break;
#elif defined(IP_RECVDSTADDR)
			} else if( cmsg->cmsg_level == IPPROTO_IP &&
				cmsg->cmsg_type == IP_RECVDSTADDR) {
				rep.srctype = 4;
				memmove(&rep.pktinfo.v4addr, CMSG_DATA(cmsg),
					sizeof(struct in_addr));
				break;
#endif /* IP_PKTINFO or IP_RECVDSTADDR */
			}
		}
		if(verbosity >= VERB_ALGO)
			p_ancil("receive_udp on interface", &rep);
#endif /* S_SPLINT_S */
		fptr_ok(fptr_whitelist_comm_point(rep.c->callback));
		if((*rep.c->callback)(rep.c, rep.c->cb_arg, NETEVENT_NOERROR, &rep)) {
			/* send back immediate reply */
			(void)comm_point_send_udp_msg_if(rep.c, rep.c->buffer,
				(struct sockaddr*)&rep.addr, rep.addrlen, &rep);
		}
		if(!rep.c || rep.c->fd == -1) /* commpoint closed */
			break;
	}
#else
	(void)fd;
	(void)event;
	(void)arg;
	fatal_exit("recvmsg: No support for IPV6_PKTINFO; IP_PKTINFO or IP_RECVDSTADDR. "
		"Please disable interface-automatic");
#endif /* AF_INET6 && IPV6_PKTINFO && HAVE_RECVMSG */
}