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
struct TYPE_9__ {scalar_t__ qname; scalar_t__ qclass; } ;
struct val_qstate {int /*<<< orphan*/  orig_msg; TYPE_4__ qchase; } ;
struct val_env {int dummy; } ;
struct outbound_entry {int dummy; } ;
struct module_qstate {void** ext_state; TYPE_3__* return_msg; TYPE_4__ qinfo; int /*<<< orphan*/  return_rcode; scalar_t__* minfo; TYPE_1__* env; } ;
typedef  enum module_ev { ____Placeholder_module_ev } module_ev ;
struct TYPE_8__ {TYPE_2__* rep; } ;
struct TYPE_7__ {int /*<<< orphan*/  security; } ;
struct TYPE_6__ {scalar_t__* modinfo; } ;

/* Variables and functions */
 scalar_t__ LDNS_RR_CLASS_ANY ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  VERB_QUERY ; 
 scalar_t__ already_validated (TYPE_3__*) ; 
 int /*<<< orphan*/  log_err (char*,...) ; 
 int /*<<< orphan*/  log_query_info (int /*<<< orphan*/ ,char*,TYPE_4__*) ; 
 void* module_error ; 
 int module_event_moddone ; 
 int module_event_new ; 
 int module_event_pass ; 
 void* module_finished ; 
 void* module_wait_module ; 
 int /*<<< orphan*/  needs_validation (struct module_qstate*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  sec_status_bogus ; 
 int /*<<< orphan*/  sec_status_indeterminate ; 
 int /*<<< orphan*/  strextstate (void*) ; 
 int /*<<< orphan*/  strmodulevent (int) ; 
 int /*<<< orphan*/  val_handle (struct module_qstate*,struct val_qstate*,struct val_env*,int) ; 
 struct val_qstate* val_new (struct module_qstate*,int) ; 
 int /*<<< orphan*/  val_new_getmsg (struct module_qstate*,struct val_qstate*) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,...) ; 

void
val_operate(struct module_qstate* qstate, enum module_ev event, int id,
        struct outbound_entry* outbound)
{
	struct val_env* ve = (struct val_env*)qstate->env->modinfo[id];
	struct val_qstate* vq = (struct val_qstate*)qstate->minfo[id];
	verbose(VERB_QUERY, "validator[module %d] operate: extstate:%s "
		"event:%s", id, strextstate(qstate->ext_state[id]), 
		strmodulevent(event));
	log_query_info(VERB_QUERY, "validator operate: query",
		&qstate->qinfo);
	if(vq && qstate->qinfo.qname != vq->qchase.qname) 
		log_query_info(VERB_QUERY, "validator operate: chased to",
		&vq->qchase);
	(void)outbound;
	if(event == module_event_new || 
		(event == module_event_pass && vq == NULL)) {

		/* pass request to next module, to get it */
		verbose(VERB_ALGO, "validator: pass to next module");
		qstate->ext_state[id] = module_wait_module;
		return;
	}
	if(event == module_event_moddone) {
		/* check if validation is needed */
		verbose(VERB_ALGO, "validator: nextmodule returned");

		if(!needs_validation(qstate, qstate->return_rcode, 
			qstate->return_msg)) {
			/* no need to validate this */
			if(qstate->return_msg)
				qstate->return_msg->rep->security =
					sec_status_indeterminate;
			qstate->ext_state[id] = module_finished;
			return;
		}
		if(already_validated(qstate->return_msg)) {
			qstate->ext_state[id] = module_finished;
			return;
		}
		/* qclass ANY should have validation result from spawned 
		 * queries. If we get here, it is bogus or an internal error */
		if(qstate->qinfo.qclass == LDNS_RR_CLASS_ANY) {
			verbose(VERB_ALGO, "cannot validate classANY: bogus");
			if(qstate->return_msg)
				qstate->return_msg->rep->security =
					sec_status_bogus;
			qstate->ext_state[id] = module_finished;
			return;
		}
		/* create state to start validation */
		qstate->ext_state[id] = module_error; /* override this */
		if(!vq) {
			vq = val_new(qstate, id);
			if(!vq) {
				log_err("validator: malloc failure");
				qstate->ext_state[id] = module_error;
				return;
			}
		} else if(!vq->orig_msg) {
			if(!val_new_getmsg(qstate, vq)) {
				log_err("validator: malloc failure");
				qstate->ext_state[id] = module_error;
				return;
			}
		}
		val_handle(qstate, vq, ve, id);
		return;
	}
	if(event == module_event_pass) {
		qstate->ext_state[id] = module_error; /* override this */
		/* continue processing, since val_env exists */
		val_handle(qstate, vq, ve, id);
		return;
	}
	log_err("validator: bad event %s", strmodulevent(event));
	qstate->ext_state[id] = module_error;
	return;
}