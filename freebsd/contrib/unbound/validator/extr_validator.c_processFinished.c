#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_16__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_22__ {scalar_t__ qtype; scalar_t__* qname; int /*<<< orphan*/  qclass; } ;
struct val_qstate {scalar_t__ rrset_skip; int dlv_checked; int restart_count; TYPE_2__* orig_msg; TYPE_6__ qchase; void* state; TYPE_3__* chase_reply; } ;
struct val_env {scalar_t__ bogus_ttl; } ;
struct module_qstate {int query_flags; int /*<<< orphan*/ * ext_state; TYPE_2__* return_msg; int /*<<< orphan*/  return_rcode; TYPE_9__* env; int /*<<< orphan*/  prefetch_leeway; int /*<<< orphan*/  no_cache_store; TYPE_6__ qinfo; int /*<<< orphan*/ * errinf; int /*<<< orphan*/ * reply_origin; int /*<<< orphan*/  region; int /*<<< orphan*/  blacklist; } ;
typedef  enum val_classification { ____Placeholder_val_classification } val_classification ;
struct TYPE_23__ {TYPE_16__* anchors; TYPE_1__* cfg; int /*<<< orphan*/  neg_cache; } ;
struct TYPE_21__ {scalar_t__ security; scalar_t__ an_numrrsets; scalar_t__ ns_numrrsets; scalar_t__ rrset_count; scalar_t__ ttl; scalar_t__ serve_expired_ttl; int /*<<< orphan*/  prefetch_ttl; } ;
struct TYPE_20__ {scalar_t__ security; } ;
struct TYPE_19__ {TYPE_4__* rep; int /*<<< orphan*/  qinfo; } ;
struct TYPE_18__ {int val_log_level; scalar_t__ root_key_sentinel; scalar_t__ val_permissive_mode; scalar_t__ log_servfail; int /*<<< orphan*/  val_log_squelch; scalar_t__ serve_expired_ttl; } ;
struct TYPE_17__ {scalar_t__ dlv_anchor; } ;

/* Variables and functions */
 int BIT_RD ; 
 int /*<<< orphan*/  LDNS_RCODE_NOERROR ; 
 scalar_t__ LDNS_RR_TYPE_A ; 
 scalar_t__ LDNS_RR_TYPE_AAAA ; 
 int /*<<< orphan*/  PREFETCH_TTL_CALC (scalar_t__) ; 
 int /*<<< orphan*/  SENTINEL_IS ; 
 scalar_t__ SENTINEL_KEYTAG_LEN ; 
 int /*<<< orphan*/  SENTINEL_NOT ; 
 int VAL_CLASS_CNAME ; 
 int VAL_CLASS_REFERRAL ; 
 void* VAL_INIT_STATE ; 
 int VAL_MAX_RESTART_COUNT ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  VERB_DETAIL ; 
 scalar_t__ anchor_has_keytag (TYPE_16__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dname_lab_startswith (scalar_t__*,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  dns_cache_store (TYPE_9__*,int /*<<< orphan*/ *,TYPE_4__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 char* errinf_to_str_bogus (struct module_qstate*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  log_info (char*,char*) ; 
 int /*<<< orphan*/  log_query_info (int /*<<< orphan*/ ,char*,TYPE_6__*) ; 
 int /*<<< orphan*/  memset (struct val_qstate*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  module_finished ; 
 int /*<<< orphan*/  module_restart_next ; 
 scalar_t__ sec_status_bogus ; 
 scalar_t__ sec_status_indeterminate ; 
 scalar_t__ sec_status_insecure ; 
 scalar_t__ sec_status_secure ; 
 void* sec_status_secure_sentinel_fail ; 
 void* sec_status_unchecked ; 
 scalar_t__ sentinel_get_keytag (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  val_blacklist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  val_chase_cname (TYPE_6__*,TYPE_4__*,scalar_t__*) ; 
 int /*<<< orphan*/  val_check_nonsecure (TYPE_9__*,TYPE_4__*) ; 
 int val_classify_response (int,TYPE_6__*,TYPE_6__*,TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  val_dlv_init (struct module_qstate*,struct val_qstate*,struct val_env*,int) ; 
 int /*<<< orphan*/  val_neg_addreply (int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ val_next_unchecked (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
processFinished(struct module_qstate* qstate, struct val_qstate* vq, 
	struct val_env* ve, int id)
{
	enum val_classification subtype = val_classify_response(
		qstate->query_flags, &qstate->qinfo, &vq->qchase, 
		vq->orig_msg->rep, vq->rrset_skip);

	/* if the result is insecure or indeterminate and we have not 
	 * checked the DLV yet, check the DLV */
	if((vq->chase_reply->security == sec_status_insecure ||
		vq->chase_reply->security == sec_status_indeterminate) &&
		qstate->env->anchors->dlv_anchor && !vq->dlv_checked) {
		vq->dlv_checked = 1;
		if(!val_dlv_init(qstate, vq, ve, id))
			return 0;
	}

	/* store overall validation result in orig_msg */
	if(vq->rrset_skip == 0)
		vq->orig_msg->rep->security = vq->chase_reply->security;
	else if(subtype != VAL_CLASS_REFERRAL ||
		vq->rrset_skip < vq->orig_msg->rep->an_numrrsets + 
		vq->orig_msg->rep->ns_numrrsets) {
		/* ignore sec status of additional section if a referral 
		 * type message skips there and
		 * use the lowest security status as end result. */
		if(vq->chase_reply->security < vq->orig_msg->rep->security)
			vq->orig_msg->rep->security = 
				vq->chase_reply->security;
	}

	if(subtype == VAL_CLASS_REFERRAL) {
		/* for a referral, move to next unchecked rrset and check it*/
		vq->rrset_skip = val_next_unchecked(vq->orig_msg->rep, 
			vq->rrset_skip);
		if(vq->rrset_skip < vq->orig_msg->rep->rrset_count) {
			/* and restart for this rrset */
			verbose(VERB_ALGO, "validator: go to next rrset");
			vq->chase_reply->security = sec_status_unchecked;
			vq->dlv_checked = 0; /* can do DLV for this RR */
			vq->state = VAL_INIT_STATE;
			return 1;
		}
		/* referral chase is done */
	}
	if(vq->chase_reply->security != sec_status_bogus &&
		subtype == VAL_CLASS_CNAME) {
		/* chase the CNAME; process next part of the message */
		if(!val_chase_cname(&vq->qchase, vq->orig_msg->rep, 
			&vq->rrset_skip)) {
			verbose(VERB_ALGO, "validator: failed to chase CNAME");
			vq->orig_msg->rep->security = sec_status_bogus;
		} else {
			/* restart process for new qchase at rrset_skip */
			log_query_info(VERB_ALGO, "validator: chased to",
				&vq->qchase);
			vq->chase_reply->security = sec_status_unchecked;
			vq->dlv_checked = 0; /* can do DLV for this RR */
			vq->state = VAL_INIT_STATE;
			return 1;
		}
	}

	if(vq->orig_msg->rep->security == sec_status_secure) {
		/* If the message is secure, check that all rrsets are
		 * secure (i.e. some inserted RRset for CNAME chain with
		 * a different signer name). And drop additional rrsets
		 * that are not secure (if clean-additional option is set) */
		/* this may cause the msg to be marked bogus */
		val_check_nonsecure(qstate->env, vq->orig_msg->rep);
		if(vq->orig_msg->rep->security == sec_status_secure) {
			log_query_info(VERB_DETAIL, "validation success", 
				&qstate->qinfo);
			if(!qstate->no_cache_store) {
				val_neg_addreply(qstate->env->neg_cache,
					vq->orig_msg->rep);
			}
		}
	}

	/* if the result is bogus - set message ttl to bogus ttl to avoid
	 * endless bogus revalidation */
	if(vq->orig_msg->rep->security == sec_status_bogus) {
		/* see if we can try again to fetch data */
		if(vq->restart_count < VAL_MAX_RESTART_COUNT) {
			int restart_count = vq->restart_count+1;
			verbose(VERB_ALGO, "validation failed, "
				"blacklist and retry to fetch data");
			val_blacklist(&qstate->blacklist, qstate->region, 
				qstate->reply_origin, 0);
			qstate->reply_origin = NULL;
			qstate->errinf = NULL;
			memset(vq, 0, sizeof(*vq));
			vq->restart_count = restart_count;
			vq->state = VAL_INIT_STATE;
			verbose(VERB_ALGO, "pass back to next module");
			qstate->ext_state[id] = module_restart_next;
			return 0;
		}

		vq->orig_msg->rep->ttl = ve->bogus_ttl;
		vq->orig_msg->rep->prefetch_ttl = 
			PREFETCH_TTL_CALC(vq->orig_msg->rep->ttl);
		vq->orig_msg->rep->serve_expired_ttl = 
			vq->orig_msg->rep->ttl + qstate->env->cfg->serve_expired_ttl;
		if((qstate->env->cfg->val_log_level >= 1 ||
			qstate->env->cfg->log_servfail) &&
			!qstate->env->cfg->val_log_squelch) {
			if(qstate->env->cfg->val_log_level < 2 &&
				!qstate->env->cfg->log_servfail)
				log_query_info(0, "validation failure",
					&qstate->qinfo);
			else {
				char* err = errinf_to_str_bogus(qstate);
				if(err) log_info("%s", err);
				free(err);
			}
		}
		/*
		 * If set, the validator will not make messages bogus, instead
		 * indeterminate is issued, so that no clients receive SERVFAIL.
		 * This allows an operator to run validation 'shadow' without
		 * hurting responses to clients.
		 */
		/* If we are in permissive mode, bogus gets indeterminate */
		if(qstate->env->cfg->val_permissive_mode)
			vq->orig_msg->rep->security = sec_status_indeterminate;
	}

	if(vq->orig_msg->rep->security == sec_status_secure &&
		qstate->env->cfg->root_key_sentinel &&
		(qstate->qinfo.qtype == LDNS_RR_TYPE_A ||
		qstate->qinfo.qtype == LDNS_RR_TYPE_AAAA)) {
		char* keytag_start;
		uint16_t keytag;
		if(*qstate->qinfo.qname == strlen(SENTINEL_IS) +
			SENTINEL_KEYTAG_LEN &&
			dname_lab_startswith(qstate->qinfo.qname, SENTINEL_IS,
			&keytag_start)) {
			if(sentinel_get_keytag(keytag_start, &keytag) &&
				!anchor_has_keytag(qstate->env->anchors,
				(uint8_t*)"", 1, 0, vq->qchase.qclass, keytag)) {
				vq->orig_msg->rep->security =
					sec_status_secure_sentinel_fail;
			}
		} else if(*qstate->qinfo.qname == strlen(SENTINEL_NOT) +
			SENTINEL_KEYTAG_LEN &&
			dname_lab_startswith(qstate->qinfo.qname, SENTINEL_NOT,
			&keytag_start)) {
			if(sentinel_get_keytag(keytag_start, &keytag) &&
				anchor_has_keytag(qstate->env->anchors,
				(uint8_t*)"", 1, 0, vq->qchase.qclass, keytag)) {
				vq->orig_msg->rep->security =
					sec_status_secure_sentinel_fail;
			}
		}
	}
	/* store results in cache */
	if(qstate->query_flags&BIT_RD) {
		/* if secure, this will override cache anyway, no need
		 * to check if from parentNS */
		if(!qstate->no_cache_store) {
			if(!dns_cache_store(qstate->env, &vq->orig_msg->qinfo,
				vq->orig_msg->rep, 0, qstate->prefetch_leeway, 0, NULL,
				qstate->query_flags)) {
				log_err("out of memory caching validator results");
			}
		}
	} else {
		/* for a referral, store the verified RRsets */
		/* and this does not get prefetched, so no leeway */
		if(!dns_cache_store(qstate->env, &vq->orig_msg->qinfo,
			vq->orig_msg->rep, 1, 0, 0, NULL,
			qstate->query_flags)) {
			log_err("out of memory caching validator results");
		}
	}
	qstate->return_rcode = LDNS_RCODE_NOERROR;
	qstate->return_msg = vq->orig_msg;
	qstate->ext_state[id] = module_finished;
	return 0;
}