#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_10__ {size_t qname_len; int /*<<< orphan*/  qclass; int /*<<< orphan*/ * qname; } ;
struct val_qstate {size_t signer_len; TYPE_4__ qchase; TYPE_3__* ds_rrset; TYPE_5__* key_entry; int /*<<< orphan*/  chain_blacklist; void* state; TYPE_1__* chase_reply; int /*<<< orphan*/ * empty_DS_name; int /*<<< orphan*/ * signer_name; } ;
struct module_qstate {int /*<<< orphan*/  region; int /*<<< orphan*/  env; int /*<<< orphan*/  blacklist; int /*<<< orphan*/  reply_origin; } ;
struct dns_msg {int /*<<< orphan*/  qinfo; } ;
struct TYPE_11__ {int /*<<< orphan*/ * name; } ;
struct TYPE_8__ {size_t dname_len; int /*<<< orphan*/ * dname; } ;
struct TYPE_9__ {TYPE_2__ rk; } ;
struct TYPE_7__ {void* security; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_CD ; 
 int /*<<< orphan*/  LDNS_RCODE_NOERROR ; 
 int /*<<< orphan*/  LDNS_RR_CLASS_IN ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_DNSKEY ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_DS ; 
 void* VAL_FINISHED_STATE ; 
 void* VAL_VALIDATE_STATE ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int dname_count_labels (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dname_remove_labels (int /*<<< orphan*/ **,size_t*,int) ; 
 int /*<<< orphan*/  dname_subdomain_c (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errinf (struct module_qstate*,char*) ; 
 int /*<<< orphan*/  errinf_origin (struct module_qstate*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generate_request (struct module_qstate*,int,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct module_qstate**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_entry_isbad (TYPE_5__*) ; 
 scalar_t__ key_entry_isnull (TYPE_5__*) ; 
 int /*<<< orphan*/  log_assert (int) ; 
 int /*<<< orphan*/  log_nametypeclass (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_query_info (int /*<<< orphan*/ ,char*,TYPE_4__*) ; 
 int /*<<< orphan*/  process_ds_response (struct module_qstate*,struct val_qstate*,int,int /*<<< orphan*/ ,struct dns_msg*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ query_dname_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* sec_status_bogus ; 
 int val_error (struct module_qstate*,int) ; 
 struct dns_msg* val_find_DS (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int
processFindKey(struct module_qstate* qstate, struct val_qstate* vq, int id)
{
	uint8_t* target_key_name, *current_key_name;
	size_t target_key_len;
	int strip_lab;
	struct module_qstate* newq = NULL;

	log_query_info(VERB_ALGO, "validator: FindKey", &vq->qchase);
	/* We know that state.key_entry is not 0 or bad key -- if it were,
	 * then previous processing should have directed this event to 
	 * a different state. 
	 * It could be an isnull key, which signals that a DLV was just
	 * done and the DNSKEY after the DLV failed with dnssec-retry state
	 * and the DNSKEY has to be performed again. */
	log_assert(vq->key_entry && !key_entry_isbad(vq->key_entry));
	if(key_entry_isnull(vq->key_entry)) {
		if(!generate_request(qstate, id, vq->ds_rrset->rk.dname, 
			vq->ds_rrset->rk.dname_len, LDNS_RR_TYPE_DNSKEY, 
			vq->qchase.qclass, BIT_CD, &newq, 0)) {
			verbose(VERB_ALGO, "error generating DNSKEY request");
			return val_error(qstate, id);
		}
		return 0;
	}

	target_key_name = vq->signer_name;
	target_key_len = vq->signer_len;
	if(!target_key_name) {
		target_key_name = vq->qchase.qname;
		target_key_len = vq->qchase.qname_len;
	}

	current_key_name = vq->key_entry->name;

	/* If our current key entry matches our target, then we are done. */
	if(query_dname_compare(target_key_name, current_key_name) == 0) {
		vq->state = VAL_VALIDATE_STATE;
		return 1;
	}

	if(vq->empty_DS_name) {
		/* if the last empty nonterminal/emptyDS name we detected is
		 * below the current key, use that name to make progress
		 * along the chain of trust */
		if(query_dname_compare(target_key_name, 
			vq->empty_DS_name) == 0) {
			/* do not query for empty_DS_name again */
			verbose(VERB_ALGO, "Cannot retrieve DS for signature");
			errinf(qstate, "no signatures");
			errinf_origin(qstate, qstate->reply_origin);
			vq->chase_reply->security = sec_status_bogus;
			vq->state = VAL_FINISHED_STATE;
			return 1;
		}
		current_key_name = vq->empty_DS_name;
	}

	log_nametypeclass(VERB_ALGO, "current keyname", current_key_name,
		LDNS_RR_TYPE_DNSKEY, LDNS_RR_CLASS_IN);
	log_nametypeclass(VERB_ALGO, "target keyname", target_key_name,
		LDNS_RR_TYPE_DNSKEY, LDNS_RR_CLASS_IN);
	/* assert we are walking down the DNS tree */
	if(!dname_subdomain_c(target_key_name, current_key_name)) {
		verbose(VERB_ALGO, "bad signer name");
		vq->chase_reply->security = sec_status_bogus;
		vq->state = VAL_FINISHED_STATE;
		return 1;
	}
	/* so this value is >= -1 */
	strip_lab = dname_count_labels(target_key_name) - 
		dname_count_labels(current_key_name) - 1;
	log_assert(strip_lab >= -1);
	verbose(VERB_ALGO, "striplab %d", strip_lab);
	if(strip_lab > 0) {
		dname_remove_labels(&target_key_name, &target_key_len, 
			strip_lab);
	}
	log_nametypeclass(VERB_ALGO, "next keyname", target_key_name,
		LDNS_RR_TYPE_DNSKEY, LDNS_RR_CLASS_IN);

	/* The next step is either to query for the next DS, or to query 
	 * for the next DNSKEY. */
	if(vq->ds_rrset)
		log_nametypeclass(VERB_ALGO, "DS RRset", vq->ds_rrset->rk.dname, LDNS_RR_TYPE_DS, LDNS_RR_CLASS_IN);
	else verbose(VERB_ALGO, "No DS RRset");

	if(vq->ds_rrset && query_dname_compare(vq->ds_rrset->rk.dname,
		vq->key_entry->name) != 0) {
		if(!generate_request(qstate, id, vq->ds_rrset->rk.dname, 
			vq->ds_rrset->rk.dname_len, LDNS_RR_TYPE_DNSKEY, 
			vq->qchase.qclass, BIT_CD, &newq, 0)) {
			verbose(VERB_ALGO, "error generating DNSKEY request");
			return val_error(qstate, id);
		}
		return 0;
	}

	if(!vq->ds_rrset || query_dname_compare(vq->ds_rrset->rk.dname,
		target_key_name) != 0) {
		/* check if there is a cache entry : pick up an NSEC if
		 * there is no DS, check if that NSEC has DS-bit unset, and
		 * thus can disprove the secure delegation we seek.
		 * We can then use that NSEC even in the absence of a SOA
		 * record that would be required by the iterator to supply
		 * a completely protocol-correct response. 
		 * Uses negative cache for NSEC3 lookup of DS responses. */
		/* only if cache not blacklisted, of course */
		struct dns_msg* msg;
		if(!qstate->blacklist && !vq->chain_blacklist &&
			(msg=val_find_DS(qstate->env, target_key_name, 
			target_key_len, vq->qchase.qclass, qstate->region,
			vq->key_entry->name)) ) {
			verbose(VERB_ALGO, "Process cached DS response");
			process_ds_response(qstate, vq, id, LDNS_RCODE_NOERROR,
				msg, &msg->qinfo, NULL);
			return 1; /* continue processing ds-response results */
		}
		if(!generate_request(qstate, id, target_key_name, 
			target_key_len, LDNS_RR_TYPE_DS, vq->qchase.qclass,
			BIT_CD, &newq, 0)) {
			verbose(VERB_ALGO, "error generating DS request");
			return val_error(qstate, id);
		}
		return 0;
	}

	/* Otherwise, it is time to query for the DNSKEY */
	if(!generate_request(qstate, id, vq->ds_rrset->rk.dname, 
		vq->ds_rrset->rk.dname_len, LDNS_RR_TYPE_DNSKEY, 
		vq->qchase.qclass, BIT_CD, &newq, 0)) {
		verbose(VERB_ALGO, "error generating DNSKEY request");
		return val_error(qstate, id);
	}

	return 0;
}