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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct ub_packed_rrset_key {TYPE_1__ entry; } ;
struct regional {int dummy; } ;
struct query_info {int /*<<< orphan*/  qclass; } ;
struct module_env {int /*<<< orphan*/ * now; int /*<<< orphan*/  rrset_cache; } ;
struct delegpt_ns {int done_pside4; int done_pside6; int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; struct delegpt_ns* next; } ;
struct delegpt {struct delegpt_ns* nslist; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_TYPE_A ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_AAAA ; 
 int /*<<< orphan*/  PACKED_RRSET_PARENT_SIDE ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  delegpt_add_rrset_A (struct delegpt*,struct regional*,struct ub_packed_rrset_key*,int) ; 
 int /*<<< orphan*/  delegpt_add_rrset_AAAA (struct delegpt*,struct regional*,struct ub_packed_rrset_key*,int) ; 
 size_t delegpt_count_targets (struct delegpt*) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  log_rrset_key (int /*<<< orphan*/ ,char*,struct ub_packed_rrset_key*) ; 
 struct ub_packed_rrset_key* rrset_cache_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int iter_lookup_parent_glue_from_cache(struct module_env* env,
        struct delegpt* dp, struct regional* region, struct query_info* qinfo)
{
	struct ub_packed_rrset_key* akey;
	struct delegpt_ns* ns;
	size_t num = delegpt_count_targets(dp);
	for(ns = dp->nslist; ns; ns = ns->next) {
		/* get cached parentside A */
		akey = rrset_cache_lookup(env->rrset_cache, ns->name, 
			ns->namelen, LDNS_RR_TYPE_A, qinfo->qclass, 
			PACKED_RRSET_PARENT_SIDE, *env->now, 0);
		if(akey) {
			log_rrset_key(VERB_ALGO, "found parent-side", akey);
			ns->done_pside4 = 1;
			/* a negative-cache-element has no addresses it adds */
			if(!delegpt_add_rrset_A(dp, region, akey, 1))
				log_err("malloc failure in lookup_parent_glue");
			lock_rw_unlock(&akey->entry.lock);
		}
		/* get cached parentside AAAA */
		akey = rrset_cache_lookup(env->rrset_cache, ns->name, 
			ns->namelen, LDNS_RR_TYPE_AAAA, qinfo->qclass, 
			PACKED_RRSET_PARENT_SIDE, *env->now, 0);
		if(akey) {
			log_rrset_key(VERB_ALGO, "found parent-side", akey);
			ns->done_pside6 = 1;
			/* a negative-cache-element has no addresses it adds */
			if(!delegpt_add_rrset_AAAA(dp, region, akey, 1))
				log_err("malloc failure in lookup_parent_glue");
			lock_rw_unlock(&akey->entry.lock);
		}
	}
	/* see if new (but lame) addresses have become available */
	return delegpt_count_targets(dp) != num;
}