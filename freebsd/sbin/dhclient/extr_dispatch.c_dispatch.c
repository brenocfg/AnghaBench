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
typedef  int time_t ;
struct timeout {scalar_t__ when; struct timeout* next; int /*<<< orphan*/  what; int /*<<< orphan*/  (* func ) (int /*<<< orphan*/ ) ;} ;
struct protocol {int /*<<< orphan*/  (* handler ) (struct protocol*) ;struct interface_info* local; struct protocol* next; int /*<<< orphan*/  fd; } ;
struct pollfd {int events; int revents; int /*<<< orphan*/  fd; } ;
struct interface_info {scalar_t__ dead; } ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 int INT_MAX ; 
 int POLLHUP ; 
 int POLLIN ; 
 scalar_t__ cur_time ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error (char*) ; 
 struct timeout* free_timeouts ; 
 int /*<<< orphan*/  got_one (struct protocol*) ; 
 scalar_t__ interfaces_invalidated ; 
 struct pollfd* malloc (int) ; 
 int poll (struct pollfd*,int,int) ; 
 struct protocol* protocols ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct protocol*) ; 
 int /*<<< orphan*/  time (scalar_t__*) ; 
 struct timeout* timeouts ; 

void
dispatch(void)
{
	int count, live_interfaces, i, to_msec, nfds = 0;
	struct protocol *l;
	struct pollfd *fds;
	time_t howlong;

	for (l = protocols; l; l = l->next)
		nfds++;

	fds = malloc(nfds * sizeof(struct pollfd));
	if (fds == NULL)
		error("Can't allocate poll structures.");

	do {
		/*
		 * Call any expired timeouts, and then if there's still
		 * a timeout registered, time out the select call then.
		 */
another:
		if (timeouts) {
			struct timeout *t;

			if (timeouts->when <= cur_time) {
				t = timeouts;
				timeouts = timeouts->next;
				(*(t->func))(t->what);
				t->next = free_timeouts;
				free_timeouts = t;
				goto another;
			}

			/*
			 * Figure timeout in milliseconds, and check for
			 * potential overflow, so we can cram into an
			 * int for poll, while not polling with a
			 * negative timeout and blocking indefinitely.
			 */
			howlong = timeouts->when - cur_time;
			if (howlong > INT_MAX / 1000)
				howlong = INT_MAX / 1000;
			to_msec = howlong * 1000;
		} else
			to_msec = -1;

		/* Set up the descriptors to be polled. */
		live_interfaces = 0;
		for (i = 0, l = protocols; l; l = l->next) {
			struct interface_info *ip = l->local;

			if (ip == NULL || ip->dead)
				continue;
			fds[i].fd = l->fd;
			fds[i].events = POLLIN;
			fds[i].revents = 0;
			i++;
			if (l->handler == got_one)
				live_interfaces++;
		}
		if (live_interfaces == 0)
			error("No live interfaces to poll on - exiting.");

		/* Wait for a packet or a timeout... XXX */
		count = poll(fds, nfds, to_msec);

		/* Not likely to be transitory... */
		if (count == -1) {
			if (errno == EAGAIN || errno == EINTR) {
				time(&cur_time);
				continue;
			} else
				error("poll: %m");
		}

		/* Get the current time... */
		time(&cur_time);

		i = 0;
		for (l = protocols; l; l = l->next) {
			struct interface_info *ip;
			ip = l->local;
			if ((fds[i].revents & (POLLIN | POLLHUP))) {
				fds[i].revents = 0;
				if (ip && (l->handler != got_one ||
				    !ip->dead))
					(*(l->handler))(l);
				if (interfaces_invalidated)
					break;
			}
			i++;
		}
		interfaces_invalidated = 0;
	} while (1);
}