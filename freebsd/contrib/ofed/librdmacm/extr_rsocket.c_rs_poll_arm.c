#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rsocket {scalar_t__ type; scalar_t__ state; int /*<<< orphan*/  epfd; TYPE_3__* cm_id; } ;
struct pollfd {scalar_t__ revents; int /*<<< orphan*/  events; int /*<<< orphan*/  fd; } ;
typedef  int nfds_t ;
struct TYPE_6__ {TYPE_2__* channel; TYPE_1__* recv_cq_channel; } ;
struct TYPE_5__ {int /*<<< orphan*/  fd; } ;
struct TYPE_4__ {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  POLLIN ; 
 scalar_t__ SOCK_STREAM ; 
 int /*<<< orphan*/  idm ; 
 struct rsocket* idm_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ rs_connected ; 
 int /*<<< orphan*/  rs_is_cq_armed ; 
 scalar_t__ rs_poll_rs (struct rsocket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rs_poll_arm(struct pollfd *rfds, struct pollfd *fds, nfds_t nfds)
{
	struct rsocket *rs;
	int i;

	for (i = 0; i < nfds; i++) {
		rs = idm_lookup(&idm, fds[i].fd);
		if (rs) {
			fds[i].revents = rs_poll_rs(rs, fds[i].events, 0, rs_is_cq_armed);
			if (fds[i].revents)
				return 1;

			if (rs->type == SOCK_STREAM) {
				if (rs->state >= rs_connected)
					rfds[i].fd = rs->cm_id->recv_cq_channel->fd;
				else
					rfds[i].fd = rs->cm_id->channel->fd;
			} else {
				rfds[i].fd = rs->epfd;
			}
			rfds[i].events = POLLIN;
		} else {
			rfds[i].fd = fds[i].fd;
			rfds[i].events = fds[i].events;
		}
		rfds[i].revents = 0;
	}
	return 0;
}