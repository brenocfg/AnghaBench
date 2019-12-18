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
struct evbuffer {int deferred_cbs; int /*<<< orphan*/  deferred; struct event_base* cb_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVBUFFER_LOCK (struct evbuffer*) ; 
 int /*<<< orphan*/  EVBUFFER_UNLOCK (struct evbuffer*) ; 
 int /*<<< orphan*/  evbuffer_deferred_callback ; 
 int event_base_get_npriorities (struct event_base*) ; 
 int /*<<< orphan*/  event_deferred_cb_init_ (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct evbuffer*) ; 

int
evbuffer_defer_callbacks(struct evbuffer *buffer, struct event_base *base)
{
	EVBUFFER_LOCK(buffer);
	buffer->cb_queue = base;
	buffer->deferred_cbs = 1;
	event_deferred_cb_init_(&buffer->deferred,
	    event_base_get_npriorities(base) / 2,
	    evbuffer_deferred_callback, buffer);
	EVBUFFER_UNLOCK(buffer);
	return 0;
}