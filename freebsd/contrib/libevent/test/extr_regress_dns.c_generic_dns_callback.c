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
struct generic_dns_callback_result {int result; char type; int count; int ttl; size_t addrs_len; int /*<<< orphan*/ * addrs_buf; int /*<<< orphan*/ * addrs; } ;

/* Variables and functions */
 char DNS_IPv4_A ; 
 char DNS_IPv6_AAAA ; 
 char DNS_PTR ; 
 int /*<<< orphan*/  evdns_close_server_port (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_base_loopexit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit_base ; 
 int /*<<< orphan*/ * exit_port ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,size_t) ; 
 scalar_t__ n_replies_left ; 
 int strlen (void*) ; 

__attribute__((used)) static void
generic_dns_callback(int result, char type, int count, int ttl, void *addresses,
    void *arg)
{
	size_t len;
	struct generic_dns_callback_result *res = arg;
	res->result = result;
	res->type = type;
	res->count = count;
	res->ttl = ttl;

	if (type == DNS_IPv4_A)
		len = count * 4;
	else if (type == DNS_IPv6_AAAA)
		len = count * 16;
	else if (type == DNS_PTR)
		len = strlen(addresses)+1;
	else {
		res->addrs_len = len = 0;
		res->addrs = NULL;
	}
	if (len) {
		res->addrs_len = len;
		if (len > 256)
			len = 256;
		memcpy(res->addrs_buf, addresses, len);
		res->addrs = res->addrs_buf;
	}

	--n_replies_left;
	if (n_replies_left == 0) {
		if (exit_port) {
			evdns_close_server_port(exit_port);
			exit_port = NULL;
		} else
			event_base_loopexit(exit_base, NULL);
	}
}