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
struct rsocket {scalar_t__ type; int state; TYPE_2__* cm_id; } ;
struct pollfd {int events; int revents; int /*<<< orphan*/  fd; } ;
struct TYPE_4__ {TYPE_1__* channel; } ;
struct TYPE_3__ {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 scalar_t__ EINPROGRESS ; 
 short POLLERR ; 
 short POLLHUP ; 
 int POLLIN ; 
 int POLLOUT ; 
 scalar_t__ SOCK_DGRAM ; 
 scalar_t__ SOCK_STREAM ; 
 scalar_t__ ds_can_send (struct rsocket*) ; 
 int /*<<< orphan*/  ds_process_cqs (struct rsocket*,int,int (*) (struct rsocket*)) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  poll (struct pollfd*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ rs_can_send (struct rsocket*) ; 
 scalar_t__ rs_conn_have_rdata (struct rsocket*) ; 
 int rs_connect_error ; 
 int rs_connected ; 
 int rs_disconnected ; 
 int rs_do_connect (struct rsocket*) ; 
 int rs_error ; 
 scalar_t__ rs_have_rdata (struct rsocket*) ; 
 int rs_listening ; 
 int rs_opening ; 
 int /*<<< orphan*/  rs_process_cq (struct rsocket*,int,int (*) (struct rsocket*)) ; 

__attribute__((used)) static int rs_poll_rs(struct rsocket *rs, int events,
		      int nonblock, int (*test)(struct rsocket *rs))
{
	struct pollfd fds;
	short revents;
	int ret;

check_cq:
	if ((rs->type == SOCK_STREAM) && ((rs->state & rs_connected) ||
	     (rs->state == rs_disconnected) || (rs->state & rs_error))) {
		rs_process_cq(rs, nonblock, test);

		revents = 0;
		if ((events & POLLIN) && rs_conn_have_rdata(rs))
			revents |= POLLIN;
		if ((events & POLLOUT) && rs_can_send(rs))
			revents |= POLLOUT;
		if (!(rs->state & rs_connected)) {
			if (rs->state == rs_disconnected)
				revents |= POLLHUP;
			else
				revents |= POLLERR;
		}

		return revents;
	} else if (rs->type == SOCK_DGRAM) {
		ds_process_cqs(rs, nonblock, test);

		revents = 0;
		if ((events & POLLIN) && rs_have_rdata(rs))
			revents |= POLLIN;
		if ((events & POLLOUT) && ds_can_send(rs))
			revents |= POLLOUT;

		return revents;
	}

	if (rs->state == rs_listening) {
		fds.fd = rs->cm_id->channel->fd;
		fds.events = events;
		fds.revents = 0;
		poll(&fds, 1, 0);
		return fds.revents;
	}

	if (rs->state & rs_opening) {
		ret = rs_do_connect(rs);
		if (ret && (errno == EINPROGRESS)) {
			errno = 0;
		} else {
			goto check_cq;
		}
	}

	if (rs->state == rs_connect_error) {
		revents = 0;
		if (events & POLLOUT)
			revents |= POLLOUT;
		if (events & POLLIN)
			revents |= POLLIN;
		revents |= POLLERR;
		return revents;
	}

	return 0;
}