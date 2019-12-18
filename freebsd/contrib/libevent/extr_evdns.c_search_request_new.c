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
typedef  char request ;
struct evdns_request {int search_index; int search_flags; TYPE_1__* search_state; int /*<<< orphan*/ * search_origname; int /*<<< orphan*/ * current_req; } ;
struct evdns_base {TYPE_1__* global_search_state; } ;
typedef  int /*<<< orphan*/  evdns_callback_type ;
struct TYPE_2__ {scalar_t__ ndots; int /*<<< orphan*/  refcount; scalar_t__ num_domains; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_LOCKED (struct evdns_base*) ; 
 int DNS_QUERY_NO_SEARCH ; 
 int /*<<< orphan*/  EVUTIL_ASSERT (int) ; 
 int TYPE_A ; 
 int TYPE_AAAA ; 
 int /*<<< orphan*/  mm_free (char* const) ; 
 int /*<<< orphan*/ * mm_strdup (char const* const) ; 
 void* request_new (struct evdns_base*,struct evdns_request*,int,char const* const,int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  request_submit (char* const) ; 
 char* search_make_new (TYPE_1__*,int /*<<< orphan*/ ,char const* const) ; 
 scalar_t__ string_num_dots (char const* const) ; 

__attribute__((used)) static struct request *
search_request_new(struct evdns_base *base, struct evdns_request *handle,
		   int type, const char *const name, int flags,
		   evdns_callback_type user_callback, void *user_arg) {
	ASSERT_LOCKED(base);
	EVUTIL_ASSERT(type == TYPE_A || type == TYPE_AAAA);
	EVUTIL_ASSERT(handle->current_req == NULL);
	if ( ((flags & DNS_QUERY_NO_SEARCH) == 0) &&
	     base->global_search_state &&
		 base->global_search_state->num_domains) {
		/* we have some domains to search */
		struct request *req;
		if (string_num_dots(name) >= base->global_search_state->ndots) {
			req = request_new(base, handle, type, name, flags, user_callback, user_arg);
			if (!req) return NULL;
			handle->search_index = -1;
		} else {
			char *const new_name = search_make_new(base->global_search_state, 0, name);
			if (!new_name) return NULL;
			req = request_new(base, handle, type, new_name, flags, user_callback, user_arg);
			mm_free(new_name);
			if (!req) return NULL;
			handle->search_index = 0;
		}
		EVUTIL_ASSERT(handle->search_origname == NULL);
		handle->search_origname = mm_strdup(name);
		if (handle->search_origname == NULL) {
			/* XXX Should we dealloc req? If yes, how? */
			if (req)
				mm_free(req);
			return NULL;
		}
		handle->search_state = base->global_search_state;
		handle->search_flags = flags;
		base->global_search_state->refcount++;
		request_submit(req);
		return req;
	} else {
		struct request *const req = request_new(base, handle, type, name, flags, user_callback, user_arg);
		if (!req) return NULL;
		request_submit(req);
		return req;
	}
}