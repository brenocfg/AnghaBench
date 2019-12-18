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
struct evdns_base {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVDNS_LOCK (struct evdns_base*) ; 
 int /*<<< orphan*/  EVDNS_UNLOCK (struct evdns_base*) ; 
 struct evdns_base* current_base ; 
 int evdns_base_load_hosts_impl (struct evdns_base*,char const*) ; 

int
evdns_base_load_hosts(struct evdns_base *base, const char *hosts_fname)
{
	int res;
	if (!base)
		base = current_base;
	EVDNS_LOCK(base);
	res = evdns_base_load_hosts_impl(base, hosts_fname);
	EVDNS_UNLOCK(base);
	return res;
}