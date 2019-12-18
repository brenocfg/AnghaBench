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
struct request {scalar_t__ tx_count; struct request* next; struct nameserver* const ns; } ;
struct nameserver {int failed_times; int /*<<< orphan*/  address; int /*<<< orphan*/  timeout_event; scalar_t__ state; struct evdns_base* base; } ;
struct evdns_base {scalar_t__ global_good_nameservers; int n_req_heads; struct request** req_heads; int /*<<< orphan*/  global_nameserver_probe_initial_timeout; } ;
typedef  int /*<<< orphan*/  addrbuf ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_LOCKED (struct evdns_base*) ; 
 int /*<<< orphan*/  EVDNS_LOG_MSG ; 
 int /*<<< orphan*/  EVDNS_LOG_WARN ; 
 int /*<<< orphan*/  EVUTIL_ASSERT (int) ; 
 scalar_t__ evtimer_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evutil_format_sockaddr_port_ (struct sockaddr*,char*,int) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  nameserver_pick (struct evdns_base*) ; 
 int /*<<< orphan*/  request_swap_ns (struct request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nameserver_failed(struct nameserver *const ns, const char *msg) {
	struct request *req, *started_at;
	struct evdns_base *base = ns->base;
	int i;
	char addrbuf[128];

	ASSERT_LOCKED(base);
	/* if this nameserver has already been marked as failed */
	/* then don't do anything */
	if (!ns->state) return;

	log(EVDNS_LOG_MSG, "Nameserver %s has failed: %s",
	    evutil_format_sockaddr_port_(
		    (struct sockaddr *)&ns->address,
		    addrbuf, sizeof(addrbuf)),
	    msg);

	base->global_good_nameservers--;
	EVUTIL_ASSERT(base->global_good_nameservers >= 0);
	if (base->global_good_nameservers == 0) {
		log(EVDNS_LOG_MSG, "All nameservers have failed");
	}

	ns->state = 0;
	ns->failed_times = 1;

	if (evtimer_add(&ns->timeout_event,
		&base->global_nameserver_probe_initial_timeout) < 0) {
		log(EVDNS_LOG_WARN,
		    "Error from libevent when adding timer event for %s",
		    evutil_format_sockaddr_port_(
			    (struct sockaddr *)&ns->address,
			    addrbuf, sizeof(addrbuf)));
		/* ???? Do more? */
	}

	/* walk the list of inflight requests to see if any can be reassigned to */
	/* a different server. Requests in the waiting queue don't have a */
	/* nameserver assigned yet */

	/* if we don't have *any* good nameservers then there's no point */
	/* trying to reassign requests to one */
	if (!base->global_good_nameservers) return;

	for (i = 0; i < base->n_req_heads; ++i) {
		req = started_at = base->req_heads[i];
		if (req) {
			do {
				if (req->tx_count == 0 && req->ns == ns) {
					/* still waiting to go out, can be moved */
					/* to another server */
					request_swap_ns(req, nameserver_pick(base));
				}
				req = req->next;
			} while (req != started_at);
		}
	}
}