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
struct delegpt {int has_parent_side_NS; int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_TYPE_NS ; 
 int /*<<< orphan*/  PACKED_RRSET_PARENT_SIDE ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  delegpt_rrset_add_ns (struct delegpt*,struct regional*,struct ub_packed_rrset_key*,int) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_rrset_key (int /*<<< orphan*/ ,char*,struct ub_packed_rrset_key*) ; 
 struct ub_packed_rrset_key* rrset_cache_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int 
iter_lookup_parent_NS_from_cache(struct module_env* env, struct delegpt* dp,
	struct regional* region, struct query_info* qinfo)
{
	struct ub_packed_rrset_key* akey;
	akey = rrset_cache_lookup(env->rrset_cache, dp->name, 
		dp->namelen, LDNS_RR_TYPE_NS, qinfo->qclass, 
		PACKED_RRSET_PARENT_SIDE, *env->now, 0);
	if(akey) {
		log_rrset_key(VERB_ALGO, "found parent-side NS in cache", akey);
		dp->has_parent_side_NS = 1;
		/* and mark the new names as lame */
		if(!delegpt_rrset_add_ns(dp, region, akey, 1)) {
			lock_rw_unlock(&akey->entry.lock);
			return 0;
		}
		lock_rw_unlock(&akey->entry.lock);
	}
	return 1;
}