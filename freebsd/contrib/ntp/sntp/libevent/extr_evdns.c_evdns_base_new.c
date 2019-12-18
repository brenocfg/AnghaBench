#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct event_base {int dummy; } ;
struct TYPE_6__ {int tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_5__ {int tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_4__ {int tv_sec; scalar_t__ tv_usec; } ;
struct evdns_base {int global_max_reissues; int global_max_retransmits; int global_max_nameserver_timeout; int global_randomize_case; int disable_when_inactive; int /*<<< orphan*/  hostsdb; TYPE_3__ global_nameserver_probe_initial_timeout; TYPE_2__ global_getaddrinfo_allow_skew; int /*<<< orphan*/ * global_search_state; TYPE_1__ global_timeout; scalar_t__ global_requests_waiting; scalar_t__ global_requests_inflight; scalar_t__ global_good_nameservers; struct event_base* event_base; int /*<<< orphan*/ * server_head; int /*<<< orphan*/ * req_heads; int /*<<< orphan*/  lock; int /*<<< orphan*/ * req_waiting_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  DNS_OPTIONS_ALL ; 
 int EVDNS_BASE_ALL_FLAGS ; 
 int EVDNS_BASE_DISABLE_WHEN_INACTIVE ; 
 int EVDNS_BASE_INITIALIZE_NAMESERVERS ; 
 int /*<<< orphan*/  EVDNS_LOCK (struct evdns_base*) ; 
 int /*<<< orphan*/  EVDNS_LOG_WARN ; 
 int /*<<< orphan*/  EVDNS_UNLOCK (struct evdns_base*) ; 
 int /*<<< orphan*/  EVTHREAD_ALLOC_LOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVTHREAD_LOCKTYPE_RECURSIVE ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int evdns_base_config_windows_nameservers (struct evdns_base*) ; 
 int /*<<< orphan*/  evdns_base_free_and_unlock (struct evdns_base*,int /*<<< orphan*/ ) ; 
 int evdns_base_resolv_conf_parse (struct evdns_base*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  evdns_base_set_max_requests_inflight (struct evdns_base*,int) ; 
 int /*<<< orphan*/  evdns_getaddrinfo ; 
 scalar_t__ evutil_secure_rng_init () ; 
 int /*<<< orphan*/  evutil_set_evdns_getaddrinfo_fn_ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (struct evdns_base*,int /*<<< orphan*/ ,int) ; 
 struct evdns_base* mm_malloc (int) ; 

struct evdns_base *
evdns_base_new(struct event_base *event_base, int flags)
{
	struct evdns_base *base;

	if (evutil_secure_rng_init() < 0) {
		log(EVDNS_LOG_WARN, "Unable to seed random number generator; "
		    "DNS can't run.");
		return NULL;
	}

	/* Give the evutil library a hook into its evdns-enabled
	 * functionality.  We can't just call evdns_getaddrinfo directly or
	 * else libevent-core will depend on libevent-extras. */
	evutil_set_evdns_getaddrinfo_fn_(evdns_getaddrinfo);

	base = mm_malloc(sizeof(struct evdns_base));
	if (base == NULL)
		return (NULL);
	memset(base, 0, sizeof(struct evdns_base));
	base->req_waiting_head = NULL;

	EVTHREAD_ALLOC_LOCK(base->lock, EVTHREAD_LOCKTYPE_RECURSIVE);
	EVDNS_LOCK(base);

	/* Set max requests inflight and allocate req_heads. */
	base->req_heads = NULL;

	evdns_base_set_max_requests_inflight(base, 64);

	base->server_head = NULL;
	base->event_base = event_base;
	base->global_good_nameservers = base->global_requests_inflight =
		base->global_requests_waiting = 0;

	base->global_timeout.tv_sec = 5;
	base->global_timeout.tv_usec = 0;
	base->global_max_reissues = 1;
	base->global_max_retransmits = 3;
	base->global_max_nameserver_timeout = 3;
	base->global_search_state = NULL;
	base->global_randomize_case = 1;
	base->global_getaddrinfo_allow_skew.tv_sec = 3;
	base->global_getaddrinfo_allow_skew.tv_usec = 0;
	base->global_nameserver_probe_initial_timeout.tv_sec = 10;
	base->global_nameserver_probe_initial_timeout.tv_usec = 0;

	TAILQ_INIT(&base->hostsdb);

#define EVDNS_BASE_ALL_FLAGS (0x8001)
	if (flags & ~EVDNS_BASE_ALL_FLAGS) {
		flags = EVDNS_BASE_INITIALIZE_NAMESERVERS;
		log(EVDNS_LOG_WARN,
		    "Unrecognized flag passed to evdns_base_new(). Assuming "
		    "you meant EVDNS_BASE_INITIALIZE_NAMESERVERS.");
	}
#undef EVDNS_BASE_ALL_FLAGS

	if (flags & EVDNS_BASE_INITIALIZE_NAMESERVERS) {
		int r;
#ifdef _WIN32
		r = evdns_base_config_windows_nameservers(base);
#else
		r = evdns_base_resolv_conf_parse(base, DNS_OPTIONS_ALL, "/etc/resolv.conf");
#endif
		if (r == -1) {
			evdns_base_free_and_unlock(base, 0);
			return NULL;
		}
	}
	if (flags & EVDNS_BASE_DISABLE_WHEN_INACTIVE) {
		base->disable_when_inactive = 1;
	}

	EVDNS_UNLOCK(base);
	return base;
}