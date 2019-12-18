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
struct evmap_io {int nread; int nwrite; int nclose; int /*<<< orphan*/  events; } ;
struct eventop {int (* add ) (struct event_base*,scalar_t__,short,short,void*) ;int /*<<< orphan*/  fdinfo_len; } ;
struct event_io_map {scalar_t__ nentries; } ;
struct event_base {struct event_io_map io; struct eventop* evsel; } ;
struct event {scalar_t__ ev_fd; short ev_events; } ;
typedef  scalar_t__ evutil_socket_t ;
typedef  void* ev_uint16_t ;

/* Variables and functions */
 scalar_t__ EVENT_DEBUG_MODE_IS_ON () ; 
 int /*<<< orphan*/  EVUTIL_ASSERT (int) ; 
 scalar_t__ EVUTIL_UNLIKELY (int) ; 
 short EV_CLOSED ; 
 short EV_ET ; 
 short EV_READ ; 
 short EV_WRITE ; 
 int /*<<< orphan*/  GET_IO_SLOT_AND_CTOR (struct evmap_io*,struct event_io_map*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct event* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ev_io_next ; 
 int /*<<< orphan*/  event_warnx (char*,int) ; 
 int /*<<< orphan*/  evmap_io ; 
 int /*<<< orphan*/  evmap_io_init ; 
 int evmap_make_space (struct event_io_map*,scalar_t__,int) ; 
 int stub1 (struct event_base*,scalar_t__,short,short,void*) ; 

int
evmap_io_add_(struct event_base *base, evutil_socket_t fd, struct event *ev)
{
	const struct eventop *evsel = base->evsel;
	struct event_io_map *io = &base->io;
	struct evmap_io *ctx = NULL;
	int nread, nwrite, nclose, retval = 0;
	short res = 0, old = 0;
	struct event *old_ev;

	EVUTIL_ASSERT(fd == ev->ev_fd);

	if (fd < 0)
		return 0;

#ifndef EVMAP_USE_HT
	if (fd >= io->nentries) {
		if (evmap_make_space(io, fd, sizeof(struct evmap_io *)) == -1)
			return (-1);
	}
#endif
	GET_IO_SLOT_AND_CTOR(ctx, io, fd, evmap_io, evmap_io_init,
						 evsel->fdinfo_len);

	nread = ctx->nread;
	nwrite = ctx->nwrite;
	nclose = ctx->nclose;

	if (nread)
		old |= EV_READ;
	if (nwrite)
		old |= EV_WRITE;
	if (nclose)
		old |= EV_CLOSED;

	if (ev->ev_events & EV_READ) {
		if (++nread == 1)
			res |= EV_READ;
	}
	if (ev->ev_events & EV_WRITE) {
		if (++nwrite == 1)
			res |= EV_WRITE;
	}
	if (ev->ev_events & EV_CLOSED) {
		if (++nclose == 1)
			res |= EV_CLOSED;
	}
	if (EVUTIL_UNLIKELY(nread > 0xffff || nwrite > 0xffff || nclose > 0xffff)) {
		event_warnx("Too many events reading or writing on fd %d",
		    (int)fd);
		return -1;
	}
	if (EVENT_DEBUG_MODE_IS_ON() &&
	    (old_ev = LIST_FIRST(&ctx->events)) &&
	    (old_ev->ev_events&EV_ET) != (ev->ev_events&EV_ET)) {
		event_warnx("Tried to mix edge-triggered and non-edge-triggered"
		    " events on fd %d", (int)fd);
		return -1;
	}

	if (res) {
		void *extra = ((char*)ctx) + sizeof(struct evmap_io);
		/* XXX(niels): we cannot mix edge-triggered and
		 * level-triggered, we should probably assert on
		 * this. */
		if (evsel->add(base, ev->ev_fd,
			old, (ev->ev_events & EV_ET) | res, extra) == -1)
			return (-1);
		retval = 1;
	}

	ctx->nread = (ev_uint16_t) nread;
	ctx->nwrite = (ev_uint16_t) nwrite;
	ctx->nclose = (ev_uint16_t) nclose;
	LIST_INSERT_HEAD(&ctx->events, ev, ev_io_next);

	return (retval);
}