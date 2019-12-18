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
struct evdns_base {int dummy; } ;
typedef  int /*<<< orphan*/  ev_socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVDNS_LOCK (struct evdns_base*) ; 
 int /*<<< orphan*/  EVDNS_UNLOCK (struct evdns_base*) ; 
 int /*<<< orphan*/  EVUTIL_ASSERT (struct evdns_base*) ; 
 int evdns_nameserver_add_impl_ (struct evdns_base*,struct sockaddr const*,int /*<<< orphan*/ ) ; 

int
evdns_base_nameserver_sockaddr_add(struct evdns_base *base,
    const struct sockaddr *sa, ev_socklen_t len, unsigned flags)
{
	int res;
	EVUTIL_ASSERT(base);
	EVDNS_LOCK(base);
	res = evdns_nameserver_add_impl_(base, sa, len);
	EVDNS_UNLOCK(base);
	return res;
}