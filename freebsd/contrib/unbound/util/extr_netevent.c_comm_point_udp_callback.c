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
struct sockaddr {int dummy; } ;
struct sldns_buffer {int dummy; } ;
struct comm_reply {struct comm_point* c; scalar_t__ addrlen; int /*<<< orphan*/  addr; scalar_t__ srctype; } ;
struct comm_point {scalar_t__ type; int fd; struct sldns_buffer* buffer; struct sldns_buffer* dnscrypt_buffer; int /*<<< orphan*/  cb_arg; scalar_t__ (* callback ) (struct comm_point*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct comm_reply*) ;TYPE_1__* ev; } ;
typedef  int ssize_t ;
typedef  scalar_t__ socklen_t ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  NETEVENT_NOERROR ; 
 int NUM_UDP_PER_SELECT ; 
 short UB_EV_READ ; 
 scalar_t__ WSAECONNRESET ; 
 scalar_t__ WSAEINPROGRESS ; 
 scalar_t__ WSAEWOULDBLOCK ; 
 scalar_t__ WSAGetLastError () ; 
 int /*<<< orphan*/  comm_point_send_udp_msg (struct comm_point*,struct sldns_buffer*,struct sockaddr*,scalar_t__) ; 
 scalar_t__ comm_udp ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fptr_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fptr_whitelist_comm_point (scalar_t__ (*) (struct comm_point*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct comm_reply*)) ; 
 int /*<<< orphan*/  log_assert (int) ; 
 int /*<<< orphan*/  log_err (char*,int,...) ; 
 int recvfrom (int,void*,scalar_t__,int /*<<< orphan*/ ,struct sockaddr*,scalar_t__*) ; 
 scalar_t__ sldns_buffer_begin (struct sldns_buffer*) ; 
 int /*<<< orphan*/  sldns_buffer_clear (struct sldns_buffer*) ; 
 int /*<<< orphan*/  sldns_buffer_flip (struct sldns_buffer*) ; 
 scalar_t__ sldns_buffer_remaining (struct sldns_buffer*) ; 
 int /*<<< orphan*/  sldns_buffer_skip (struct sldns_buffer*,int) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 scalar_t__ stub1 (struct comm_point*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct comm_reply*) ; 
 int /*<<< orphan*/  ub_comm_base_now (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wsa_strerror (scalar_t__) ; 

void 
comm_point_udp_callback(int fd, short event, void* arg)
{
	struct comm_reply rep;
	ssize_t rcv;
	int i;
	struct sldns_buffer *buffer;

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
		rcv = recvfrom(fd, (void*)sldns_buffer_begin(rep.c->buffer), 
			sldns_buffer_remaining(rep.c->buffer), 0, 
			(struct sockaddr*)&rep.addr, &rep.addrlen);
		if(rcv == -1) {
#ifndef USE_WINSOCK
			if(errno != EAGAIN && errno != EINTR)
				log_err("recvfrom %d failed: %s", 
					fd, strerror(errno));
#else
			if(WSAGetLastError() != WSAEINPROGRESS &&
				WSAGetLastError() != WSAECONNRESET &&
				WSAGetLastError()!= WSAEWOULDBLOCK)
				log_err("recvfrom failed: %s",
					wsa_strerror(WSAGetLastError()));
#endif
			return;
		}
		sldns_buffer_skip(rep.c->buffer, rcv);
		sldns_buffer_flip(rep.c->buffer);
		rep.srctype = 0;
		fptr_ok(fptr_whitelist_comm_point(rep.c->callback));
		if((*rep.c->callback)(rep.c, rep.c->cb_arg, NETEVENT_NOERROR, &rep)) {
			/* send back immediate reply */
#ifdef USE_DNSCRYPT
			buffer = rep.c->dnscrypt_buffer;
#else
			buffer = rep.c->buffer;
#endif
			(void)comm_point_send_udp_msg(rep.c, buffer,
				(struct sockaddr*)&rep.addr, rep.addrlen);
		}
		if(!rep.c || rep.c->fd != fd) /* commpoint closed to -1 or reused for
		another UDP port. Note rep.c cannot be reused with TCP fd. */
			break;
	}
}