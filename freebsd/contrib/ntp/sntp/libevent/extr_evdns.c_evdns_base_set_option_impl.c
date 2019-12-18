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
typedef  int /*<<< orphan*/  tv ;
struct timeval {int tv_sec; } ;
struct sockaddr {int dummy; } ;
struct evdns_base {int global_max_nameserver_timeout; int global_max_retransmits; int global_randomize_case; int global_outgoing_addrlen; int /*<<< orphan*/  global_nameserver_probe_initial_timeout; int /*<<< orphan*/  global_outgoing_address; int /*<<< orphan*/  global_getaddrinfo_allow_skew; int /*<<< orphan*/  global_timeout; TYPE_1__* global_search_state; } ;
struct TYPE_2__ {int ndots; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_LOCKED (struct evdns_base*) ; 
 int DNS_OPTION_MISC ; 
 int DNS_OPTION_NAMESERVERS ; 
 int DNS_OPTION_SEARCH ; 
 int /*<<< orphan*/  EVDNS_LOG_DEBUG ; 
 int /*<<< orphan*/  evdns_base_set_max_requests_inflight (struct evdns_base*,int const) ; 
 int evdns_strtotimeval (char const*,struct timeval*) ; 
 scalar_t__ evutil_parse_sockaddr_port (char const*,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct timeval*,int) ; 
 TYPE_1__* search_state_new () ; 
 scalar_t__ str_matches_option (char const*,char*) ; 
 void* strtoint (char const*) ; 
 int strtoint_clipped (char const*,int,int) ; 

__attribute__((used)) static int
evdns_base_set_option_impl(struct evdns_base *base,
    const char *option, const char *val, int flags)
{
	ASSERT_LOCKED(base);
	if (str_matches_option(option, "ndots:")) {
		const int ndots = strtoint(val);
		if (ndots == -1) return -1;
		if (!(flags & DNS_OPTION_SEARCH)) return 0;
		log(EVDNS_LOG_DEBUG, "Setting ndots to %d", ndots);
		if (!base->global_search_state) base->global_search_state = search_state_new();
		if (!base->global_search_state) return -1;
		base->global_search_state->ndots = ndots;
	} else if (str_matches_option(option, "timeout:")) {
		struct timeval tv;
		if (evdns_strtotimeval(val, &tv) == -1) return -1;
		if (!(flags & DNS_OPTION_MISC)) return 0;
		log(EVDNS_LOG_DEBUG, "Setting timeout to %s", val);
		memcpy(&base->global_timeout, &tv, sizeof(struct timeval));
	} else if (str_matches_option(option, "getaddrinfo-allow-skew:")) {
		struct timeval tv;
		if (evdns_strtotimeval(val, &tv) == -1) return -1;
		if (!(flags & DNS_OPTION_MISC)) return 0;
		log(EVDNS_LOG_DEBUG, "Setting getaddrinfo-allow-skew to %s",
		    val);
		memcpy(&base->global_getaddrinfo_allow_skew, &tv,
		    sizeof(struct timeval));
	} else if (str_matches_option(option, "max-timeouts:")) {
		const int maxtimeout = strtoint_clipped(val, 1, 255);
		if (maxtimeout == -1) return -1;
		if (!(flags & DNS_OPTION_MISC)) return 0;
		log(EVDNS_LOG_DEBUG, "Setting maximum allowed timeouts to %d",
			maxtimeout);
		base->global_max_nameserver_timeout = maxtimeout;
	} else if (str_matches_option(option, "max-inflight:")) {
		const int maxinflight = strtoint_clipped(val, 1, 65000);
		if (maxinflight == -1) return -1;
		if (!(flags & DNS_OPTION_MISC)) return 0;
		log(EVDNS_LOG_DEBUG, "Setting maximum inflight requests to %d",
			maxinflight);
		evdns_base_set_max_requests_inflight(base, maxinflight);
	} else if (str_matches_option(option, "attempts:")) {
		int retries = strtoint(val);
		if (retries == -1) return -1;
		if (retries > 255) retries = 255;
		if (!(flags & DNS_OPTION_MISC)) return 0;
		log(EVDNS_LOG_DEBUG, "Setting retries to %d", retries);
		base->global_max_retransmits = retries;
	} else if (str_matches_option(option, "randomize-case:")) {
		int randcase = strtoint(val);
		if (!(flags & DNS_OPTION_MISC)) return 0;
		base->global_randomize_case = randcase;
	} else if (str_matches_option(option, "bind-to:")) {
		/* XXX This only applies to successive nameservers, not
		 * to already-configured ones.	We might want to fix that. */
		int len = sizeof(base->global_outgoing_address);
		if (!(flags & DNS_OPTION_NAMESERVERS)) return 0;
		if (evutil_parse_sockaddr_port(val,
			(struct sockaddr*)&base->global_outgoing_address, &len))
			return -1;
		base->global_outgoing_addrlen = len;
	} else if (str_matches_option(option, "initial-probe-timeout:")) {
		struct timeval tv;
		if (evdns_strtotimeval(val, &tv) == -1) return -1;
		if (tv.tv_sec > 3600)
			tv.tv_sec = 3600;
		if (!(flags & DNS_OPTION_MISC)) return 0;
		log(EVDNS_LOG_DEBUG, "Setting initial probe timeout to %s",
		    val);
		memcpy(&base->global_nameserver_probe_initial_timeout, &tv,
		    sizeof(tv));
	}
	return 0;
}