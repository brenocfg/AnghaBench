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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct request {int dummy; } ;
struct in_addr {int /*<<< orphan*/  s_addr; } ;
struct evdns_request {int /*<<< orphan*/ * current_req; } ;
struct evdns_base {int dummy; } ;
typedef  int /*<<< orphan*/  evdns_callback_type ;
typedef  int /*<<< orphan*/  buf ;
typedef  scalar_t__ a ;

/* Variables and functions */
 int /*<<< orphan*/  EVDNS_LOCK (struct evdns_base*) ; 
 int /*<<< orphan*/  EVDNS_LOG_DEBUG ; 
 int /*<<< orphan*/  EVDNS_UNLOCK (struct evdns_base*) ; 
 int /*<<< orphan*/  EVUTIL_ASSERT (struct in_addr const*) ; 
 int /*<<< orphan*/  TYPE_PTR ; 
 int /*<<< orphan*/  evutil_snprintf (char*,int,char*,int,int,int,int) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,char*) ; 
 struct evdns_request* mm_calloc (int,int) ; 
 int /*<<< orphan*/  mm_free (struct evdns_request*) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 struct request* request_new (struct evdns_base*,struct evdns_request*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  request_submit (struct request*) ; 

struct evdns_request *
evdns_base_resolve_reverse(struct evdns_base *base, const struct in_addr *in, int flags, evdns_callback_type callback, void *ptr) {
	char buf[32];
	struct evdns_request *handle;
	struct request *req;
	u32 a;
	EVUTIL_ASSERT(in);
	a = ntohl(in->s_addr);
	evutil_snprintf(buf, sizeof(buf), "%d.%d.%d.%d.in-addr.arpa",
			(int)(u8)((a	)&0xff),
			(int)(u8)((a>>8 )&0xff),
			(int)(u8)((a>>16)&0xff),
			(int)(u8)((a>>24)&0xff));
	handle = mm_calloc(1, sizeof(*handle));
	if (handle == NULL)
		return NULL;
	log(EVDNS_LOG_DEBUG, "Resolve requested for %s (reverse)", buf);
	EVDNS_LOCK(base);
	req = request_new(base, handle, TYPE_PTR, buf, flags, callback, ptr);
	if (req)
		request_submit(req);
	if (handle->current_req == NULL) {
		mm_free(handle);
		handle = NULL;
	}
	EVDNS_UNLOCK(base);
	return (handle);
}