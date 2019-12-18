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
struct evbuffer {scalar_t__ parent; int /*<<< orphan*/  deferred; int /*<<< orphan*/  cb_queue; scalar_t__ deferred_cbs; scalar_t__ n_del_for_cb; scalar_t__ n_add_for_cb; int /*<<< orphan*/  callbacks; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVBUFFER_UNLOCK (struct evbuffer*) ; 
 scalar_t__ LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bufferevent_incref_ (scalar_t__) ; 
 int /*<<< orphan*/  evbuffer_incref_and_lock_ (struct evbuffer*) ; 
 int /*<<< orphan*/  evbuffer_run_callbacks (struct evbuffer*,int /*<<< orphan*/ ) ; 
 scalar_t__ event_deferred_cb_schedule_ (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
evbuffer_invoke_callbacks_(struct evbuffer *buffer)
{
	if (LIST_EMPTY(&buffer->callbacks)) {
		buffer->n_add_for_cb = buffer->n_del_for_cb = 0;
		return;
	}

	if (buffer->deferred_cbs) {
		if (event_deferred_cb_schedule_(buffer->cb_queue, &buffer->deferred)) {
			evbuffer_incref_and_lock_(buffer);
			if (buffer->parent)
				bufferevent_incref_(buffer->parent);
		}
		EVBUFFER_UNLOCK(buffer);
	}

	evbuffer_run_callbacks(buffer, 0);
}