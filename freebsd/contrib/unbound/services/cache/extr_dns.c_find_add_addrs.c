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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct ub_packed_rrset_key {TYPE_1__ entry; } ;
struct regional {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct msgreply_entry {TYPE_2__ entry; } ;
struct module_env {int /*<<< orphan*/  rrset_cache; } ;
struct dns_msg {int dummy; } ;
struct delegpt_ns {int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; struct delegpt_ns* next; } ;
struct delegpt {struct delegpt_ns* nslist; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_TYPE_A ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_AAAA ; 
 int /*<<< orphan*/  addr_to_additional (struct ub_packed_rrset_key*,struct regional*,struct dns_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delegpt_add_neg_msg (struct delegpt*,struct msgreply_entry*) ; 
 int /*<<< orphan*/  delegpt_add_rrset_A (struct delegpt*,struct regional*,struct ub_packed_rrset_key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delegpt_add_rrset_AAAA (struct delegpt*,struct regional*,struct ub_packed_rrset_key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 struct msgreply_entry* msg_cache_lookup (struct module_env*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ub_packed_rrset_key* rrset_cache_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
find_add_addrs(struct module_env* env, uint16_t qclass, 
	struct regional* region, struct delegpt* dp, time_t now, 
	struct dns_msg** msg)
{
	struct delegpt_ns* ns;
	struct msgreply_entry* neg;
	struct ub_packed_rrset_key* akey;
	for(ns = dp->nslist; ns; ns = ns->next) {
		akey = rrset_cache_lookup(env->rrset_cache, ns->name, 
			ns->namelen, LDNS_RR_TYPE_A, qclass, 0, now, 0);
		if(akey) {
			if(!delegpt_add_rrset_A(dp, region, akey, 0)) {
				lock_rw_unlock(&akey->entry.lock);
				return 0;
			}
			if(msg)
				addr_to_additional(akey, region, *msg, now);
			lock_rw_unlock(&akey->entry.lock);
		} else {
			/* BIT_CD on false because delegpt lookup does
			 * not use dns64 translation */
			neg = msg_cache_lookup(env, ns->name, ns->namelen,
				LDNS_RR_TYPE_A, qclass, 0, now, 0);
			if(neg) {
				delegpt_add_neg_msg(dp, neg);
				lock_rw_unlock(&neg->entry.lock);
			}
		}
		akey = rrset_cache_lookup(env->rrset_cache, ns->name, 
			ns->namelen, LDNS_RR_TYPE_AAAA, qclass, 0, now, 0);
		if(akey) {
			if(!delegpt_add_rrset_AAAA(dp, region, akey, 0)) {
				lock_rw_unlock(&akey->entry.lock);
				return 0;
			}
			if(msg)
				addr_to_additional(akey, region, *msg, now);
			lock_rw_unlock(&akey->entry.lock);
		} else {
			/* BIT_CD on false because delegpt lookup does
			 * not use dns64 translation */
			neg = msg_cache_lookup(env, ns->name, ns->namelen,
				LDNS_RR_TYPE_AAAA, qclass, 0, now, 0);
			if(neg) {
				delegpt_add_neg_msg(dp, neg);
				lock_rw_unlock(&neg->entry.lock);
			}
		}
	}
	return 1;
}