#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct ub_packed_rrset_key {TYPE_2__ entry; int /*<<< orphan*/  id; TYPE_1__ rk; } ;
struct reply_info {size_t rrset_count; TYPE_3__* ref; struct ub_packed_rrset_key** rrsets; } ;
struct regional {int dummy; } ;
struct module_env {int /*<<< orphan*/  alloc; int /*<<< orphan*/  rrset_cache; } ;
struct TYPE_6__ {struct ub_packed_rrset_key* key; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_NS ; 
 int /*<<< orphan*/  lock_rw_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 struct ub_packed_rrset_key* packed_rrset_copy_region (struct ub_packed_rrset_key*,struct regional*,scalar_t__) ; 
 int rrset_cache_update (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
store_rrsets(struct module_env* env, struct reply_info* rep, time_t now,
	time_t leeway, int pside, struct reply_info* qrep,
	struct regional* region)
{
        size_t i;
        /* see if rrset already exists in cache, if not insert it. */
        for(i=0; i<rep->rrset_count; i++) {
                rep->ref[i].key = rep->rrsets[i];
                rep->ref[i].id = rep->rrsets[i]->id;
		/* update ref if it was in the cache */ 
		switch(rrset_cache_update(env->rrset_cache, &rep->ref[i],
                        env->alloc, now + ((ntohs(rep->ref[i].key->rk.type)==
			LDNS_RR_TYPE_NS && !pside)?0:leeway))) {
		case 0: /* ref unchanged, item inserted */
			break;
		case 2: /* ref updated, cache is superior */
			if(region) {
				struct ub_packed_rrset_key* ck;
				lock_rw_rdlock(&rep->ref[i].key->entry.lock);
				/* if deleted rrset, do not copy it */
				if(rep->ref[i].key->id == 0)
					ck = NULL;
				else 	ck = packed_rrset_copy_region(
					rep->ref[i].key, region, now);
				lock_rw_unlock(&rep->ref[i].key->entry.lock);
				if(ck) {
					/* use cached copy if memory allows */
					qrep->rrsets[i] = ck;
				}
			}
			/* no break: also copy key item */
			/* the line below is matched by gcc regex and silences
			 * the fallthrough warning */
			/* fallthrough */
		case 1: /* ref updated, item inserted */
                        rep->rrsets[i] = rep->ref[i].key;
		}
        }
}