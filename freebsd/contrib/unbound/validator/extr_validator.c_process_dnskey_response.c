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
struct val_qstate {scalar_t__ restart_count; struct key_entry_key* key_entry; int /*<<< orphan*/ * chain_blacklist; void* state; int /*<<< orphan*/  ds_rrset; } ;
struct val_env {int /*<<< orphan*/  kcache; } ;
struct ub_packed_rrset_key {int dummy; } ;
struct sock_list {int dummy; } ;
struct query_info {int /*<<< orphan*/  qname; int /*<<< orphan*/  qclass; int /*<<< orphan*/  qname_len; } ;
struct module_qstate {int /*<<< orphan*/ * errinf; int /*<<< orphan*/  region; TYPE_2__* env; } ;
struct key_entry_key {int dummy; } ;
struct dns_msg {int /*<<< orphan*/  rep; } ;
struct TYPE_4__ {TYPE_1__* cfg; int /*<<< orphan*/ * now; scalar_t__* modinfo; } ;
struct TYPE_3__ {int harden_algo_downgrade; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOGUS_KEY_TTL ; 
 int LDNS_RCODE_NOERROR ; 
 scalar_t__ VAL_MAX_RESTART_COUNT ; 
 void* VAL_VALIDATE_STATE ; 
 int /*<<< orphan*/  VERB_DETAIL ; 
 int /*<<< orphan*/  errinf (struct module_qstate*,char*) ; 
 int /*<<< orphan*/  errinf_dname (struct module_qstate*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errinf_origin (struct module_qstate*,struct sock_list*) ; 
 int /*<<< orphan*/  key_cache_insert (int /*<<< orphan*/ ,struct key_entry_key*,struct module_qstate*) ; 
 struct key_entry_key* key_entry_create_bad (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ key_entry_isbad (struct key_entry_key*) ; 
 int /*<<< orphan*/  key_entry_isgood (struct key_entry_key*) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  log_query_info (int /*<<< orphan*/ ,char*,struct query_info*) ; 
 struct ub_packed_rrset_key* reply_find_answer_rrset (struct query_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  val_blacklist (int /*<<< orphan*/ **,int /*<<< orphan*/ ,struct sock_list*,int) ; 
 struct key_entry_key* val_verify_new_DNSKEYs (int /*<<< orphan*/ ,TYPE_2__*,struct val_env*,struct ub_packed_rrset_key*,int /*<<< orphan*/ ,int,char**,struct module_qstate*) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
process_dnskey_response(struct module_qstate* qstate, struct val_qstate* vq,
	int id, int rcode, struct dns_msg* msg, struct query_info* qinfo,
	struct sock_list* origin)
{
	struct val_env* ve = (struct val_env*)qstate->env->modinfo[id];
	struct key_entry_key* old = vq->key_entry;
	struct ub_packed_rrset_key* dnskey = NULL;
	int downprot;
	char* reason = NULL;

	if(rcode == LDNS_RCODE_NOERROR)
		dnskey = reply_find_answer_rrset(qinfo, msg->rep);

	if(dnskey == NULL) {
		/* bad response */
		verbose(VERB_DETAIL, "Missing DNSKEY RRset in response to "
			"DNSKEY query.");
		if(vq->restart_count < VAL_MAX_RESTART_COUNT) {
			val_blacklist(&vq->chain_blacklist, qstate->region,
				origin, 1);
			qstate->errinf = NULL;
			vq->restart_count++;
			return;
		}
		vq->key_entry = key_entry_create_bad(qstate->region, 
			qinfo->qname, qinfo->qname_len, qinfo->qclass,
			BOGUS_KEY_TTL, *qstate->env->now);
		if(!vq->key_entry) {
			log_err("alloc failure in missing dnskey response");
			/* key_entry is NULL for failure in Validate */
		}
		errinf(qstate, "No DNSKEY record");
		errinf_origin(qstate, origin);
		errinf_dname(qstate, "for key", qinfo->qname);
		vq->state = VAL_VALIDATE_STATE;
		return;
	}
	if(!vq->ds_rrset) {
		log_err("internal error: no DS rrset for new DNSKEY response");
		vq->key_entry = NULL;
		vq->state = VAL_VALIDATE_STATE;
		return;
	}
	downprot = qstate->env->cfg->harden_algo_downgrade;
	vq->key_entry = val_verify_new_DNSKEYs(qstate->region, qstate->env,
		ve, dnskey, vq->ds_rrset, downprot, &reason, qstate);

	if(!vq->key_entry) {
		log_err("out of memory in verify new DNSKEYs");
		vq->state = VAL_VALIDATE_STATE;
		return;
	}
	/* If the key entry isBad or isNull, then we can move on to the next
	 * state. */
	if(!key_entry_isgood(vq->key_entry)) {
		if(key_entry_isbad(vq->key_entry)) {
			if(vq->restart_count < VAL_MAX_RESTART_COUNT) {
				val_blacklist(&vq->chain_blacklist, 
					qstate->region, origin, 1);
				qstate->errinf = NULL;
				vq->restart_count++;
				vq->key_entry = old;
				return;
			}
			verbose(VERB_DETAIL, "Did not match a DS to a DNSKEY, "
				"thus bogus.");
			errinf(qstate, reason);
			errinf_origin(qstate, origin);
			errinf_dname(qstate, "for key", qinfo->qname);
		}
		vq->chain_blacklist = NULL;
		vq->state = VAL_VALIDATE_STATE;
		return;
	}
	vq->chain_blacklist = NULL;
	qstate->errinf = NULL;

	/* The DNSKEY validated, so cache it as a trusted key rrset. */
	key_cache_insert(ve->kcache, vq->key_entry, qstate);

	/* If good, we stay in the FINDKEY state. */
	log_query_info(VERB_DETAIL, "validated DNSKEY", qinfo);
}