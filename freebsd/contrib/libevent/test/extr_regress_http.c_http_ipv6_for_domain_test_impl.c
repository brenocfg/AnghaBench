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
struct basic_test_data {int /*<<< orphan*/  base; } ;
typedef  int /*<<< orphan*/  ev_uint16_t ;
typedef  int /*<<< orphan*/  address ;

/* Variables and functions */
 int /*<<< orphan*/  evdns_base_free (struct evdns_base*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evdns_base_nameserver_ip_add (struct evdns_base*,char*) ; 
 struct evdns_base* evdns_base_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evutil_snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  http_connection_test_ (void*,int /*<<< orphan*/ ,char*,struct evdns_base*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv6_search_table ; 
 int /*<<< orphan*/  regress_clean_dnsserver () ; 
 struct evdns_base* regress_dnsserver (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tt_assert (struct evdns_base*) ; 

__attribute__((used)) static void
http_ipv6_for_domain_test_impl(void *arg, int family)
{
	struct basic_test_data *data = arg;
	struct evdns_base *dns_base = NULL;
	ev_uint16_t portnum = 0;
	char address[64];

	tt_assert(regress_dnsserver(data->base, &portnum, ipv6_search_table));

	dns_base = evdns_base_new(data->base, 0/* init name servers */);
	tt_assert(dns_base);

	/* Add ourself as the only nameserver, and make sure we really are
	 * the only nameserver. */
	evutil_snprintf(address, sizeof(address), "127.0.0.1:%d", portnum);
	evdns_base_nameserver_ip_add(dns_base, address);

	http_connection_test_(arg, 0 /* not persistent */, "localhost", dns_base,
		1 /* ipv6 */, family, 0);

 end:
	if (dns_base)
		evdns_base_free(dns_base, 0);
	regress_clean_dnsserver();
}