#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct event {int dummy; } ;
struct TYPE_4__ {int resp_read_pipe; struct event* resp_read_ctx; } ;
typedef  TYPE_1__ blocking_child ;

/* Variables and functions */
 int EV_PERSIST ; 
 int EV_READ ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  base ; 
 TYPE_1__** blocking_children ; 
 size_t blocking_children_alloc ; 
 int /*<<< orphan*/  event_add (struct event*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_del (struct event*) ; 
 int /*<<< orphan*/  event_free (struct event*) ; 
 struct event* event_new (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  worker_resp_cb ; 

void sntp_addremove_fd(
	int	fd,
	int	is_pipe,
	int	remove_it
	)
{
	u_int		idx;
	blocking_child *c;
	struct event *	ev;

#ifdef HAVE_SOCKETPAIR
	if (is_pipe) {
		/* sntp only asks for EV_FEATURE_FDS without HAVE_SOCKETPAIR */
		msyslog(LOG_ERR, "fatal: pipes not supported on systems with socketpair()");
		exit(1);
	}
#endif

	c = NULL;
	for (idx = 0; idx < blocking_children_alloc; idx++) {
		c = blocking_children[idx];
		if (NULL == c)
			continue;
		if (fd == c->resp_read_pipe)
			break;
	}
	if (idx == blocking_children_alloc)
		return;

	if (remove_it) {
		ev = c->resp_read_ctx;
		c->resp_read_ctx = NULL;
		event_del(ev);
		event_free(ev);

		return;
	}

	ev = event_new(base, fd, EV_READ | EV_PERSIST,
		       &worker_resp_cb, c);
	if (NULL == ev) {
		msyslog(LOG_ERR,
			"sntp_addremove_fd: event_new(base, fd) failed!");
		return;
	}
	c->resp_read_ctx = ev;
	event_add(ev, NULL);
}