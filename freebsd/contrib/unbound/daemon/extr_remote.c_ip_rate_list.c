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
struct lruhash_entry {scalar_t__ data; scalar_t__ key; } ;
struct ip_ratelimit_list_arg {scalar_t__ all; int /*<<< orphan*/  ssl; int /*<<< orphan*/  now; } ;
struct ip_rate_key {int /*<<< orphan*/  addrlen; int /*<<< orphan*/  addr; } ;
struct ip_rate_data {int dummy; } ;
typedef  int /*<<< orphan*/  ip ;

/* Variables and functions */
 int /*<<< orphan*/  addr_to_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int infra_ip_ratelimit ; 
 int infra_rate_max (struct ip_rate_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl_printf (int /*<<< orphan*/ ,char*,char*,int,int) ; 

__attribute__((used)) static void
ip_rate_list(struct lruhash_entry* e, void* arg)
{
	char ip[128];
	struct ip_ratelimit_list_arg* a = (struct ip_ratelimit_list_arg*)arg;
	struct ip_rate_key* k = (struct ip_rate_key*)e->key;
	struct ip_rate_data* d = (struct ip_rate_data*)e->data;
	int lim = infra_ip_ratelimit;
	int max = infra_rate_max(d, a->now);
	if(a->all == 0) {
		if(max < lim)
			return;
	}
	addr_to_str(&k->addr, k->addrlen, ip, sizeof(ip));
	ssl_printf(a->ssl, "%s %d limit %d\n", ip, max, lim);
}