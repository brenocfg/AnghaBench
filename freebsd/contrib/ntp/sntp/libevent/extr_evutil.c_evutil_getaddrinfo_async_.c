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
struct evutil_addrinfo {int dummy; } ;
struct evdns_base {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  evdns_getaddrinfo_impl (struct evdns_base*,char const*,char const*,struct evutil_addrinfo const*,void (*) (int,struct evutil_addrinfo*,void*),void*) ; 
 int evutil_getaddrinfo (char const*,char const*,struct evutil_addrinfo const*,struct evutil_addrinfo**) ; 

int
evutil_getaddrinfo_async_(struct evdns_base *dns_base,
    const char *nodename, const char *servname,
    const struct evutil_addrinfo *hints_in,
    void (*cb)(int, struct evutil_addrinfo *, void *), void *arg)
{
	if (dns_base && evdns_getaddrinfo_impl) {
		evdns_getaddrinfo_impl(
			dns_base, nodename, servname, hints_in, cb, arg);
	} else {
		struct evutil_addrinfo *ai=NULL;
		int err;
		err = evutil_getaddrinfo(nodename, servname, hints_in, &ai);
		cb(err, ai, arg);
	}
	return 0;
}