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

/* Variables and functions */
 int /*<<< orphan*/  evdns_base_free (struct evdns_base*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evdns_base_nameserver_ip_add (struct evdns_base*,char*) ; 
 struct evdns_base* evdns_base_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evdns_base_set_option (struct evdns_base*,char*,char*) ; 
 int /*<<< orphan*/  tt_assert (int) ; 

__attribute__((used)) static void
test_set_so_rcvbuf_so_sndbuf(void *arg)
{
	struct basic_test_data *data = arg;
	struct evdns_base *dns_base;

	dns_base = evdns_base_new(data->base, 0);
	tt_assert(dns_base);

	tt_assert(!evdns_base_set_option(dns_base, "so-rcvbuf", "10240"));
	tt_assert(!evdns_base_set_option(dns_base, "so-sndbuf", "10240"));

	/* actually check SO_RCVBUF/SO_SNDBUF not fails */
	tt_assert(!evdns_base_nameserver_ip_add(dns_base, "127.0.0.1"));

end:
	if (dns_base)
		evdns_base_free(dns_base, 0);
}