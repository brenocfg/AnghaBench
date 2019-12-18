#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ sa_family; } ;
struct TYPE_3__ {TYPE_2__ sa; } ;
struct hosts_entry {int /*<<< orphan*/  addrlen; TYPE_1__ addr; } ;
struct evutil_addrinfo {int ai_family; int /*<<< orphan*/  ai_addr; } ;
struct evdns_base {int dummy; } ;
typedef  int /*<<< orphan*/  ev_uint16_t ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  EVDNS_LOCK (struct evdns_base*) ; 
 int /*<<< orphan*/  EVDNS_UNLOCK (struct evdns_base*) ; 
 int PF_INET ; 
 int PF_INET6 ; 
 struct evutil_addrinfo* evutil_addrinfo_append_ (struct evutil_addrinfo*,struct evutil_addrinfo*) ; 
 int /*<<< orphan*/  evutil_freeaddrinfo (struct evutil_addrinfo*) ; 
 struct evutil_addrinfo* evutil_new_addrinfo_ (TYPE_2__*,int /*<<< orphan*/ ,struct evutil_addrinfo*) ; 
 struct hosts_entry* find_hosts_entry (struct evdns_base*,char const*,struct hosts_entry*) ; 
 int /*<<< orphan*/  sockaddr_setport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
evdns_getaddrinfo_fromhosts(struct evdns_base *base,
    const char *nodename, struct evutil_addrinfo *hints, ev_uint16_t port,
    struct evutil_addrinfo **res)
{
	int n_found = 0;
	struct hosts_entry *e;
	struct evutil_addrinfo *ai=NULL;
	int f = hints->ai_family;

	EVDNS_LOCK(base);
	for (e = find_hosts_entry(base, nodename, NULL); e;
	    e = find_hosts_entry(base, nodename, e)) {
		struct evutil_addrinfo *ai_new;
		++n_found;
		if ((e->addr.sa.sa_family == AF_INET && f == PF_INET6) ||
		    (e->addr.sa.sa_family == AF_INET6 && f == PF_INET))
			continue;
		ai_new = evutil_new_addrinfo_(&e->addr.sa, e->addrlen, hints);
		if (!ai_new) {
			n_found = 0;
			goto out;
		}
		sockaddr_setport(ai_new->ai_addr, port);
		ai = evutil_addrinfo_append_(ai, ai_new);
	}
	EVDNS_UNLOCK(base);
out:
	if (n_found) {
		/* Note that we return an empty answer if we found entries for
		 * this hostname but none were of the right address type. */
		*res = ai;
		return 0;
	} else {
		if (ai)
			evutil_freeaddrinfo(ai);
		return -1;
	}
}