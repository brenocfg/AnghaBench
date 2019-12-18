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
struct request {int dummy; } ;
struct evdns_request {int /*<<< orphan*/ * current_req; } ;
struct evdns_base {int dummy; } ;
typedef  int /*<<< orphan*/  evdns_callback_type ;

/* Variables and functions */
 int DNS_QUERY_NO_SEARCH ; 
 int /*<<< orphan*/  EVDNS_LOCK (struct evdns_base*) ; 
 int /*<<< orphan*/  EVDNS_LOG_DEBUG ; 
 int /*<<< orphan*/  EVDNS_UNLOCK (struct evdns_base*) ; 
 int /*<<< orphan*/  TYPE_A ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,char const*) ; 
 struct evdns_request* mm_calloc (int,int) ; 
 int /*<<< orphan*/  mm_free (struct evdns_request*) ; 
 struct request* request_new (struct evdns_base*,struct evdns_request*,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  request_submit (struct request*) ; 
 int /*<<< orphan*/  search_request_new (struct evdns_base*,struct evdns_request*,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ,void*) ; 

struct evdns_request *
evdns_base_resolve_ipv4(struct evdns_base *base, const char *name, int flags,
    evdns_callback_type callback, void *ptr) {
	struct evdns_request *handle;
	struct request *req;
	log(EVDNS_LOG_DEBUG, "Resolve requested for %s", name);
	handle = mm_calloc(1, sizeof(*handle));
	if (handle == NULL)
		return NULL;
	EVDNS_LOCK(base);
	if (flags & DNS_QUERY_NO_SEARCH) {
		req =
			request_new(base, handle, TYPE_A, name, flags,
				    callback, ptr);
		if (req)
			request_submit(req);
	} else {
		search_request_new(base, handle, TYPE_A, name, flags,
		    callback, ptr);
	}
	if (handle->current_req == NULL) {
		mm_free(handle);
		handle = NULL;
	}
	EVDNS_UNLOCK(base);
	return handle;
}