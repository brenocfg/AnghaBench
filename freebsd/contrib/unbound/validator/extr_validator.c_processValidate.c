#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_37__   TYPE_5__ ;
typedef  struct TYPE_36__   TYPE_3__ ;
typedef  struct TYPE_35__   TYPE_2__ ;
typedef  struct TYPE_34__   TYPE_26__ ;
typedef  struct TYPE_33__   TYPE_1__ ;

/* Type definitions */
struct val_qstate {scalar_t__ restart_count; TYPE_2__* chase_reply; TYPE_5__* key_entry; int /*<<< orphan*/  qchase; TYPE_1__* orig_msg; int /*<<< orphan*/  rrset_skip; int /*<<< orphan*/ * signer_name; int /*<<< orphan*/  state; } ;
struct val_env {int /*<<< orphan*/  kcache; } ;
struct module_qstate {int /*<<< orphan*/  reply_origin; TYPE_3__* env; int /*<<< orphan*/ * errinf; int /*<<< orphan*/  qinfo; int /*<<< orphan*/  query_flags; } ;
typedef  enum val_classification { ____Placeholder_val_classification } val_classification ;
struct TYPE_37__ {int /*<<< orphan*/  key_class; int /*<<< orphan*/  name; } ;
struct TYPE_36__ {int /*<<< orphan*/  rrset_cache; } ;
struct TYPE_35__ {scalar_t__ security; int /*<<< orphan*/  flags; int /*<<< orphan*/  an_numrrsets; int /*<<< orphan*/  rrset_count; scalar_t__ ar_numrrsets; scalar_t__ ns_numrrsets; } ;
struct TYPE_34__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  an_numrrsets; int /*<<< orphan*/  rrset_count; scalar_t__ ar_numrrsets; scalar_t__ ns_numrrsets; } ;
struct TYPE_33__ {TYPE_26__* rep; } ;

/* Variables and functions */
 scalar_t__ FLAGS_GET_RCODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FLAGS_SET_RCODE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_DNSKEY ; 
#define  VAL_CLASS_ANY 134 
#define  VAL_CLASS_CNAME 133 
#define  VAL_CLASS_CNAMENOANSWER 132 
#define  VAL_CLASS_NAMEERROR 131 
#define  VAL_CLASS_NODATA 130 
#define  VAL_CLASS_POSITIVE 129 
#define  VAL_CLASS_REFERRAL 128 
 int /*<<< orphan*/  VAL_FINISHED_STATE ; 
 scalar_t__ VAL_MAX_RESTART_COUNT ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  VERB_DETAIL ; 
 scalar_t__ detect_wrongly_truncated (TYPE_26__*) ; 
 int /*<<< orphan*/  errinf (struct module_qstate*,char*) ; 
 int /*<<< orphan*/  errinf_origin (struct module_qstate*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_cache_insert (int /*<<< orphan*/ ,TYPE_5__*,struct module_qstate*) ; 
 scalar_t__ key_entry_isbad (TYPE_5__*) ; 
 scalar_t__ key_entry_isnull (TYPE_5__*) ; 
 int /*<<< orphan*/  log_err (char*,int) ; 
 int /*<<< orphan*/  log_nametypeclass (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_query_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_spurious_authority (TYPE_2__*,TYPE_26__*) ; 
 scalar_t__ sec_status_bogus ; 
 scalar_t__ sec_status_insecure ; 
 char* sec_status_to_string (scalar_t__) ; 
 char* val_classification_to_string (int) ; 
 int val_classify_response (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_26__*,int /*<<< orphan*/ ) ; 
 int val_error (struct module_qstate*,int) ; 
 int /*<<< orphan*/  val_mark_insecure (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  validate_any_response (TYPE_3__*,struct val_env*,int /*<<< orphan*/ *,TYPE_2__*,TYPE_5__*) ; 
 int /*<<< orphan*/  validate_cname_noanswer_response (TYPE_3__*,struct val_env*,int /*<<< orphan*/ *,TYPE_2__*,TYPE_5__*) ; 
 int /*<<< orphan*/  validate_cname_response (TYPE_3__*,struct val_env*,int /*<<< orphan*/ *,TYPE_2__*,TYPE_5__*) ; 
 int /*<<< orphan*/  validate_msg_signatures (struct module_qstate*,TYPE_3__*,struct val_env*,int /*<<< orphan*/ *,TYPE_2__*,TYPE_5__*) ; 
 int /*<<< orphan*/  validate_nameerror_response (TYPE_3__*,struct val_env*,int /*<<< orphan*/ *,TYPE_2__*,TYPE_5__*,int*) ; 
 int /*<<< orphan*/  validate_nodata_response (TYPE_3__*,struct val_env*,int /*<<< orphan*/ *,TYPE_2__*,TYPE_5__*) ; 
 int /*<<< orphan*/  validate_positive_response (TYPE_3__*,struct val_env*,int /*<<< orphan*/ *,TYPE_2__*,TYPE_5__*) ; 
 int /*<<< orphan*/  validate_referral_response (TYPE_2__*) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int
processValidate(struct module_qstate* qstate, struct val_qstate* vq, 
	struct val_env* ve, int id)
{
	enum val_classification subtype;
	int rcode;

	if(!vq->key_entry) {
		verbose(VERB_ALGO, "validate: no key entry, failed");
		return val_error(qstate, id);
	}

	/* This is the default next state. */
	vq->state = VAL_FINISHED_STATE;

	/* Unsigned responses must be underneath a "null" key entry.*/
	if(key_entry_isnull(vq->key_entry)) {
		verbose(VERB_DETAIL, "Verified that %sresponse is INSECURE",
			vq->signer_name?"":"unsigned ");
		vq->chase_reply->security = sec_status_insecure;
		val_mark_insecure(vq->chase_reply, vq->key_entry->name, 
			qstate->env->rrset_cache, qstate->env);
		key_cache_insert(ve->kcache, vq->key_entry, qstate);
		return 1;
	}

	if(key_entry_isbad(vq->key_entry)) {
		log_nametypeclass(VERB_DETAIL, "Could not establish a chain "
			"of trust to keys for", vq->key_entry->name,
			LDNS_RR_TYPE_DNSKEY, vq->key_entry->key_class);
		vq->chase_reply->security = sec_status_bogus;
		errinf(qstate, "while building chain of trust");
		if(vq->restart_count >= VAL_MAX_RESTART_COUNT)
			key_cache_insert(ve->kcache, vq->key_entry, qstate);
		return 1;
	}

	/* signerName being null is the indicator that this response was 
	 * unsigned */
	if(vq->signer_name == NULL) {
		log_query_info(VERB_ALGO, "processValidate: state has no "
			"signer name", &vq->qchase);
		verbose(VERB_DETAIL, "Could not establish validation of "
		          "INSECURE status of unsigned response.");
		errinf(qstate, "no signatures");
		errinf_origin(qstate, qstate->reply_origin);
		vq->chase_reply->security = sec_status_bogus;
		return 1;
	}
	subtype = val_classify_response(qstate->query_flags, &qstate->qinfo,
		&vq->qchase, vq->orig_msg->rep, vq->rrset_skip);
	if(subtype != VAL_CLASS_REFERRAL)
		remove_spurious_authority(vq->chase_reply, vq->orig_msg->rep);

	/* check signatures in the message; 
	 * answer and authority must be valid, additional is only checked. */
	if(!validate_msg_signatures(qstate, qstate->env, ve, &vq->qchase, 
		vq->chase_reply, vq->key_entry)) {
		/* workaround bad recursor out there that truncates (even
		 * with EDNS4k) to 512 by removing RRSIG from auth section
		 * for positive replies*/
		if((subtype == VAL_CLASS_POSITIVE || subtype == VAL_CLASS_ANY
			|| subtype == VAL_CLASS_CNAME) &&
			detect_wrongly_truncated(vq->orig_msg->rep)) {
			/* truncate the message some more */
			vq->orig_msg->rep->ns_numrrsets = 0;
			vq->orig_msg->rep->ar_numrrsets = 0;
			vq->orig_msg->rep->rrset_count = 
				vq->orig_msg->rep->an_numrrsets;
			vq->chase_reply->ns_numrrsets = 0;
			vq->chase_reply->ar_numrrsets = 0;
			vq->chase_reply->rrset_count = 
				vq->chase_reply->an_numrrsets;
			qstate->errinf = NULL;
		}
		else {
			verbose(VERB_DETAIL, "Validate: message contains "
				"bad rrsets");
			return 1;
		}
	}

	switch(subtype) {
		case VAL_CLASS_POSITIVE:
			verbose(VERB_ALGO, "Validating a positive response");
			validate_positive_response(qstate->env, ve,
				&vq->qchase, vq->chase_reply, vq->key_entry);
			verbose(VERB_DETAIL, "validate(positive): %s",
			  	sec_status_to_string(
				vq->chase_reply->security));
			break;

		case VAL_CLASS_NODATA:
			verbose(VERB_ALGO, "Validating a nodata response");
			validate_nodata_response(qstate->env, ve,
				&vq->qchase, vq->chase_reply, vq->key_entry);
			verbose(VERB_DETAIL, "validate(nodata): %s",
			  	sec_status_to_string(
				vq->chase_reply->security));
			break;

		case VAL_CLASS_NAMEERROR:
			rcode = (int)FLAGS_GET_RCODE(vq->orig_msg->rep->flags);
			verbose(VERB_ALGO, "Validating a nxdomain response");
			validate_nameerror_response(qstate->env, ve, 
				&vq->qchase, vq->chase_reply, vq->key_entry, &rcode);
			verbose(VERB_DETAIL, "validate(nxdomain): %s",
			  	sec_status_to_string(
				vq->chase_reply->security));
			FLAGS_SET_RCODE(vq->orig_msg->rep->flags, rcode);
			FLAGS_SET_RCODE(vq->chase_reply->flags, rcode);
			break;

		case VAL_CLASS_CNAME:
			verbose(VERB_ALGO, "Validating a cname response");
			validate_cname_response(qstate->env, ve,
				&vq->qchase, vq->chase_reply, vq->key_entry);
			verbose(VERB_DETAIL, "validate(cname): %s",
			  	sec_status_to_string(
				vq->chase_reply->security));
			break;

		case VAL_CLASS_CNAMENOANSWER:
			verbose(VERB_ALGO, "Validating a cname noanswer "
				"response");
			validate_cname_noanswer_response(qstate->env, ve,
				&vq->qchase, vq->chase_reply, vq->key_entry);
			verbose(VERB_DETAIL, "validate(cname_noanswer): %s",
			  	sec_status_to_string(
				vq->chase_reply->security));
			break;

		case VAL_CLASS_REFERRAL:
			verbose(VERB_ALGO, "Validating a referral response");
			validate_referral_response(vq->chase_reply);
			verbose(VERB_DETAIL, "validate(referral): %s",
			  	sec_status_to_string(
				vq->chase_reply->security));
			break;

		case VAL_CLASS_ANY:
			verbose(VERB_ALGO, "Validating a positive ANY "
				"response");
			validate_any_response(qstate->env, ve, &vq->qchase, 
				vq->chase_reply, vq->key_entry);
			verbose(VERB_DETAIL, "validate(positive_any): %s",
			  	sec_status_to_string(
				vq->chase_reply->security));
			break;

		default:
			log_err("validate: unhandled response subtype: %d",
				subtype);
	}
	if(vq->chase_reply->security == sec_status_bogus) {
		if(subtype == VAL_CLASS_POSITIVE)
			errinf(qstate, "wildcard");
		else errinf(qstate, val_classification_to_string(subtype));
		errinf(qstate, "proof failed");
		errinf_origin(qstate, qstate->reply_origin);
	}

	return 1;
}