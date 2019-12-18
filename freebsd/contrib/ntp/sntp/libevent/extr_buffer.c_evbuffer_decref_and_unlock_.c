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
struct evbuffer_chain {struct evbuffer_chain* next; } ;
struct evbuffer {scalar_t__ refcnt; int /*<<< orphan*/  lock; scalar_t__ own_lock; int /*<<< orphan*/  deferred; int /*<<< orphan*/  cb_queue; scalar_t__ deferred_cbs; struct evbuffer_chain* first; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_EVBUFFER_LOCKED (struct evbuffer*) ; 
 int /*<<< orphan*/  EVBUFFER_UNLOCK (struct evbuffer*) ; 
 int /*<<< orphan*/  EVTHREAD_FREE_LOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVTHREAD_LOCKTYPE_RECURSIVE ; 
 int /*<<< orphan*/  EVUTIL_ASSERT (int) ; 
 int /*<<< orphan*/  evbuffer_chain_free (struct evbuffer_chain*) ; 
 int /*<<< orphan*/  evbuffer_remove_all_callbacks (struct evbuffer*) ; 
 int /*<<< orphan*/  event_deferred_cb_cancel_ (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mm_free (struct evbuffer*) ; 

void
evbuffer_decref_and_unlock_(struct evbuffer *buffer)
{
	struct evbuffer_chain *chain, *next;
	ASSERT_EVBUFFER_LOCKED(buffer);

	EVUTIL_ASSERT(buffer->refcnt > 0);

	if (--buffer->refcnt > 0) {
		EVBUFFER_UNLOCK(buffer);
		return;
	}

	for (chain = buffer->first; chain != NULL; chain = next) {
		next = chain->next;
		evbuffer_chain_free(chain);
	}
	evbuffer_remove_all_callbacks(buffer);
	if (buffer->deferred_cbs)
		event_deferred_cb_cancel_(buffer->cb_queue, &buffer->deferred);

	EVBUFFER_UNLOCK(buffer);
	if (buffer->own_lock)
		EVTHREAD_FREE_LOCK(buffer->lock, EVTHREAD_LOCKTYPE_RECURSIVE);
	mm_free(buffer);
}