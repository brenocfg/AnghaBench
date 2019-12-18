#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_12__ {int /*<<< orphan*/  qclass; } ;
struct val_qstate {scalar_t__ dlv_status; size_t dlv_lookup_name_len; TYPE_6__ qchase; scalar_t__* dlv_lookup_name; void* state; scalar_t__ dlv_insecure_at; TYPE_2__* ds_rrset; int /*<<< orphan*/  key_entry; } ;
struct val_env {int /*<<< orphan*/  neg_cache; } ;
struct module_qstate {TYPE_5__* env; int /*<<< orphan*/  region; } ;
struct TYPE_11__ {int /*<<< orphan*/ * now; int /*<<< orphan*/  rrset_cache; TYPE_4__* anchors; } ;
struct TYPE_10__ {TYPE_3__* dlv_anchor; } ;
struct TYPE_9__ {int namelen; scalar_t__ name; } ;
struct TYPE_7__ {size_t dname_len; scalar_t__* dname; } ;
struct TYPE_8__ {TYPE_1__ rk; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_CD ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_DLV ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_DNSKEY ; 
 void* VAL_FINDKEY_STATE ; 
 void* VAL_FINISHED_STATE ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  VERB_QUERY ; 
 scalar_t__ dlv_ask_higher ; 
 scalar_t__ dlv_error ; 
 scalar_t__ dlv_success ; 
 scalar_t__ dlv_there_is_no_dlv ; 
 int /*<<< orphan*/  dname_remove_label (scalar_t__**,size_t*) ; 
 int dname_subdomain_c (scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  errinf (struct module_qstate*,char*) ; 
 int /*<<< orphan*/  generate_request (struct module_qstate*,int,scalar_t__*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct module_qstate**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_entry_create_null (int /*<<< orphan*/ ,scalar_t__*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_assert (int) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  log_nametypeclass (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__* regional_alloc_init (int /*<<< orphan*/ ,scalar_t__*,size_t) ; 
 int val_error (struct module_qstate*,int) ; 
 scalar_t__ val_neg_dlvlookup (int /*<<< orphan*/ ,scalar_t__*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
processDLVLookup(struct module_qstate* qstate, struct val_qstate* vq, 
	struct val_env* ve, int id)
{
	struct module_qstate* newq = NULL;
	/* see if this we are ready to continue normal resolution */
	/* we may need more DLV lookups */
	if(vq->dlv_status==dlv_error)
		verbose(VERB_ALGO, "DLV woke up with status dlv_error");
	else if(vq->dlv_status==dlv_success)
		verbose(VERB_ALGO, "DLV woke up with status dlv_success");
	else if(vq->dlv_status==dlv_ask_higher)
		verbose(VERB_ALGO, "DLV woke up with status dlv_ask_higher");
	else if(vq->dlv_status==dlv_there_is_no_dlv)
		verbose(VERB_ALGO, "DLV woke up with status dlv_there_is_no_dlv");
	else 	verbose(VERB_ALGO, "DLV woke up with status unknown");

	if(vq->dlv_status == dlv_error) {
		verbose(VERB_QUERY, "failed DLV lookup");
		errinf(qstate, "failed DLV lookup");
		return val_error(qstate, id);
	} else if(vq->dlv_status == dlv_success) {
		uint8_t* nm;
		size_t nmlen;
		/* chain continues with DNSKEY, continue in FINDKEY */
		vq->state = VAL_FINDKEY_STATE;

		/* strip off the DLV suffix from the name; could result in . */
		log_assert(dname_subdomain_c(vq->ds_rrset->rk.dname,
			qstate->env->anchors->dlv_anchor->name));
		nmlen = vq->ds_rrset->rk.dname_len -
			qstate->env->anchors->dlv_anchor->namelen + 1;
		nm = regional_alloc_init(qstate->region, 
			vq->ds_rrset->rk.dname, nmlen);
		if(!nm) {
			log_err("Out of memory in DLVLook");
			return val_error(qstate, id);
		}
		nm[nmlen-1] = 0;

		vq->ds_rrset->rk.dname = nm;
		vq->ds_rrset->rk.dname_len = nmlen;

		/* create a nullentry for the key so the dnskey lookup
		 * can be retried after a validation failure for it */
		vq->key_entry = key_entry_create_null(qstate->region,
			nm, nmlen, vq->qchase.qclass, 0, 0);
		if(!vq->key_entry) {
			log_err("Out of memory in DLVLook");
			return val_error(qstate, id);
		}

		if(!generate_request(qstate, id, vq->ds_rrset->rk.dname, 
			vq->ds_rrset->rk.dname_len, LDNS_RR_TYPE_DNSKEY, 
			vq->qchase.qclass, BIT_CD, &newq, 0)) {
			verbose(VERB_ALGO, "error generating DNSKEY request");
			return val_error(qstate, id);
		}
		return 0;
	} else if(vq->dlv_status == dlv_there_is_no_dlv) {
		/* continue with the insecure result we got */
		vq->state = VAL_FINISHED_STATE;
		return 1;
	} 
	log_assert(vq->dlv_status == dlv_ask_higher);

	/* ask higher, make sure we stay in DLV repo, below dlv_at */
	if(!dname_subdomain_c(vq->dlv_lookup_name,
		qstate->env->anchors->dlv_anchor->name)) {
		/* just like, there is no DLV */
		verbose(VERB_ALGO, "ask above dlv repo");
		vq->state = VAL_FINISHED_STATE;
		return 1;
	}
	if(vq->dlv_insecure_at && !dname_subdomain_c(vq->dlv_lookup_name,
		vq->dlv_insecure_at)) {
		/* already checked a chain lower than dlv_lookup_name */
		verbose(VERB_ALGO, "ask above insecure endpoint");
		log_nametypeclass(VERB_ALGO, "enpt", vq->dlv_insecure_at, 0, 0);
		vq->state = VAL_FINISHED_STATE;
		return 1;
	}

	/* check negative cache before making new request */
	if(val_neg_dlvlookup(ve->neg_cache, vq->dlv_lookup_name,
		vq->dlv_lookup_name_len, vq->qchase.qclass,
		qstate->env->rrset_cache, *qstate->env->now)) {
		/* does not exist, go up one (go higher). */
		dname_remove_label(&vq->dlv_lookup_name, 
			&vq->dlv_lookup_name_len);
		/* limit number of labels, limited number of recursion */
		return processDLVLookup(qstate, vq, ve, id);
	}

	if(!generate_request(qstate, id, vq->dlv_lookup_name,
		vq->dlv_lookup_name_len, LDNS_RR_TYPE_DLV, 
		vq->qchase.qclass, 0, &newq, 0)) {
		return val_error(qstate, id);
	}

	return 0;
}