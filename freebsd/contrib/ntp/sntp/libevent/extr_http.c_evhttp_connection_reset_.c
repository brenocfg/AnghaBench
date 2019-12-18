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
struct evhttp_connection {int fd; int /*<<< orphan*/  state; int /*<<< orphan*/  bufev; int /*<<< orphan*/  closecb_arg; int /*<<< orphan*/  (* closecb ) (struct evhttp_connection*,int /*<<< orphan*/ ) ;} ;
struct evbuffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVCON_DISCONNECTED ; 
 int /*<<< orphan*/  EVUTIL_SHUT_WR ; 
 int EV_READ ; 
 int EV_WRITE ; 
 int /*<<< orphan*/  bufferevent_disable_hard_ (int /*<<< orphan*/ ,int) ; 
 struct evbuffer* bufferevent_get_input (int /*<<< orphan*/ ) ; 
 struct evbuffer* bufferevent_get_output (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufferevent_setfd (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  evbuffer_drain (struct evbuffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evbuffer_get_length (struct evbuffer*) ; 
 scalar_t__ evhttp_connected (struct evhttp_connection*) ; 
 int /*<<< orphan*/  evutil_closesocket (int) ; 
 int /*<<< orphan*/  shutdown (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct evhttp_connection*,int /*<<< orphan*/ ) ; 

void
evhttp_connection_reset_(struct evhttp_connection *evcon)
{
	struct evbuffer *tmp;

	/* XXXX This is not actually an optimal fix.  Instead we ought to have
	   an API for "stop connecting", or use bufferevent_setfd to turn off
	   connecting.  But for Libevent 2.0, this seems like a minimal change
	   least likely to disrupt the rest of the bufferevent and http code.

	   Why is this here?  If the fd is set in the bufferevent, and the
	   bufferevent is connecting, then you can't actually stop the
	   bufferevent from trying to connect with bufferevent_disable().  The
	   connect will never trigger, since we close the fd, but the timeout
	   might.  That caused an assertion failure in evhttp_connection_fail_.
	*/
	bufferevent_disable_hard_(evcon->bufev, EV_READ|EV_WRITE);

	if (evcon->fd != -1) {
		/* inform interested parties about connection close */
		if (evhttp_connected(evcon) && evcon->closecb != NULL)
			(*evcon->closecb)(evcon, evcon->closecb_arg);

		shutdown(evcon->fd, EVUTIL_SHUT_WR);
		evutil_closesocket(evcon->fd);
		bufferevent_setfd(evcon->bufev, -1);
		evcon->fd = -1;
	}

	/* we need to clean up any buffered data */
	tmp = bufferevent_get_output(evcon->bufev);
	evbuffer_drain(tmp, evbuffer_get_length(tmp));
	tmp = bufferevent_get_input(evcon->bufev);
	evbuffer_drain(tmp, evbuffer_get_length(tmp));

	evcon->state = EVCON_DISCONNECTED;
}