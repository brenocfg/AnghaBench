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
struct val_env {int dummy; } ;
struct ub_packed_rrset_key {int dummy; } ;
struct trust_anchor {int /*<<< orphan*/  dclass; int /*<<< orphan*/  name; int /*<<< orphan*/  namelen; int /*<<< orphan*/  dnskey_rrset; int /*<<< orphan*/  ds_rrset; } ;
struct module_qstate {TYPE_2__* env; int /*<<< orphan*/  region; } ;
struct key_entry_key {int dummy; } ;
typedef  enum sec_status { ____Placeholder_sec_status } sec_status ;
struct TYPE_4__ {int /*<<< orphan*/ * now; TYPE_1__* cfg; scalar_t__* modinfo; } ;
struct TYPE_3__ {int harden_algo_downgrade; scalar_t__ harden_dnssec_stripped; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOGUS_KEY_TTL ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_DNSKEY ; 
 int /*<<< orphan*/  NULL_KEY_TTL ; 
 int /*<<< orphan*/  VERB_DETAIL ; 
 int /*<<< orphan*/  VERB_OPS ; 
 int /*<<< orphan*/  errinf (struct module_qstate*,char*) ; 
 struct key_entry_key* key_entry_create_bad (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct key_entry_key* key_entry_create_null (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ key_entry_isgood (struct key_entry_key*) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  log_nametypeclass (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sec_status_bogus ; 
 int sec_status_secure ; 
 int /*<<< orphan*/  sec_status_to_string (int) ; 
 int sec_status_unchecked ; 
 struct key_entry_key* val_verify_new_DNSKEYs_with_ta (int /*<<< orphan*/ ,TYPE_2__*,struct val_env*,struct ub_packed_rrset_key*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char**,struct module_qstate*) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct key_entry_key*
primeResponseToKE(struct ub_packed_rrset_key* dnskey_rrset, 
	struct trust_anchor* ta, struct module_qstate* qstate, int id)
{
	struct val_env* ve = (struct val_env*)qstate->env->modinfo[id];
	struct key_entry_key* kkey = NULL;
	enum sec_status sec = sec_status_unchecked;
	char* reason = NULL;
	int downprot = qstate->env->cfg->harden_algo_downgrade;

	if(!dnskey_rrset) {
		log_nametypeclass(VERB_OPS, "failed to prime trust anchor -- "
			"could not fetch DNSKEY rrset", 
			ta->name, LDNS_RR_TYPE_DNSKEY, ta->dclass);
		if(qstate->env->cfg->harden_dnssec_stripped) {
			errinf(qstate, "no DNSKEY rrset");
			kkey = key_entry_create_bad(qstate->region, ta->name,
				ta->namelen, ta->dclass, BOGUS_KEY_TTL,
				*qstate->env->now);
		} else 	kkey = key_entry_create_null(qstate->region, ta->name,
				ta->namelen, ta->dclass, NULL_KEY_TTL,
				*qstate->env->now);
		if(!kkey) {
			log_err("out of memory: allocate fail prime key");
			return NULL;
		}
		return kkey;
	}
	/* attempt to verify with trust anchor DS and DNSKEY */
	kkey = val_verify_new_DNSKEYs_with_ta(qstate->region, qstate->env, ve, 
		dnskey_rrset, ta->ds_rrset, ta->dnskey_rrset, downprot,
		&reason, qstate);
	if(!kkey) {
		log_err("out of memory: verifying prime TA");
		return NULL;
	}
	if(key_entry_isgood(kkey))
		sec = sec_status_secure;
	else
		sec = sec_status_bogus;
	verbose(VERB_DETAIL, "validate keys with anchor(DS): %s", 
		sec_status_to_string(sec));

	if(sec != sec_status_secure) {
		log_nametypeclass(VERB_OPS, "failed to prime trust anchor -- "
			"DNSKEY rrset is not secure", 
			ta->name, LDNS_RR_TYPE_DNSKEY, ta->dclass);
		/* NOTE: in this case, we should probably reject the trust 
		 * anchor for longer, perhaps forever. */
		if(qstate->env->cfg->harden_dnssec_stripped) {
			errinf(qstate, reason);
			kkey = key_entry_create_bad(qstate->region, ta->name,
				ta->namelen, ta->dclass, BOGUS_KEY_TTL,
				*qstate->env->now);
		} else 	kkey = key_entry_create_null(qstate->region, ta->name,
				ta->namelen, ta->dclass, NULL_KEY_TTL,
				*qstate->env->now);
		if(!kkey) {
			log_err("out of memory: allocate null prime key");
			return NULL;
		}
		return kkey;
	}

	log_nametypeclass(VERB_DETAIL, "Successfully primed trust anchor", 
		ta->name, LDNS_RR_TYPE_DNSKEY, ta->dclass);
	return kkey;
}