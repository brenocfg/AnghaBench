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
struct TYPE_4__ {int /*<<< orphan*/  addrlen; int /*<<< orphan*/  addr; } ;
struct comm_point {int /*<<< orphan*/  buffer; TYPE_2__ repinfo; TYPE_1__* ev; } ;
typedef  int ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  ev; } ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  UB_EV_WRITE ; 
 scalar_t__ WSAEINPROGRESS ; 
 scalar_t__ WSAEWOULDBLOCK ; 
 scalar_t__ WSAGetLastError () ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  log_assert (int) ; 
 int /*<<< orphan*/  log_err_addr (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int send (int,void*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ sldns_buffer_current (int /*<<< orphan*/ ) ; 
 scalar_t__ sldns_buffer_remaining (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_skip (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int /*<<< orphan*/  ub_winsock_tcp_wouldblock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wsa_strerror (scalar_t__) ; 

__attribute__((used)) static int
http_write_more(int fd, struct comm_point* c)
{
	ssize_t r;
	log_assert(sldns_buffer_remaining(c->buffer) > 0);
	r = send(fd, (void*)sldns_buffer_current(c->buffer), 
		sldns_buffer_remaining(c->buffer), 0);
	if(r == -1) {
#ifndef USE_WINSOCK
		if(errno == EINTR || errno == EAGAIN)
			return 1;
		log_err_addr("http send r", strerror(errno),
			&c->repinfo.addr, c->repinfo.addrlen);
#else
		if(WSAGetLastError() == WSAEINPROGRESS)
			return 1;
		if(WSAGetLastError() == WSAEWOULDBLOCK) {
			ub_winsock_tcp_wouldblock(c->ev->ev, UB_EV_WRITE);
			return 1; 
		}
		log_err_addr("http send r", wsa_strerror(WSAGetLastError()),
			&c->repinfo.addr, c->repinfo.addrlen);
#endif
		return 0;
	}
	sldns_buffer_skip(c->buffer, r);
	return 1;
}