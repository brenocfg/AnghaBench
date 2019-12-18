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
struct pollop {int* idxplus1_by_fd; int nfds; struct pollfd* event_set; int /*<<< orphan*/ ** event_w_back; int /*<<< orphan*/ ** event_r_back; } ;
struct pollfd {int events; size_t fd; } ;
struct event {int ev_events; size_t ev_fd; } ;

/* Variables and functions */
 int EV_READ ; 
 int EV_SIGNAL ; 
 int EV_WRITE ; 
 int POLLIN ; 
 int POLLOUT ; 
 int evsignal_del (struct event*) ; 
 int /*<<< orphan*/  memcpy (struct pollfd*,struct pollfd*,int) ; 
 int /*<<< orphan*/  poll_check_ok (struct pollop*) ; 

int
poll_del(void *arg, struct event *ev)
{
	struct pollop *pop = arg;
	struct pollfd *pfd = NULL;
	int i;

	if (ev->ev_events & EV_SIGNAL)
		return (evsignal_del(ev));

	if (!(ev->ev_events & (EV_READ|EV_WRITE)))
		return (0);

	poll_check_ok(pop);
	i = pop->idxplus1_by_fd[ev->ev_fd] - 1;
	if (i < 0)
		return (-1);

	/* Do we still want to read or write? */
	pfd = &pop->event_set[i];
	if (ev->ev_events & EV_READ) {
		pfd->events &= ~POLLIN;
		pop->event_r_back[i] = NULL;
	}
	if (ev->ev_events & EV_WRITE) {
		pfd->events &= ~POLLOUT;
		pop->event_w_back[i] = NULL;
	}
	poll_check_ok(pop);
	if (pfd->events)
		/* Another event cares about that fd. */
		return (0);

	/* Okay, so we aren't interested in that fd anymore. */
	pop->idxplus1_by_fd[ev->ev_fd] = 0;

	--pop->nfds;
	if (i != pop->nfds) {
		/* 
		 * Shift the last pollfd down into the now-unoccupied
		 * position.
		 */
		memcpy(&pop->event_set[i], &pop->event_set[pop->nfds],
		       sizeof(struct pollfd));
		pop->event_r_back[i] = pop->event_r_back[pop->nfds];
		pop->event_w_back[i] = pop->event_w_back[pop->nfds];
		pop->idxplus1_by_fd[pop->event_set[i].fd] = i + 1;
	}

	poll_check_ok(pop);
	return (0);
}