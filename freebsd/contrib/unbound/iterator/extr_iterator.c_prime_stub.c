#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_5__ {int /*<<< orphan*/  qclass; } ;
struct module_qstate {int /*<<< orphan*/ * ext_state; TYPE_1__ qinfo; TYPE_2__* env; int /*<<< orphan*/  region; scalar_t__* minfo; } ;
struct iter_qstate {int wait_priming_stub; TYPE_3__* dp; int /*<<< orphan*/  dnssec_expected; scalar_t__ num_target_queries; int /*<<< orphan*/  auth_zone_avoid; } ;
struct iter_hints_stub {scalar_t__ noprime; struct delegpt* dp; } ;
struct delegpt {int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; scalar_t__ auth_dp; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* kill_sub ) (struct module_qstate*) ;int /*<<< orphan*/  hints; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RCODE_SERVFAIL ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_NS ; 
 int /*<<< orphan*/  PRIME_RESP_STATE ; 
 int /*<<< orphan*/  QUERYTARGETS_STATE ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  VERB_DETAIL ; 
 void* delegpt_copy (struct delegpt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errinf (struct module_qstate*,char*) ; 
 int /*<<< orphan*/  error_response (struct module_qstate*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fptr_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fptr_whitelist_modenv_kill_sub (int /*<<< orphan*/  (*) (struct module_qstate*)) ; 
 int /*<<< orphan*/  generate_sub_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct module_qstate*,int,struct iter_qstate*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct module_qstate**,int /*<<< orphan*/ ) ; 
 struct iter_hints_stub* hints_lookup_stub (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  iter_indicates_dnssec (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  log_nametypeclass (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_wait_subquery ; 
 scalar_t__ query_dname_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct module_qstate*) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
prime_stub(struct module_qstate* qstate, struct iter_qstate* iq, int id,
	uint8_t* qname, uint16_t qclass)
{
	/* Lookup the stub hint. This will return null if the stub doesn't 
	 * need to be re-primed. */
	struct iter_hints_stub* stub;
	struct delegpt* stub_dp;
	struct module_qstate* subq;

	if(!qname) return 0;
	stub = hints_lookup_stub(qstate->env->hints, qname, qclass, iq->dp);
	/* The stub (if there is one) does not need priming. */
	if(!stub)
		return 0;
	stub_dp = stub->dp;
	/* if we have an auth_zone dp, and stub is equal, don't prime stub
	 * yet, unless we want to fallback and avoid the auth_zone */
	if(!iq->auth_zone_avoid && iq->dp && iq->dp->auth_dp && 
		query_dname_compare(iq->dp->name, stub_dp->name) == 0)
		return 0;

	/* is it a noprime stub (always use) */
	if(stub->noprime) {
		int r = 0;
		if(iq->dp == NULL) r = 2;
		/* copy the dp out of the fixed hints structure, so that
		 * it can be changed when servicing this query */
		iq->dp = delegpt_copy(stub_dp, qstate->region);
		if(!iq->dp) {
			log_err("out of memory priming stub");
			errinf(qstate, "malloc failure, priming stub");
			(void)error_response(qstate, id, LDNS_RCODE_SERVFAIL);
			return 1; /* return 1 to make module stop, with error */
		}
		log_nametypeclass(VERB_DETAIL, "use stub", stub_dp->name, 
			LDNS_RR_TYPE_NS, qclass);
		return r;
	}

	/* Otherwise, we need to (re)prime the stub. */
	log_nametypeclass(VERB_DETAIL, "priming stub", stub_dp->name, 
		LDNS_RR_TYPE_NS, qclass);

	/* Stub priming events start at the QUERYTARGETS state to avoid the
	 * redundant INIT state processing. */
	if(!generate_sub_request(stub_dp->name, stub_dp->namelen, 
		LDNS_RR_TYPE_NS, qclass, qstate, id, iq,
		QUERYTARGETS_STATE, PRIME_RESP_STATE, &subq, 0)) {
		verbose(VERB_ALGO, "could not prime stub");
		errinf(qstate, "could not generate lookup for stub prime");
		(void)error_response(qstate, id, LDNS_RCODE_SERVFAIL);
		return 1; /* return 1 to make module stop, with error */
	}
	if(subq) {
		struct iter_qstate* subiq = 
			(struct iter_qstate*)subq->minfo[id];

		/* Set the initial delegation point to the hint. */
		/* make copy to avoid use of stub dp by different qs/threads */
		subiq->dp = delegpt_copy(stub_dp, subq->region);
		if(!subiq->dp) {
			log_err("out of memory priming stub, copydp");
			fptr_ok(fptr_whitelist_modenv_kill_sub(
				qstate->env->kill_sub));
			(*qstate->env->kill_sub)(subq);
			errinf(qstate, "malloc failure, in stub prime");
			(void)error_response(qstate, id, LDNS_RCODE_SERVFAIL);
			return 1; /* return 1 to make module stop, with error */
		}
		/* there should not be any target queries -- although there 
		 * wouldn't be anyway, since stub hints never have 
		 * missing targets. */
		subiq->num_target_queries = 0; 
		subiq->wait_priming_stub = 1;
		subiq->dnssec_expected = iter_indicates_dnssec(
			qstate->env, subiq->dp, NULL, subq->qinfo.qclass);
	}
	
	/* this module stops, our submodule starts, and does the query. */
	qstate->ext_state[id] = module_wait_subquery;
	return 1;
}