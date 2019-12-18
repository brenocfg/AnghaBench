#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  qclass; } ;
struct module_qstate {int /*<<< orphan*/ * ext_state; TYPE_1__ qinfo; TYPE_3__* env; int /*<<< orphan*/  region; scalar_t__* minfo; } ;
struct iter_qstate {int /*<<< orphan*/  dp; int /*<<< orphan*/  dnssec_expected; scalar_t__ num_target_queries; } ;
struct delegpt {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* kill_sub ) (struct module_qstate*) ;int /*<<< orphan*/  hints; } ;
struct TYPE_5__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_TYPE_NS ; 
 int /*<<< orphan*/  PRIME_RESP_STATE ; 
 int /*<<< orphan*/  QUERYTARGETS_STATE ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  VERB_DETAIL ; 
 int /*<<< orphan*/  delegpt_copy (struct delegpt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fptr_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fptr_whitelist_modenv_kill_sub (int /*<<< orphan*/  (*) (struct module_qstate*)) ; 
 int /*<<< orphan*/  generate_sub_request (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,scalar_t__,struct module_qstate*,int,struct iter_qstate*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct module_qstate**,int /*<<< orphan*/ ) ; 
 struct delegpt* hints_lookup_root (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  iter_indicates_dnssec (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  module_wait_subquery ; 
 TYPE_2__* sldns_lookup_by_id (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sldns_rr_classes ; 
 int /*<<< orphan*/  stub1 (struct module_qstate*) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int
prime_root(struct module_qstate* qstate, struct iter_qstate* iq, int id,
	uint16_t qclass)
{
	struct delegpt* dp;
	struct module_qstate* subq;
	verbose(VERB_DETAIL, "priming . %s NS", 
		sldns_lookup_by_id(sldns_rr_classes, (int)qclass)?
		sldns_lookup_by_id(sldns_rr_classes, (int)qclass)->name:"??");
	dp = hints_lookup_root(qstate->env->hints, qclass);
	if(!dp) {
		verbose(VERB_ALGO, "Cannot prime due to lack of hints");
		return 0;
	}
	/* Priming requests start at the QUERYTARGETS state, skipping 
	 * the normal INIT state logic (which would cause an infloop). */
	if(!generate_sub_request((uint8_t*)"\000", 1, LDNS_RR_TYPE_NS, 
		qclass, qstate, id, iq, QUERYTARGETS_STATE, PRIME_RESP_STATE,
		&subq, 0)) {
		verbose(VERB_ALGO, "could not prime root");
		return 0;
	}
	if(subq) {
		struct iter_qstate* subiq = 
			(struct iter_qstate*)subq->minfo[id];
		/* Set the initial delegation point to the hint.
		 * copy dp, it is now part of the root prime query. 
		 * dp was part of in the fixed hints structure. */
		subiq->dp = delegpt_copy(dp, subq->region);
		if(!subiq->dp) {
			log_err("out of memory priming root, copydp");
			fptr_ok(fptr_whitelist_modenv_kill_sub(
				qstate->env->kill_sub));
			(*qstate->env->kill_sub)(subq);
			return 0;
		}
		/* there should not be any target queries. */
		subiq->num_target_queries = 0; 
		subiq->dnssec_expected = iter_indicates_dnssec(
			qstate->env, subiq->dp, NULL, subq->qinfo.qclass);
	}
	
	/* this module stops, our submodule starts, and does the query. */
	qstate->ext_state[id] = module_wait_subquery;
	return 1;
}