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
struct evmap_signal {int /*<<< orphan*/  events; } ;
struct eventop {int (* del ) (struct event_base*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct event_signal_map {int nentries; } ;
struct event_base {struct event_signal_map sigmap; struct eventop* evsigsel; } ;
struct event {int /*<<< orphan*/  ev_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_SIGNAL ; 
 int /*<<< orphan*/  GET_SIGNAL_SLOT (struct evmap_signal*,struct event_signal_map*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ev_signal_next ; 
 int /*<<< orphan*/  evmap_signal ; 
 int stub1 (struct event_base*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
evmap_signal_del_(struct event_base *base, int sig, struct event *ev)
{
	const struct eventop *evsel = base->evsigsel;
	struct event_signal_map *map = &base->sigmap;
	struct evmap_signal *ctx;

	if (sig < 0 || sig >= map->nentries)
		return (-1);

	GET_SIGNAL_SLOT(ctx, map, sig, evmap_signal);

	LIST_REMOVE(ev, ev_signal_next);

	if (LIST_FIRST(&ctx->events) == NULL) {
		if (evsel->del(base, ev->ev_fd, 0, EV_SIGNAL, NULL) == -1)
			return (-1);
	}

	return (1);
}