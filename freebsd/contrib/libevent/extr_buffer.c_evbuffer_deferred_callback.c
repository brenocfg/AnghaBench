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
struct event_callback {int dummy; } ;
struct evbuffer {struct bufferevent* parent; } ;
struct bufferevent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVBUFFER_LOCK (struct evbuffer*) ; 
 int /*<<< orphan*/  bufferevent_decref_ (struct bufferevent*) ; 
 int /*<<< orphan*/  evbuffer_decref_and_unlock_ (struct evbuffer*) ; 
 int /*<<< orphan*/  evbuffer_run_callbacks (struct evbuffer*,int) ; 

__attribute__((used)) static void
evbuffer_deferred_callback(struct event_callback *cb, void *arg)
{
	struct bufferevent *parent = NULL;
	struct evbuffer *buffer = arg;

	/* XXXX It would be better to run these callbacks without holding the
	 * lock */
	EVBUFFER_LOCK(buffer);
	parent = buffer->parent;
	evbuffer_run_callbacks(buffer, 1);
	evbuffer_decref_and_unlock_(buffer);
	if (parent)
		bufferevent_decref_(parent);
}