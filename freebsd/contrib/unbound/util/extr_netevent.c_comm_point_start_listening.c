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
struct timeval {int tv_sec; int tv_usec; } ;
struct comm_point {int fd; scalar_t__ type; struct timeval* timeout; TYPE_1__* ev; scalar_t__ tcp_is_reading; int /*<<< orphan*/  tcp_free; } ;
struct TYPE_2__ {int /*<<< orphan*/  ev; } ;

/* Variables and functions */
 int UB_EV_READ ; 
 int UB_EV_TIMEOUT ; 
 int UB_EV_WRITE ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  closesocket (int) ; 
 scalar_t__ comm_http ; 
 scalar_t__ comm_tcp ; 
 scalar_t__ comm_tcp_accept ; 
 int /*<<< orphan*/  log_err (char*) ; 
 scalar_t__ malloc (int) ; 
 scalar_t__ ub_event_add (int /*<<< orphan*/ ,struct timeval*) ; 
 int /*<<< orphan*/  ub_event_add_bits (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ub_event_del_bits (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ub_event_set_fd (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,int,int) ; 

void 
comm_point_start_listening(struct comm_point* c, int newfd, int msec)
{
	verbose(VERB_ALGO, "comm point start listening %d (%d msec)", 
		c->fd==-1?newfd:c->fd, msec);
	if(c->type == comm_tcp_accept && !c->tcp_free) {
		/* no use to start listening no free slots. */
		return;
	}
	if(msec != -1 && msec != 0) {
		if(!c->timeout) {
			c->timeout = (struct timeval*)malloc(sizeof(
				struct timeval));
			if(!c->timeout) {
				log_err("cpsl: malloc failed. No net read.");
				return;
			}
		}
		ub_event_add_bits(c->ev->ev, UB_EV_TIMEOUT);
#ifndef S_SPLINT_S /* splint fails on struct timeval. */
		c->timeout->tv_sec = msec/1000;
		c->timeout->tv_usec = (msec%1000)*1000;
#endif /* S_SPLINT_S */
	}
	if(c->type == comm_tcp || c->type == comm_http) {
		ub_event_del_bits(c->ev->ev, UB_EV_READ|UB_EV_WRITE);
		if(c->tcp_is_reading)
			ub_event_add_bits(c->ev->ev, UB_EV_READ);
		else	ub_event_add_bits(c->ev->ev, UB_EV_WRITE);
	}
	if(newfd != -1) {
		if(c->fd != -1) {
#ifndef USE_WINSOCK
			close(c->fd);
#else
			closesocket(c->fd);
#endif
		}
		c->fd = newfd;
		ub_event_set_fd(c->ev->ev, c->fd);
	}
	if(ub_event_add(c->ev->ev, msec==0?NULL:c->timeout) != 0) {
		log_err("event_add failed. in cpsl.");
	}
}