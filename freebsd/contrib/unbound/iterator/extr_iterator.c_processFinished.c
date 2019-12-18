#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct module_qstate {int query_flags; TYPE_4__* return_msg; int /*<<< orphan*/  return_rcode; int /*<<< orphan*/  region; int /*<<< orphan*/  prefetch_leeway; int /*<<< orphan*/  qinfo; int /*<<< orphan*/  env; int /*<<< orphan*/  no_cache_store; int /*<<< orphan*/ * ext_state; } ;
struct iter_qstate {TYPE_4__* response; TYPE_2__* dp; scalar_t__ ns_prepend_list; scalar_t__ an_prepend_list; TYPE_1__* deleg_msg; int /*<<< orphan*/  pside_glue; scalar_t__ query_for_pside_glue; } ;
struct TYPE_9__ {TYPE_3__* rep; int /*<<< orphan*/  qinfo; } ;
struct TYPE_8__ {int /*<<< orphan*/  security; int /*<<< orphan*/  flags; } ;
struct TYPE_7__ {scalar_t__ has_parent_side_NS; } ;
struct TYPE_6__ {TYPE_3__* rep; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_AA ; 
 int /*<<< orphan*/  BIT_QR ; 
 int /*<<< orphan*/  BIT_RA ; 
 int BIT_RD ; 
 int /*<<< orphan*/  LDNS_RCODE_NOERROR ; 
 int /*<<< orphan*/  LDNS_RCODE_SERVFAIL ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  VERB_QUERY ; 
 int /*<<< orphan*/  errinf (struct module_qstate*,char*) ; 
 int error_response (struct module_qstate*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iter_dns_store (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iter_prepend (struct iter_qstate*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iter_store_parentside_neg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  log_query_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_finished ; 
 int /*<<< orphan*/  sec_status_unchecked ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
processFinished(struct module_qstate* qstate, struct iter_qstate* iq,
	int id)
{
	log_query_info(VERB_QUERY, "finishing processing for", 
		&qstate->qinfo);

	/* store negative cache element for parent side glue. */
	if(!qstate->no_cache_store && iq->query_for_pside_glue
		&& !iq->pside_glue)
			iter_store_parentside_neg(qstate->env, &qstate->qinfo,
				iq->deleg_msg?iq->deleg_msg->rep:
				(iq->response?iq->response->rep:NULL));
	if(!iq->response) {
		verbose(VERB_ALGO, "No response is set, servfail");
		errinf(qstate, "(no response found at query finish)");
		return error_response(qstate, id, LDNS_RCODE_SERVFAIL);
	}

	/* Make sure that the RA flag is set (since the presence of 
	 * this module means that recursion is available) */
	iq->response->rep->flags |= BIT_RA;

	/* Clear the AA flag */
	/* FIXME: does this action go here or in some other module? */
	iq->response->rep->flags &= ~BIT_AA;

	/* make sure QR flag is on */
	iq->response->rep->flags |= BIT_QR;

	/* we have finished processing this query */
	qstate->ext_state[id] = module_finished;

	/* TODO:  we are using a private TTL, trim the response. */
	/* if (mPrivateTTL > 0){IterUtils.setPrivateTTL(resp, mPrivateTTL); } */

	/* prepend any items we have accumulated */
	if(iq->an_prepend_list || iq->ns_prepend_list) {
		if(!iter_prepend(iq, iq->response, qstate->region)) {
			log_err("prepend rrsets: out of memory");
			return error_response(qstate, id, LDNS_RCODE_SERVFAIL);
		}
		/* reset the query name back */
		iq->response->qinfo = qstate->qinfo;
		/* the security state depends on the combination */
		iq->response->rep->security = sec_status_unchecked;
		/* store message with the finished prepended items,
		 * but only if we did recursion. The nonrecursion referral
		 * from cache does not need to be stored in the msg cache. */
		if(!qstate->no_cache_store && qstate->query_flags&BIT_RD) {
			iter_dns_store(qstate->env, &qstate->qinfo, 
				iq->response->rep, 0, qstate->prefetch_leeway,
				iq->dp&&iq->dp->has_parent_side_NS,
				qstate->region, qstate->query_flags);
		}
	}
	qstate->return_rcode = LDNS_RCODE_NOERROR;
	qstate->return_msg = iq->response;
	return 0;
}