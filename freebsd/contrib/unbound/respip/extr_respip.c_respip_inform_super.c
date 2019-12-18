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
struct respip_qstate {int /*<<< orphan*/  state; } ;
struct reply_info {int dummy; } ;
struct module_qstate {scalar_t__ return_rcode; TYPE_2__* return_msg; int /*<<< orphan*/  region; TYPE_1__* env; int /*<<< orphan*/  client_info; int /*<<< orphan*/  qinfo; scalar_t__* minfo; } ;
struct TYPE_4__ {struct reply_info* rep; } ;
struct TYPE_3__ {int /*<<< orphan*/  need_to_validate; } ;

/* Variables and functions */
 scalar_t__ LDNS_RCODE_NOERROR ; 
 scalar_t__ LDNS_RCODE_SERVFAIL ; 
 int /*<<< orphan*/  RESPIP_SUBQUERY_FINISHED ; 
 int /*<<< orphan*/  log_assert (int) ; 
 int /*<<< orphan*/  respip_merge_cname (struct reply_info*,int /*<<< orphan*/ *,struct reply_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct reply_info**,int /*<<< orphan*/ ) ; 

void
respip_inform_super(struct module_qstate* qstate, int id,
	struct module_qstate* super)
{
	struct respip_qstate* rq = (struct respip_qstate*)super->minfo[id];
	struct reply_info* new_rep = NULL;

	rq->state = RESPIP_SUBQUERY_FINISHED;

	/* respip subquery should have always been created with a valid reply
	 * in super. */
	log_assert(super->return_msg && super->return_msg->rep);

	/* return_msg can be NULL when, e.g., the sub query resulted in
	 * SERVFAIL, in which case we regard it as a failure of the original
	 * query.  Other checks are probably redundant, but we check them
	 * for safety. */
	if(!qstate->return_msg || !qstate->return_msg->rep ||
		qstate->return_rcode != LDNS_RCODE_NOERROR)
		goto fail;

	if(!respip_merge_cname(super->return_msg->rep, &qstate->qinfo,
		qstate->return_msg->rep, super->client_info,
		super->env->need_to_validate, &new_rep, super->region))
		goto fail;
	super->return_msg->rep = new_rep;
	return;

  fail:
	super->return_rcode = LDNS_RCODE_SERVFAIL;
	super->return_msg = NULL;
	return;
}