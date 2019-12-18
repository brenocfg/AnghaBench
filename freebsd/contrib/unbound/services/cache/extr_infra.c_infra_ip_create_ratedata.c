#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_2__ {struct ip_rate_key* data; struct ip_rate_key* key; int /*<<< orphan*/  hash; int /*<<< orphan*/  lock; } ;
struct ip_rate_key {int* qps; TYPE_1__ entry; int /*<<< orphan*/ * timestamp; int /*<<< orphan*/  addrlen; int /*<<< orphan*/  addr; } ;
struct ip_rate_data {int* qps; TYPE_1__ entry; int /*<<< orphan*/ * timestamp; int /*<<< orphan*/  addrlen; int /*<<< orphan*/  addr; } ;
struct infra_cache {int /*<<< orphan*/  client_ip_rates; } ;
struct comm_reply {int /*<<< orphan*/  addrlen; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  hashvalue_type ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (struct ip_rate_key*) ; 
 int /*<<< orphan*/  hash_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_rw_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slabhash_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,struct ip_rate_key*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void infra_ip_create_ratedata(struct infra_cache* infra,
	struct comm_reply* repinfo, time_t timenow)
{
	hashvalue_type h = hash_addr(&(repinfo->addr),
	repinfo->addrlen, 0);
	struct ip_rate_key* k = (struct ip_rate_key*)calloc(1, sizeof(*k));
	struct ip_rate_data* d = (struct ip_rate_data*)calloc(1, sizeof(*d));
	if(!k || !d) {
		free(k);
		free(d);
		return; /* alloc failure */
	}
	k->addr = repinfo->addr;
	k->addrlen = repinfo->addrlen;
	lock_rw_init(&k->entry.lock);
	k->entry.hash = h;
	k->entry.key = k;
	k->entry.data = d;
	d->qps[0] = 1;
	d->timestamp[0] = timenow;
	slabhash_insert(infra->client_ip_rates, h, &k->entry, d, NULL);
}