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
struct TYPE_5__ {int /*<<< orphan*/  dname; int /*<<< orphan*/  dname_len; } ;
struct ub_packed_rrset_key {TYPE_2__ rk; } ;
struct TYPE_6__ {int /*<<< orphan*/  qname_len; int /*<<< orphan*/  qname; } ;
struct module_qstate {scalar_t__ return_rcode; int /*<<< orphan*/  region; TYPE_1__* return_msg; TYPE_3__ qinfo; scalar_t__* minfo; } ;
struct iter_qstate {int /*<<< orphan*/  dp; int /*<<< orphan*/  qchase; struct ub_packed_rrset_key* pside_glue; int /*<<< orphan*/  num_target_queries; int /*<<< orphan*/  state; } ;
struct delegpt_ns {int lame; int resolved; } ;
struct TYPE_4__ {int /*<<< orphan*/  rep; } ;

/* Variables and functions */
 scalar_t__ LDNS_RCODE_NOERROR ; 
 int /*<<< orphan*/  QUERYTARGETS_STATE ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  delegpt_add_ns (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  delegpt_add_rrset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ub_packed_rrset_key*,int) ; 
 struct delegpt_ns* delegpt_find_ns (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delegpt_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_assert (int) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  log_query_info (int /*<<< orphan*/ ,char*,TYPE_3__*) ; 
 int /*<<< orphan*/  log_rrset_key (int /*<<< orphan*/ ,char*,struct ub_packed_rrset_key*) ; 
 struct ub_packed_rrset_key* reply_find_answer_rrset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
processTargetResponse(struct module_qstate* qstate, int id,
	struct module_qstate* forq)
{
	struct iter_qstate* iq = (struct iter_qstate*)qstate->minfo[id];
	struct iter_qstate* foriq = (struct iter_qstate*)forq->minfo[id];
	struct ub_packed_rrset_key* rrset;
	struct delegpt_ns* dpns;
	log_assert(qstate->return_rcode == LDNS_RCODE_NOERROR);

	foriq->state = QUERYTARGETS_STATE;
	log_query_info(VERB_ALGO, "processTargetResponse", &qstate->qinfo);
	log_query_info(VERB_ALGO, "processTargetResponse super", &forq->qinfo);

	/* Tell the originating event that this target query has finished
	 * (regardless if it succeeded or not). */
	foriq->num_target_queries--;

	/* check to see if parent event is still interested (in orig name).  */
	if(!foriq->dp) {
		verbose(VERB_ALGO, "subq: parent not interested, was reset");
		return; /* not interested anymore */
	}
	dpns = delegpt_find_ns(foriq->dp, qstate->qinfo.qname,
			qstate->qinfo.qname_len);
	if(!dpns) {
		/* If not interested, just stop processing this event */
		verbose(VERB_ALGO, "subq: parent not interested anymore");
		/* could be because parent was jostled out of the cache,
		   and a new identical query arrived, that does not want it*/
		return;
	}

	/* if iq->query_for_pside_glue then add the pside_glue (marked lame) */
	if(iq->pside_glue) {
		/* if the pside_glue is NULL, then it could not be found,
		 * the done_pside is already set when created and a cache
		 * entry created in processFinished so nothing to do here */
		log_rrset_key(VERB_ALGO, "add parentside glue to dp", 
			iq->pside_glue);
		if(!delegpt_add_rrset(foriq->dp, forq->region, 
			iq->pside_glue, 1))
			log_err("out of memory adding pside glue");
	}

	/* This response is relevant to the current query, so we 
	 * add (attempt to add, anyway) this target(s) and reactivate 
	 * the original event. 
	 * NOTE: we could only look for the AnswerRRset if the 
	 * response type was ANSWER. */
	rrset = reply_find_answer_rrset(&iq->qchase, qstate->return_msg->rep);
	if(rrset) {
		/* if CNAMEs have been followed - add new NS to delegpt. */
		/* BTW. RFC 1918 says NS should not have got CNAMEs. Robust. */
		if(!delegpt_find_ns(foriq->dp, rrset->rk.dname, 
			rrset->rk.dname_len)) {
			/* if dpns->lame then set newcname ns lame too */
			if(!delegpt_add_ns(foriq->dp, forq->region, 
				rrset->rk.dname, dpns->lame))
				log_err("out of memory adding cnamed-ns");
		}
		/* if dpns->lame then set the address(es) lame too */
		if(!delegpt_add_rrset(foriq->dp, forq->region, rrset, 
			dpns->lame))
			log_err("out of memory adding targets");
		verbose(VERB_ALGO, "added target response");
		delegpt_log(VERB_ALGO, foriq->dp);
	} else {
		verbose(VERB_ALGO, "iterator TargetResponse failed");
		dpns->resolved = 1; /* fail the target */
	}
}