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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_2__ {struct rate_key* data; struct rate_key* key; int /*<<< orphan*/  hash; int /*<<< orphan*/  lock; } ;
struct rate_key {size_t namelen; int* qps; TYPE_1__ entry; int /*<<< orphan*/ * timestamp; int /*<<< orphan*/  name; } ;
struct rate_data {size_t namelen; int* qps; TYPE_1__ entry; int /*<<< orphan*/ * timestamp; int /*<<< orphan*/  name; } ;
struct infra_cache {int /*<<< orphan*/  domain_rates; } ;
typedef  int /*<<< orphan*/  hashvalue_type ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  dname_query_hash (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (struct rate_key*) ; 
 int /*<<< orphan*/  lock_rw_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memdup (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  slabhash_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,struct rate_key*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void infra_create_ratedata(struct infra_cache* infra,
	uint8_t* name, size_t namelen, time_t timenow)
{
	hashvalue_type h = dname_query_hash(name, 0xab);
	struct rate_key* k = (struct rate_key*)calloc(1, sizeof(*k));
	struct rate_data* d = (struct rate_data*)calloc(1, sizeof(*d));
	if(!k || !d) {
		free(k);
		free(d);
		return; /* alloc failure */
	}
	k->namelen = namelen;
	k->name = memdup(name, namelen);
	if(!k->name) {
		free(k);
		free(d);
		return; /* alloc failure */
	}
	lock_rw_init(&k->entry.lock);
	k->entry.hash = h;
	k->entry.key = k;
	k->entry.data = d;
	d->qps[0] = 1;
	d->timestamp[0] = timenow;
	slabhash_insert(infra->domain_rates, h, &k->entry, d, NULL);
}