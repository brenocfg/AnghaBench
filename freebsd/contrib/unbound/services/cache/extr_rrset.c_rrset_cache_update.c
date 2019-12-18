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
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_4__ {scalar_t__ data; int /*<<< orphan*/  hash; } ;
struct TYPE_3__ {int /*<<< orphan*/ * dname; int /*<<< orphan*/  type; } ;
struct ub_packed_rrset_key {scalar_t__ id; TYPE_2__ entry; TYPE_1__ rk; } ;
struct rrset_ref {scalar_t__ id; struct ub_packed_rrset_key* key; } ;
struct rrset_cache {int /*<<< orphan*/  table; } ;
struct packed_rrset_data {int dummy; } ;
struct lruhash_entry {int /*<<< orphan*/  lock; scalar_t__ data; scalar_t__ key; } ;
struct alloc_cache {int dummy; } ;
typedef  int /*<<< orphan*/  hashvalue_type ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_DNAME ; 
 scalar_t__ LDNS_RR_TYPE_NS ; 
 scalar_t__ LDNS_RR_TYPE_NSEC ; 
 scalar_t__ LDNS_RR_TYPE_NSEC3 ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_assert (int) ; 
 int /*<<< orphan*/  need_to_update_rrset (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrset_update_id (struct rrset_ref*,struct alloc_cache*) ; 
 int rrsetdata_equal (struct packed_rrset_data*,struct packed_rrset_data*) ; 
 int /*<<< orphan*/  slabhash_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,scalar_t__,struct alloc_cache*) ; 
 struct lruhash_entry* slabhash_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ub_packed_rrset_key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ub_packed_rrset_parsedelete (struct ub_packed_rrset_key*,struct alloc_cache*) ; 

int 
rrset_cache_update(struct rrset_cache* r, struct rrset_ref* ref,
	struct alloc_cache* alloc, time_t timenow)
{
	struct lruhash_entry* e;
	struct ub_packed_rrset_key* k = ref->key;
	hashvalue_type h = k->entry.hash;
	uint16_t rrset_type = ntohs(k->rk.type);
	int equal = 0;
	log_assert(ref->id != 0 && k->id != 0);
	log_assert(k->rk.dname != NULL);
	/* looks up item with a readlock - no editing! */
	if((e=slabhash_lookup(&r->table, h, k, 0)) != 0) {
		/* return id and key as they will be used in the cache
		 * since the lruhash_insert, if item already exists, deallocs
		 * the passed key in favor of the already stored key.
		 * because of the small gap (see below) this key ptr and id
		 * may prove later to be already deleted, which is no problem
		 * as it only makes a cache miss. 
		 */
		ref->key = (struct ub_packed_rrset_key*)e->key;
		ref->id = ref->key->id;
		equal = rrsetdata_equal((struct packed_rrset_data*)k->entry.
			data, (struct packed_rrset_data*)e->data);
		if(!need_to_update_rrset(k->entry.data, e->data, timenow,
			equal, (rrset_type==LDNS_RR_TYPE_NS))) {
			/* cache is superior, return that value */
			lock_rw_unlock(&e->lock);
			ub_packed_rrset_parsedelete(k, alloc);
			if(equal) return 2;
			return 1;
		}
		lock_rw_unlock(&e->lock);
		/* Go on and insert the passed item.
		 * small gap here, where entry is not locked.
		 * possibly entry is updated with something else.
		 * we then overwrite that with our data.
		 * this is just too bad, its cache anyway. */
		/* use insert to update entry to manage lruhash
		 * cache size values nicely. */
	}
	log_assert(ref->key->id != 0);
	slabhash_insert(&r->table, h, &k->entry, k->entry.data, alloc);
	if(e) {
		/* For NSEC, NSEC3, DNAME, when rdata is updated, update 
		 * the ID number so that proofs in message cache are 
		 * invalidated */
		if((rrset_type == LDNS_RR_TYPE_NSEC 
			|| rrset_type == LDNS_RR_TYPE_NSEC3
			|| rrset_type == LDNS_RR_TYPE_DNAME) && !equal) {
			rrset_update_id(ref, alloc);
		}
		return 1;
	}
	return 0;
}