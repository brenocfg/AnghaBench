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
struct evhttp_connection {int /*<<< orphan*/  read_more_deferred_cb; int /*<<< orphan*/  bufev; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVCON_READING_FIRSTLINE ; 
 int /*<<< orphan*/  EV_READ ; 
 int /*<<< orphan*/  EV_WRITE ; 
 int /*<<< orphan*/  bufferevent_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufferevent_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufferevent_get_input (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufferevent_setcb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct evhttp_connection*) ; 
 scalar_t__ evbuffer_get_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_deferred_cb_schedule_ (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evhttp_error_cb ; 
 int /*<<< orphan*/  evhttp_read_cb ; 
 int /*<<< orphan*/  evhttp_write_cb ; 
 int /*<<< orphan*/  get_deferred_queue (struct evhttp_connection*) ; 

void
evhttp_start_read_(struct evhttp_connection *evcon)
{
	bufferevent_disable(evcon->bufev, EV_WRITE);
	bufferevent_enable(evcon->bufev, EV_READ);

	evcon->state = EVCON_READING_FIRSTLINE;
	/* Reset the bufferevent callbacks */
	bufferevent_setcb(evcon->bufev,
	    evhttp_read_cb,
	    evhttp_write_cb,
	    evhttp_error_cb,
	    evcon);

	/* If there's still data pending, process it next time through the
	 * loop.  Don't do it now; that could get recusive. */
	if (evbuffer_get_length(bufferevent_get_input(evcon->bufev))) {
		event_deferred_cb_schedule_(get_deferred_queue(evcon),
		    &evcon->read_more_deferred_cb);
	}
}