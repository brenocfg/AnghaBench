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
struct val_env {int dummy; } ;
struct ub_packed_rrset_key {int dummy; } ;
struct trust_anchor {int /*<<< orphan*/  dnskey_rrset; int /*<<< orphan*/  ds_rrset; TYPE_1__* autr; int /*<<< orphan*/  dclass; int /*<<< orphan*/  name; int /*<<< orphan*/  lock; } ;
struct module_qstate {int dummy; } ;
struct module_env {scalar_t__* now; } ;
struct TYPE_2__ {scalar_t__ query_failed; scalar_t__ last_success; scalar_t__ last_queried; scalar_t__ revoked; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_TYPE_DNSKEY ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  autr_assemble (struct trust_anchor*) ; 
 int /*<<< orphan*/  autr_cleanup_keys (struct trust_anchor*) ; 
 int /*<<< orphan*/  autr_holddown_exceed (struct module_env*,struct trust_anchor*,int*) ; 
 int /*<<< orphan*/  autr_tp_remove (struct module_env*,struct trust_anchor*,struct ub_packed_rrset_key*) ; 
 int /*<<< orphan*/  autr_write_file (struct module_env*,struct trust_anchor*) ; 
 int /*<<< orphan*/  check_contains_revoked (struct module_env*,struct val_env*,struct trust_anchor*,struct ub_packed_rrset_key*,int*,struct module_qstate*) ; 
 int /*<<< orphan*/  do_statetable (struct module_env*,struct trust_anchor*,int*) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_assert (int) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  log_nametypeclass (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_next_probe (struct module_env*,struct trust_anchor*,struct ub_packed_rrset_key*) ; 
 int /*<<< orphan*/  update_events (struct module_env*,struct val_env*,struct trust_anchor*,struct ub_packed_rrset_key*,int*) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  verify_dnskey (struct module_env*,struct val_env*,struct trust_anchor*,struct ub_packed_rrset_key*,struct module_qstate*) ; 

int autr_process_prime(struct module_env* env, struct val_env* ve,
	struct trust_anchor* tp, struct ub_packed_rrset_key* dnskey_rrset,
	struct module_qstate* qstate)
{
	int changed = 0;
	log_assert(tp && tp->autr);
	/* autotrust update trust anchors */
	/* the tp is locked, and stays locked unless it is deleted */

	/* we could just catch the anchor here while another thread
	 * is busy deleting it. Just unlock and let the other do its job */
	if(tp->autr->revoked) {
		log_nametypeclass(VERB_ALGO, "autotrust not processed, "
			"trust point revoked", tp->name, 
			LDNS_RR_TYPE_DNSKEY, tp->dclass);
		lock_basic_unlock(&tp->lock);
		return 0; /* it is revoked */
	}

	/* query_dnskeys(): */
	tp->autr->last_queried = *env->now;

	log_nametypeclass(VERB_ALGO, "autotrust process for",
		tp->name, LDNS_RR_TYPE_DNSKEY, tp->dclass);
	/* see if time alone makes some keys valid */
	autr_holddown_exceed(env, tp, &changed);
	if(changed) {
		verbose(VERB_ALGO, "autotrust: morekeys, reassemble");
		if(!autr_assemble(tp)) {
			log_err("malloc failure assembling autotrust keys");
			return 1; /* unchanged */
		}
	}
	/* did we get any data? */
	if(!dnskey_rrset) {
		verbose(VERB_ALGO, "autotrust: no dnskey rrset");
		/* no update of query_failed, because then we would have
		 * to write to disk. But we cannot because we maybe are
		 * still 'initializing' with DS records, that we cannot write
		 * in the full format (which only contains KSKs). */
		return 1; /* trust point exists */
	}
	/* check for revoked keys to remove immediately */
	check_contains_revoked(env, ve, tp, dnskey_rrset, &changed, qstate);
	if(changed) {
		verbose(VERB_ALGO, "autotrust: revokedkeys, reassemble");
		if(!autr_assemble(tp)) {
			log_err("malloc failure assembling autotrust keys");
			return 1; /* unchanged */
		}
		if(!tp->ds_rrset && !tp->dnskey_rrset) {
			/* no more keys, all are revoked */
			/* this is a success for this probe attempt */
			tp->autr->last_success = *env->now;
			autr_tp_remove(env, tp, dnskey_rrset);
			return 0; /* trust point removed */
		}
	}
	/* verify the dnskey rrset and see if it is valid. */
	if(!verify_dnskey(env, ve, tp, dnskey_rrset, qstate)) {
		verbose(VERB_ALGO, "autotrust: dnskey did not verify.");
		/* only increase failure count if this is not the first prime,
		 * this means there was a previous successful probe */
		if(tp->autr->last_success) {
			tp->autr->query_failed += 1;
			autr_write_file(env, tp);
		}
		return 1; /* trust point exists */
	}

	tp->autr->last_success = *env->now;
	tp->autr->query_failed = 0;

	/* Add new trust anchors to the data structure
	 * - note which trust anchors are seen this probe.
	 * Set trustpoint query_interval and retry_time.
	 * - find minimum rrsig expiration interval
	 */
	if(!update_events(env, ve, tp, dnskey_rrset, &changed)) {
		log_err("malloc failure in autotrust update_events. "
			"trust point unchanged.");
		return 1; /* trust point unchanged, so exists */
	}

	/* - for every SEP key do the 5011 statetable.
	 * - remove missing trustanchors (if veryold and we have new anchors).
	 */
	if(!do_statetable(env, tp, &changed)) {
		log_err("malloc failure in autotrust do_statetable. "
			"trust point unchanged.");
		return 1; /* trust point unchanged, so exists */
	}

	autr_cleanup_keys(tp);
	if(!set_next_probe(env, tp, dnskey_rrset))
		return 0; /* trust point does not exist */
	autr_write_file(env, tp);
	if(changed) {
		verbose(VERB_ALGO, "autotrust: changed, reassemble");
		if(!autr_assemble(tp)) {
			log_err("malloc failure assembling autotrust keys");
			return 1; /* unchanged */
		}
		if(!tp->ds_rrset && !tp->dnskey_rrset) {
			/* no more keys, all are revoked */
			autr_tp_remove(env, tp, dnskey_rrset);
			return 0; /* trust point removed */
		}
	} else verbose(VERB_ALGO, "autotrust: no changes");
	
	return 1; /* trust point exists */
}