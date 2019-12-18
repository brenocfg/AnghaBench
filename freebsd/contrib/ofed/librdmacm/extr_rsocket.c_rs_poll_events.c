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
struct rsocket {scalar_t__ type; int /*<<< orphan*/  cq_wait_lock; } ;
struct pollfd {scalar_t__ revents; int /*<<< orphan*/  events; int /*<<< orphan*/  fd; } ;
typedef  int nfds_t ;

/* Variables and functions */
 scalar_t__ SOCK_STREAM ; 
 int /*<<< orphan*/  ds_get_cq_event (struct rsocket*) ; 
 int /*<<< orphan*/  fastlock_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fastlock_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idm ; 
 struct rsocket* idm_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rs_get_cq_event (struct rsocket*) ; 
 int /*<<< orphan*/  rs_poll_all ; 
 scalar_t__ rs_poll_rs (struct rsocket*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rs_poll_events(struct pollfd *rfds, struct pollfd *fds, nfds_t nfds)
{
	struct rsocket *rs;
	int i, cnt = 0;

	for (i = 0; i < nfds; i++) {
		if (!rfds[i].revents)
			continue;

		rs = idm_lookup(&idm, fds[i].fd);
		if (rs) {
			fastlock_acquire(&rs->cq_wait_lock);
			if (rs->type == SOCK_STREAM)
				rs_get_cq_event(rs);
			else
				ds_get_cq_event(rs);
			fastlock_release(&rs->cq_wait_lock);
			fds[i].revents = rs_poll_rs(rs, fds[i].events, 1, rs_poll_all);
		} else {
			fds[i].revents = rfds[i].revents;
		}
		if (fds[i].revents)
			cnt++;
	}
	return cnt;
}