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
struct comm_point {int fd; scalar_t__ type; TYPE_1__* ev; int /*<<< orphan*/  do_not_close; scalar_t__ tcp_req_info; int /*<<< orphan*/  tcl_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  ev; } ;

/* Variables and functions */
 int /*<<< orphan*/  UB_EV_READ ; 
 int /*<<< orphan*/  UB_EV_WRITE ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  closesocket (int) ; 
 scalar_t__ comm_http ; 
 scalar_t__ comm_tcp ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  tcl_close_connection (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_req_info_clear (scalar_t__) ; 
 scalar_t__ ub_event_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ub_winsock_tcp_wouldblock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,int) ; 

void 
comm_point_close(struct comm_point* c)
{
	if(!c)
		return;
	if(c->fd != -1) {
		if(ub_event_del(c->ev->ev) != 0) {
			log_err("could not event_del on close");
		}
	}
	tcl_close_connection(c->tcl_addr);
	if(c->tcp_req_info)
		tcp_req_info_clear(c->tcp_req_info);
	/* close fd after removing from event lists, or epoll.. is messed up */
	if(c->fd != -1 && !c->do_not_close) {
		if(c->type == comm_tcp || c->type == comm_http) {
			/* delete sticky events for the fd, it gets closed */
			ub_winsock_tcp_wouldblock(c->ev->ev, UB_EV_READ);
			ub_winsock_tcp_wouldblock(c->ev->ev, UB_EV_WRITE);
		}
		verbose(VERB_ALGO, "close fd %d", c->fd);
#ifndef USE_WINSOCK
		close(c->fd);
#else
		closesocket(c->fd);
#endif
	}
	c->fd = -1;
}