#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct module_qstate {int query_flags; TYPE_3__* env; int /*<<< orphan*/  region; scalar_t__ reply_origin; int /*<<< orphan*/  qinfo; } ;
struct TYPE_5__ {int /*<<< orphan*/  qclass; } ;
struct iter_qstate {int chase_flags; scalar_t__ dnssec_expected; TYPE_4__* response; TYPE_4__* deleg_msg; TYPE_1__ qchase; int /*<<< orphan*/  dp; } ;
struct TYPE_8__ {int /*<<< orphan*/  rep; int /*<<< orphan*/  qinfo; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* detach_subs ) (struct module_qstate*) ;TYPE_2__* cfg; } ;
struct TYPE_6__ {scalar_t__ prefetch_key; } ;

/* Variables and functions */
 int BIT_CD ; 
 int BIT_RD ; 
 int /*<<< orphan*/  QUERYTARGETS_STATE ; 
 scalar_t__ VERB_ALGO ; 
 int /*<<< orphan*/  VERB_QUERY ; 
 int final_state (struct iter_qstate*) ; 
 int /*<<< orphan*/  fptr_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fptr_whitelist_modenv_detach_subs (int /*<<< orphan*/  (*) (struct module_qstate*)) ; 
 int /*<<< orphan*/  generate_dnskey_prefetch (struct module_qstate*,struct iter_qstate*,int) ; 
 scalar_t__ iter_indicates_dnssec (TYPE_3__*,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_dns_msg (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_query_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int next_state (struct iter_qstate*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_list_insert (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct module_qstate*) ; 
 scalar_t__ verbosity ; 

__attribute__((used)) static int
processInitRequest3(struct module_qstate* qstate, struct iter_qstate* iq, 
	int id)
{
	log_query_info(VERB_QUERY, "resolving (init part 3): ", 
		&qstate->qinfo);
	/* if the cache reply dp equals a validation anchor or msg has DS,
	 * then DNSSEC RRSIGs are expected in the reply */
	iq->dnssec_expected = iter_indicates_dnssec(qstate->env, iq->dp, 
		iq->deleg_msg, iq->qchase.qclass);

	/* If the RD flag wasn't set, then we just finish with the 
	 * cached referral as the response. */
	if(!(qstate->query_flags & BIT_RD) && iq->deleg_msg) {
		iq->response = iq->deleg_msg;
		if(verbosity >= VERB_ALGO && iq->response)
			log_dns_msg("no RD requested, using delegation msg", 
				&iq->response->qinfo, iq->response->rep);
		if(qstate->reply_origin)
			sock_list_insert(&qstate->reply_origin, NULL, 0, qstate->region);
		return final_state(iq);
	}
	/* After this point, unset the RD flag -- this query is going to 
	 * be sent to an auth. server. */
	iq->chase_flags &= ~BIT_RD;

	/* if dnssec expected, fetch key for the trust-anchor or cached-DS */
	if(iq->dnssec_expected && qstate->env->cfg->prefetch_key &&
		!(qstate->query_flags&BIT_CD)) {
		generate_dnskey_prefetch(qstate, iq, id);
		fptr_ok(fptr_whitelist_modenv_detach_subs(
			qstate->env->detach_subs));
		(*qstate->env->detach_subs)(qstate);
	}

	/* Jump to the next state. */
	return next_state(iq, QUERYTARGETS_STATE);
}