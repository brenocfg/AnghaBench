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
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct ub_packed_rrset_key {TYPE_1__ entry; } ;
struct regional {int dummy; } ;
struct query_info {size_t qname_len; int /*<<< orphan*/ * local_alias; int /*<<< orphan*/  qclass; int /*<<< orphan*/  qtype; int /*<<< orphan*/ * qname; } ;
struct module_env {int /*<<< orphan*/  cfg; int /*<<< orphan*/ * now; int /*<<< orphan*/  scratch_buffer; int /*<<< orphan*/  rrset_cache; int /*<<< orphan*/  neg_cache; } ;
struct dns_msg {TYPE_2__* rep; } ;
struct TYPE_4__ {int /*<<< orphan*/  an_numrrsets; int /*<<< orphan*/  rrset_count; struct ub_packed_rrset_key** rrsets; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_TYPE_DS ; 
 struct dns_msg* dns_msg_create (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct regional*,int) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 struct ub_packed_rrset_key* packed_rrset_copy_region (struct ub_packed_rrset_key*,struct regional*,int /*<<< orphan*/ ) ; 
 struct ub_packed_rrset_key* rrset_cache_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dns_msg* val_neg_getmsg (int /*<<< orphan*/ ,struct query_info*,struct regional*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct dns_msg* 
val_find_DS(struct module_env* env, uint8_t* nm, size_t nmlen, uint16_t c, 
	struct regional* region, uint8_t* topname)
{
	struct dns_msg* msg;
	struct query_info qinfo;
	struct ub_packed_rrset_key *rrset = rrset_cache_lookup(
		env->rrset_cache, nm, nmlen, LDNS_RR_TYPE_DS, c, 0, 
		*env->now, 0);
	if(rrset) {
		/* DS rrset exists. Return it to the validator immediately*/
		struct ub_packed_rrset_key* copy = packed_rrset_copy_region(
			rrset, region, *env->now);
		lock_rw_unlock(&rrset->entry.lock);
		if(!copy)
			return NULL;
		msg = dns_msg_create(nm, nmlen, LDNS_RR_TYPE_DS, c, region, 1);
		if(!msg)
			return NULL;
		msg->rep->rrsets[0] = copy;
		msg->rep->rrset_count++;
		msg->rep->an_numrrsets++;
		return msg;
	}
	/* lookup in rrset and negative cache for NSEC/NSEC3 */
	qinfo.qname = nm;
	qinfo.qname_len = nmlen;
	qinfo.qtype = LDNS_RR_TYPE_DS;
	qinfo.qclass = c;
	qinfo.local_alias = NULL;
	/* do not add SOA to reply message, it is going to be used internal */
	msg = val_neg_getmsg(env->neg_cache, &qinfo, region, env->rrset_cache,
		env->scratch_buffer, *env->now, 0, topname, env->cfg);
	return msg;
}