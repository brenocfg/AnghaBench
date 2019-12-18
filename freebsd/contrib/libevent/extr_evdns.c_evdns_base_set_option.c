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
 int /*<<< orphan*/  DNS_OPTIONS_ALL ; 
 int /*<<< orphan*/  EVDNS_LOCK (struct evdns_base*) ; 
 int /*<<< orphan*/  EVDNS_UNLOCK (struct evdns_base*) ; 
 int evdns_base_set_option_impl (struct evdns_base*,char const*,char const*,int /*<<< orphan*/ ) ; 

int
evdns_base_set_option(struct evdns_base *base,
    const char *option, const char *val)
{
	int res;
	EVDNS_LOCK(base);
	res = evdns_base_set_option_impl(base, option, val, DNS_OPTIONS_ALL);
	EVDNS_UNLOCK(base);
	return res;
}