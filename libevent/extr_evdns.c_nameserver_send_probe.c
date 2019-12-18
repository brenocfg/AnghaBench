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
struct sockaddr {int dummy; } ;
struct request {struct nameserver* ns; } ;
struct nameserver {int /*<<< orphan*/  base; struct evdns_request* probe_request; int /*<<< orphan*/  address; } ;
struct evdns_request {int dummy; } ;
typedef  int /*<<< orphan*/  addrbuf ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_LOCKED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DNS_QUERY_NO_SEARCH ; 
 int /*<<< orphan*/  EVDNS_LOG_DEBUG ; 
 int /*<<< orphan*/  TYPE_A ; 
 int /*<<< orphan*/  evutil_format_sockaddr_port_ (struct sockaddr*,char*,int) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct evdns_request* mm_calloc (int,int) ; 
 int /*<<< orphan*/  mm_free (struct evdns_request*) ; 
 int /*<<< orphan*/  nameserver_probe_callback ; 
 struct request* request_new (int /*<<< orphan*/ ,struct evdns_request*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nameserver* const) ; 
 int /*<<< orphan*/  request_submit (struct request*) ; 
 int /*<<< orphan*/  request_trans_id_set (struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transaction_id_pick (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nameserver_send_probe(struct nameserver *const ns) {
	struct evdns_request *handle;
	struct request *req;
	char addrbuf[128];
	/* here we need to send a probe to a given nameserver */
	/* in the hope that it is up now. */

	ASSERT_LOCKED(ns->base);
	log(EVDNS_LOG_DEBUG, "Sending probe to %s",
	    evutil_format_sockaddr_port_(
		    (struct sockaddr *)&ns->address,
		    addrbuf, sizeof(addrbuf)));
	handle = mm_calloc(1, sizeof(*handle));
	if (!handle) return;
	req = request_new(ns->base, handle, TYPE_A, "google.com", DNS_QUERY_NO_SEARCH, nameserver_probe_callback, ns);
	if (!req) {
		mm_free(handle);
		return;
	}
	ns->probe_request = handle;
	/* we force this into the inflight queue no matter what */
	request_trans_id_set(req, transaction_id_pick(ns->base));
	req->ns = ns;
	request_submit(req);
}