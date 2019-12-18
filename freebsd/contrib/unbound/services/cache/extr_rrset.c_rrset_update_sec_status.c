#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int /*<<< orphan*/  hash; scalar_t__ data; } ;
struct ub_packed_rrset_key {TYPE_2__ rk; TYPE_1__ entry; } ;
struct rrset_cache {int /*<<< orphan*/  table; } ;
struct packed_rrset_data {scalar_t__ security; scalar_t__ trust; scalar_t__ ttl; size_t count; size_t rrsig_count; scalar_t__* rr_ttl; } ;
struct lruhash_entry {int /*<<< orphan*/  lock; scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_NS ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrset_key_hash (TYPE_2__*) ; 
 int /*<<< orphan*/  rrsetdata_equal (struct packed_rrset_data*,struct packed_rrset_data*) ; 
 scalar_t__ sec_status_bogus ; 
 struct lruhash_entry* slabhash_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ub_packed_rrset_key*,int) ; 

void 
rrset_update_sec_status(struct rrset_cache* r, 
	struct ub_packed_rrset_key* rrset, time_t now)
{
	struct packed_rrset_data* updata = 
		(struct packed_rrset_data*)rrset->entry.data;
	struct lruhash_entry* e;
	struct packed_rrset_data* cachedata;

	/* hash it again to make sure it has a hash */
	rrset->entry.hash = rrset_key_hash(&rrset->rk);

	e = slabhash_lookup(&r->table, rrset->entry.hash, rrset, 1);
	if(!e)
		return; /* not in the cache anymore */
	cachedata = (struct packed_rrset_data*)e->data;
	if(!rrsetdata_equal(updata, cachedata)) {
		lock_rw_unlock(&e->lock);
		return; /* rrset has changed in the meantime */
	}
	/* update the cached rrset */
	if(updata->security > cachedata->security) {
		size_t i;
		if(updata->trust > cachedata->trust)
			cachedata->trust = updata->trust;
		cachedata->security = updata->security;
		/* for NS records only shorter TTLs, other types: update it */
		if(ntohs(rrset->rk.type) != LDNS_RR_TYPE_NS ||
			updata->ttl+now < cachedata->ttl ||
			cachedata->ttl < now ||
			updata->security == sec_status_bogus) {
			cachedata->ttl = updata->ttl + now;
			for(i=0; i<cachedata->count+cachedata->rrsig_count; i++)
				cachedata->rr_ttl[i] = updata->rr_ttl[i]+now;
		}
	}
	lock_rw_unlock(&e->lock);
}