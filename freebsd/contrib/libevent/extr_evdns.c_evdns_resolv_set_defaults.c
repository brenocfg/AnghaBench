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
 int /*<<< orphan*/  ASSERT_LOCKED (struct evdns_base*) ; 
 int DNS_OPTION_NAMESERVERS ; 
 int DNS_OPTION_SEARCH ; 
 int /*<<< orphan*/  evdns_base_nameserver_ip_add (struct evdns_base*,char*) ; 
 int /*<<< orphan*/  search_set_from_hostname (struct evdns_base*) ; 

__attribute__((used)) static void
evdns_resolv_set_defaults(struct evdns_base *base, int flags) {
	/* if the file isn't found then we assume a local resolver */
	ASSERT_LOCKED(base);
	if (flags & DNS_OPTION_SEARCH) search_set_from_hostname(base);
	if (flags & DNS_OPTION_NAMESERVERS) evdns_base_nameserver_ip_add(base,"127.0.0.1");
}