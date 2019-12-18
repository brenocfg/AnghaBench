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
struct selectop {int event_fds; int event_fdsz; struct event** event_w_by_fd; int /*<<< orphan*/  event_writeset_in; struct event** event_r_by_fd; int /*<<< orphan*/  event_readset_in; } ;
struct event {int ev_events; int ev_fd; } ;
typedef  int /*<<< orphan*/  fd_mask ;

/* Variables and functions */
 int EV_READ ; 
 int EV_SIGNAL ; 
 int EV_WRITE ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFDBITS ; 
 int /*<<< orphan*/  check_selectop (struct selectop*) ; 
 int evsignal_add (struct event*) ; 
 int howmany (int,int /*<<< orphan*/ ) ; 
 scalar_t__ select_resize (struct selectop*,int) ; 

int
select_add(void *arg, struct event *ev)
{
	struct selectop *sop = arg;

	if (ev->ev_events & EV_SIGNAL)
		return (evsignal_add(ev));

	check_selectop(sop);
	/*
	 * Keep track of the highest fd, so that we can calculate the size
	 * of the fd_sets for select(2)
	 */
	if (sop->event_fds < ev->ev_fd) {
		int fdsz = sop->event_fdsz;

		if (fdsz < sizeof(fd_mask))
			fdsz = sizeof(fd_mask);

		while (fdsz <
		    (howmany(ev->ev_fd + 1, NFDBITS) * sizeof(fd_mask)))
			fdsz *= 2;

		if (fdsz != sop->event_fdsz) {
			if (select_resize(sop, fdsz)) {
				check_selectop(sop);
				return (-1);
			}
		}

		sop->event_fds = ev->ev_fd;
	}

	if (ev->ev_events & EV_READ) {
		FD_SET(ev->ev_fd, sop->event_readset_in);
		sop->event_r_by_fd[ev->ev_fd] = ev;
	}
	if (ev->ev_events & EV_WRITE) {
		FD_SET(ev->ev_fd, sop->event_writeset_in);
		sop->event_w_by_fd[ev->ev_fd] = ev;
	}
	check_selectop(sop);

	return (0);
}