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
struct event_base {int dummy; } ;
struct bufferevent {int /*<<< orphan*/  output; int /*<<< orphan*/  input; int /*<<< orphan*/  ev_base; int /*<<< orphan*/  ev_write; int /*<<< orphan*/  ev_read; } ;
struct bufferevent_private {struct bufferevent bev; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVBUFFER_FLAG_DRAINS_TO_FD ; 
 int EV_FINALIZE ; 
 int EV_PERSIST ; 
 int EV_READ ; 
 int EV_WRITE ; 
 struct bufferevent* bufferevent_async_new_ (struct event_base*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bufferevent_init_common_ (struct bufferevent_private*,struct event_base*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bufferevent_ops_socket ; 
 int /*<<< orphan*/  bufferevent_readcb ; 
 int /*<<< orphan*/  bufferevent_socket_outbuf_cb ; 
 int /*<<< orphan*/  bufferevent_writecb ; 
 int /*<<< orphan*/  evbuffer_add_cb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bufferevent*) ; 
 int /*<<< orphan*/  evbuffer_freeze (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  evbuffer_set_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_assign (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct bufferevent*) ; 
 scalar_t__ event_base_get_iocp_ (struct event_base*) ; 
 struct bufferevent_private* mm_calloc (int,int) ; 
 int /*<<< orphan*/  mm_free (struct bufferevent_private*) ; 

struct bufferevent *
bufferevent_socket_new(struct event_base *base, evutil_socket_t fd,
    int options)
{
	struct bufferevent_private *bufev_p;
	struct bufferevent *bufev;

#ifdef _WIN32
	if (base && event_base_get_iocp_(base))
		return bufferevent_async_new_(base, fd, options);
#endif

	if ((bufev_p = mm_calloc(1, sizeof(struct bufferevent_private)))== NULL)
		return NULL;

	if (bufferevent_init_common_(bufev_p, base, &bufferevent_ops_socket,
				    options) < 0) {
		mm_free(bufev_p);
		return NULL;
	}
	bufev = &bufev_p->bev;
	evbuffer_set_flags(bufev->output, EVBUFFER_FLAG_DRAINS_TO_FD);

	event_assign(&bufev->ev_read, bufev->ev_base, fd,
	    EV_READ|EV_PERSIST|EV_FINALIZE, bufferevent_readcb, bufev);
	event_assign(&bufev->ev_write, bufev->ev_base, fd,
	    EV_WRITE|EV_PERSIST|EV_FINALIZE, bufferevent_writecb, bufev);

	evbuffer_add_cb(bufev->output, bufferevent_socket_outbuf_cb, bufev);

	evbuffer_freeze(bufev->input, 0);
	evbuffer_freeze(bufev->output, 1);

	return bufev;
}