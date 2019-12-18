#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct request {struct request* current_req; struct request* handle; int /*<<< orphan*/  pending_cb; struct request* const request; int /*<<< orphan*/  request_appended; TYPE_1__* ns; struct evdns_base* base; int /*<<< orphan*/  timeout_event; } ;
struct evdns_base {scalar_t__ disable_when_inactive; int /*<<< orphan*/  global_requests_waiting; int /*<<< orphan*/  global_requests_inflight; struct request* req_waiting_head; } ;
struct TYPE_2__ {scalar_t__ requests_inflight; int /*<<< orphan*/  timeout_event; int /*<<< orphan*/  event; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_VALID_REQUEST (struct request* const) ; 
 int /*<<< orphan*/  EVDNS_LOCK (struct evdns_base*) ; 
 int /*<<< orphan*/  EVDNS_LOG_DEBUG ; 
 int /*<<< orphan*/  EVDNS_UNLOCK (struct evdns_base*) ; 
 int /*<<< orphan*/  EVUTIL_ASSERT (int) ; 
 int /*<<< orphan*/  evdns_request_remove (struct request* const,struct request**) ; 
 int /*<<< orphan*/  evdns_requests_pump_waiting_queue (struct evdns_base*) ; 
 int /*<<< orphan*/  event_debug_unassign (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evtimer_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,struct request* const) ; 
 int /*<<< orphan*/  mm_free (struct request* const) ; 
 int /*<<< orphan*/  search_request_finished (struct request*) ; 

__attribute__((used)) static void
request_finished(struct request *const req, struct request **head, int free_handle) {
	struct evdns_base *base = req->base;
	int was_inflight = (head != &base->req_waiting_head);
	EVDNS_LOCK(base);
	ASSERT_VALID_REQUEST(req);

	if (head)
		evdns_request_remove(req, head);

	log(EVDNS_LOG_DEBUG, "Removing timeout for request %p", req);
	if (was_inflight) {
		evtimer_del(&req->timeout_event);
		base->global_requests_inflight--;
		req->ns->requests_inflight--;
	} else {
		base->global_requests_waiting--;
	}
	/* it was initialized during request_new / evtimer_assign */
	event_debug_unassign(&req->timeout_event);

	if (req->ns &&
	    req->ns->requests_inflight == 0 &&
	    req->base->disable_when_inactive) {
		event_del(&req->ns->event);
		evtimer_del(&req->ns->timeout_event);
	}

	if (!req->request_appended) {
		/* need to free the request data on it's own */
		mm_free(req->request);
	} else {
		/* the request data is appended onto the header */
		/* so everything gets free()ed when we: */
	}

	if (req->handle) {
		EVUTIL_ASSERT(req->handle->current_req == req);

		if (free_handle) {
			search_request_finished(req->handle);
			req->handle->current_req = NULL;
			if (! req->handle->pending_cb) {
				/* If we're planning to run the callback,
				 * don't free the handle until later. */
				mm_free(req->handle);
			}
			req->handle = NULL; /* If we have a bug, let's crash
					     * early */
		} else {
			req->handle->current_req = NULL;
		}
	}

	mm_free(req);

	evdns_requests_pump_waiting_queue(base);
	EVDNS_UNLOCK(base);
}