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
struct selectop {size_t event_fds; int /*<<< orphan*/ ** event_w_by_fd; int /*<<< orphan*/  event_writeset_in; int /*<<< orphan*/ ** event_r_by_fd; int /*<<< orphan*/  event_readset_in; } ;
struct event {int ev_events; size_t ev_fd; } ;

/* Variables and functions */
 int EV_READ ; 
 int EV_SIGNAL ; 
 int EV_WRITE ; 
 int /*<<< orphan*/  FD_CLR (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_selectop (struct selectop*) ; 
 int evsignal_del (struct event*) ; 

int
select_del(void *arg, struct event *ev)
{
	struct selectop *sop = arg;

	check_selectop(sop);
	if (ev->ev_events & EV_SIGNAL)
		return (evsignal_del(ev));

	if (sop->event_fds < ev->ev_fd) {
		check_selectop(sop);
		return (0);
	}

	if (ev->ev_events & EV_READ) {
		FD_CLR(ev->ev_fd, sop->event_readset_in);
		sop->event_r_by_fd[ev->ev_fd] = NULL;
	}

	if (ev->ev_events & EV_WRITE) {
		FD_CLR(ev->ev_fd, sop->event_writeset_in);
		sop->event_w_by_fd[ev->ev_fd] = NULL;
	}

	check_selectop(sop);
	return (0);
}