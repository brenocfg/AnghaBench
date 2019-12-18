#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ qtype; } ;
struct module_qstate {int query_flags; TYPE_1__* return_msg; TYPE_2__ qinfo; int /*<<< orphan*/  env; scalar_t__* minfo; } ;
struct dns64_qstate {scalar_t__ state; int /*<<< orphan*/  started_no_cache_store; } ;
typedef  enum module_ext_state { ____Placeholder_module_ext_state } module_ext_state ;
struct TYPE_4__ {scalar_t__ rep; } ;

/* Variables and functions */
 int BIT_CD ; 
 scalar_t__ DNS64_INTERNAL_QUERY ; 
 scalar_t__ LDNS_RR_TYPE_AAAA ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 scalar_t__ dns64_always_synth_for_qname (struct module_qstate*,int) ; 
 int /*<<< orphan*/  dns_cache_store (int /*<<< orphan*/ ,TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int generate_type_A_query (struct module_qstate*,int) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int module_finished ; 
 scalar_t__ reply_find_answer_rrset (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static enum module_ext_state
handle_event_moddone(struct module_qstate* qstate, int id)
{
	struct dns64_qstate* iq = (struct dns64_qstate*)qstate->minfo[id];
    /*
     * In many cases we have nothing special to do. From most to least common:
     *
     *   - An internal query.
     *   - A query for a record type other than AAAA.
     *   - CD FLAG was set on querier
     *   - An AAAA query for which an error was returned.(qstate.return_rcode)
     *     -> treated as servfail thus synthesize (sec 5.1.3 6147), thus
     *        synthesize in (sec 5.1.2 of RFC6147).
     *   - A successful AAAA query with an answer.
     */
	if((!iq || iq->state != DNS64_INTERNAL_QUERY)
            && qstate->qinfo.qtype == LDNS_RR_TYPE_AAAA
	    && !(qstate->query_flags & BIT_CD)
	    && !(qstate->return_msg &&
		    qstate->return_msg->rep &&
		    reply_find_answer_rrset(&qstate->qinfo,
			    qstate->return_msg->rep)))
		/* not internal, type AAAA, not CD, and no answer RRset,
		 * So, this is a AAAA noerror/nodata answer */
		return generate_type_A_query(qstate, id);

	if((!iq || iq->state != DNS64_INTERNAL_QUERY)
	    && qstate->qinfo.qtype == LDNS_RR_TYPE_AAAA
	    && !(qstate->query_flags & BIT_CD)
	    && dns64_always_synth_for_qname(qstate, id)) {
		/* if it is not internal, AAAA, not CD and listed domain,
		 * generate from A record and ignore AAAA */
		verbose(VERB_ALGO, "dns64: ignore-aaaa and synthesize anyway");
		return generate_type_A_query(qstate, id);
	}

	/* Store the response in cache. */
	if ( (!iq || !iq->started_no_cache_store) &&
		qstate->return_msg && qstate->return_msg->rep &&
		!dns_cache_store(qstate->env, &qstate->qinfo, qstate->return_msg->rep,
		0, 0, 0, NULL, qstate->query_flags))
		log_err("out of memory");

	/* do nothing */
	return module_finished;
}