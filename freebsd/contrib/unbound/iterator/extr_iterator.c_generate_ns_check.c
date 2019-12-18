#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ qtype; int /*<<< orphan*/  qname; } ;
struct module_qstate {int query_flags; TYPE_6__* env; int /*<<< orphan*/  region; scalar_t__* minfo; TYPE_1__ qinfo; } ;
struct TYPE_8__ {int /*<<< orphan*/  qclass; } ;
struct iter_qstate {scalar_t__ depth; int refetch_glue; TYPE_3__* dp; TYPE_2__ qchase; } ;
struct iter_env {scalar_t__ max_dependency_depth; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* kill_sub ) (struct module_qstate*) ;scalar_t__* modinfo; } ;
struct TYPE_9__ {int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int BIT_CD ; 
 int BIT_RD ; 
 int /*<<< orphan*/  FINISHED_STATE ; 
 int /*<<< orphan*/  INIT_REQUEST_STATE ; 
 scalar_t__ LDNS_RR_TYPE_DS ; 
 scalar_t__ LDNS_RR_TYPE_NS ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  can_have_last_resort (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* delegpt_copy (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fptr_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fptr_whitelist_modenv_kill_sub (int /*<<< orphan*/  (*) (struct module_qstate*)) ; 
 int /*<<< orphan*/  generate_a_aaaa_check (struct module_qstate*,struct iter_qstate*,int) ; 
 int /*<<< orphan*/  generate_sub_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,struct module_qstate*,int,struct iter_qstate*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct module_qstate**,int) ; 
 int /*<<< orphan*/  log_assert (TYPE_3__*) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  log_nametypeclass (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ query_dname_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct module_qstate*) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
generate_ns_check(struct module_qstate* qstate, struct iter_qstate* iq, int id)
{
	struct iter_env* ie = (struct iter_env*)qstate->env->modinfo[id];
	struct module_qstate* subq;
	log_assert(iq->dp);

	if(iq->depth == ie->max_dependency_depth)
		return;
	if(!can_have_last_resort(qstate->env, iq->dp->name, iq->dp->namelen,
		iq->qchase.qclass, NULL))
		return;
	/* is this query the same as the nscheck? */
	if(qstate->qinfo.qtype == LDNS_RR_TYPE_NS &&
		query_dname_compare(iq->dp->name, qstate->qinfo.qname)==0 &&
		(qstate->query_flags&BIT_RD) && !(qstate->query_flags&BIT_CD)){
		/* spawn off A, AAAA queries for in-zone glue to check */
		generate_a_aaaa_check(qstate, iq, id);
		return;
	}
	/* no need to get the NS record for DS, it is above the zonecut */
	if(qstate->qinfo.qtype == LDNS_RR_TYPE_DS)
		return;

	log_nametypeclass(VERB_ALGO, "schedule ns fetch", 
		iq->dp->name, LDNS_RR_TYPE_NS, iq->qchase.qclass);
	if(!generate_sub_request(iq->dp->name, iq->dp->namelen, 
		LDNS_RR_TYPE_NS, iq->qchase.qclass, qstate, id, iq,
		INIT_REQUEST_STATE, FINISHED_STATE, &subq, 1)) {
		verbose(VERB_ALGO, "could not generate ns check");
		return;
	}
	if(subq) {
		struct iter_qstate* subiq = 
			(struct iter_qstate*)subq->minfo[id];

		/* make copy to avoid use of stub dp by different qs/threads */
		/* refetch glue to start higher up the tree */
		subiq->refetch_glue = 1;
		subiq->dp = delegpt_copy(iq->dp, subq->region);
		if(!subiq->dp) {
			log_err("out of memory generating ns check, copydp");
			fptr_ok(fptr_whitelist_modenv_kill_sub(
				qstate->env->kill_sub));
			(*qstate->env->kill_sub)(subq);
			return;
		}
	}
}