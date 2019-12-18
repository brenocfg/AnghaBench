#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct query_info {int /*<<< orphan*/  qtype; } ;
struct module_qstate {int curmod; int /*<<< orphan*/ ** minfo; int /*<<< orphan*/ * ext_state; int /*<<< orphan*/  query_flags; TYPE_1__* env; struct query_info qinfo; } ;
typedef  enum module_ext_state { ____Placeholder_module_ext_state } module_ext_state ;
struct TYPE_2__ {int /*<<< orphan*/  (* attach_sub ) (struct module_qstate*,struct query_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct module_qstate**) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_TYPE_A ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  fptr_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fptr_whitelist_modenv_attach_sub (int /*<<< orphan*/  (*) (struct module_qstate*,struct query_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct module_qstate**)) ; 
 int module_error ; 
 int /*<<< orphan*/  module_state_initial ; 
 int module_wait_subquery ; 
 int /*<<< orphan*/  stub1 (struct module_qstate*,struct query_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct module_qstate**) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static enum module_ext_state
generate_type_A_query(struct module_qstate* qstate, int id)
{
	struct module_qstate* subq = NULL;
	struct query_info qinfo;

	verbose(VERB_ALGO, "dns64: query A record");

	/* Create a new query info. */
	qinfo = qstate->qinfo;
	qinfo.qtype = LDNS_RR_TYPE_A;

	/* Start the sub-query. */
	fptr_ok(fptr_whitelist_modenv_attach_sub(qstate->env->attach_sub));
	if(!(*qstate->env->attach_sub)(qstate, &qinfo, qstate->query_flags, 0,
				       0, &subq))
	{
		verbose(VERB_ALGO, "dns64: sub-query creation failed");
		return module_error;
	}
	if (subq) {
		subq->curmod = id;
		subq->ext_state[id] = module_state_initial;
		subq->minfo[id] = NULL;
	}

	return module_wait_subquery;
}