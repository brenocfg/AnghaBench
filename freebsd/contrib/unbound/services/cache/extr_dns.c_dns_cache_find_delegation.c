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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_4__ {int /*<<< orphan*/  lock; scalar_t__ data; } ;
struct TYPE_3__ {int /*<<< orphan*/  dname; } ;
struct ub_packed_rrset_key {TYPE_2__ entry; TYPE_1__ rk; } ;
struct regional {int dummy; } ;
struct packed_rrset_data {int count; } ;
struct module_env {int dummy; } ;
struct dns_msg {int dummy; } ;
struct delegpt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_TYPE_NS ; 
 struct delegpt* delegpt_create (struct regional*) ; 
 int /*<<< orphan*/  delegpt_rrset_add_ns (struct delegpt*,struct regional*,struct ub_packed_rrset_key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delegpt_set_name (struct delegpt*,struct regional*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dns_msg_authadd (struct dns_msg*,struct regional*,struct ub_packed_rrset_key*,int /*<<< orphan*/ ) ; 
 struct dns_msg* dns_msg_create (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct regional*,int) ; 
 int /*<<< orphan*/  find_add_addrs (struct module_env*,int /*<<< orphan*/ ,struct regional*,struct delegpt*,int /*<<< orphan*/ ,struct dns_msg**) ; 
 int /*<<< orphan*/  find_add_ds (struct module_env*,struct regional*,struct dns_msg*,struct delegpt*,int /*<<< orphan*/ ) ; 
 struct ub_packed_rrset_key* find_closest_of_type (struct module_env*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*) ; 

struct delegpt* 
dns_cache_find_delegation(struct module_env* env, uint8_t* qname, 
	size_t qnamelen, uint16_t qtype, uint16_t qclass, 
	struct regional* region, struct dns_msg** msg, time_t now)
{
	/* try to find closest NS rrset */
	struct ub_packed_rrset_key* nskey;
	struct packed_rrset_data* nsdata;
	struct delegpt* dp;

	nskey = find_closest_of_type(env, qname, qnamelen, qclass, now,
		LDNS_RR_TYPE_NS, 0);
	if(!nskey) /* hope the caller has hints to prime or something */
		return NULL;
	nsdata = (struct packed_rrset_data*)nskey->entry.data;
	/* got the NS key, create delegation point */
	dp = delegpt_create(region);
	if(!dp || !delegpt_set_name(dp, region, nskey->rk.dname)) {
		lock_rw_unlock(&nskey->entry.lock);
		log_err("find_delegation: out of memory");
		return NULL;
	}
	/* create referral message */
	if(msg) {
		/* allocate the array to as much as we could need:
		 *	NS rrset + DS/NSEC rrset +
		 *	A rrset for every NS RR
		 *	AAAA rrset for every NS RR
		 */
		*msg = dns_msg_create(qname, qnamelen, qtype, qclass, region, 
			2 + nsdata->count*2);
		if(!*msg || !dns_msg_authadd(*msg, region, nskey, now)) {
			lock_rw_unlock(&nskey->entry.lock);
			log_err("find_delegation: out of memory");
			return NULL;
		}
	}
	if(!delegpt_rrset_add_ns(dp, region, nskey, 0))
		log_err("find_delegation: addns out of memory");
	lock_rw_unlock(&nskey->entry.lock); /* first unlock before next lookup*/
	/* find and add DS/NSEC (if any) */
	if(msg)
		find_add_ds(env, region, *msg, dp, now);
	/* find and add A entries */
	if(!find_add_addrs(env, qclass, region, dp, now, msg))
		log_err("find_delegation: addrs out of memory");
	return dp;
}