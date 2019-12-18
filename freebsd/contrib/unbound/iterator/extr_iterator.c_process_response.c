#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct outbound_entry {int dummy; } ;
struct msg_parse {int /*<<< orphan*/  flags; scalar_t__ opt_list; } ;
struct module_qstate {TYPE_4__* env; TYPE_3__* reply; int /*<<< orphan*/  qinfo; int /*<<< orphan*/  region; int /*<<< orphan*/  edns_opts_back_in; } ;
struct iter_qstate {int sent_count; int caps_fallback; int caps_server; scalar_t__ caps_minimisation_state; scalar_t__ minimisation_state; int /*<<< orphan*/  outlist; int /*<<< orphan*/  num_current_queries; void* state; int /*<<< orphan*/ * caps_reply; TYPE_7__* response; TYPE_7__* caps_response; TYPE_5__* dp; int /*<<< orphan*/  qinfo_out; } ;
struct iter_env {int dummy; } ;
struct edns_data {int /*<<< orphan*/  flags; scalar_t__ opt_list; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;
typedef  enum module_ev { ____Placeholder_module_ev } module_ev ;
typedef  int /*<<< orphan*/  edns ;
struct TYPE_13__ {int /*<<< orphan*/ * rep; int /*<<< orphan*/  qinfo; } ;
struct TYPE_12__ {int /*<<< orphan*/  name; } ;
struct TYPE_11__ {int /*<<< orphan*/  scratch; TYPE_1__* cfg; } ;
struct TYPE_10__ {int /*<<< orphan*/  addrlen; int /*<<< orphan*/  addr; TYPE_2__* c; } ;
struct TYPE_9__ {int /*<<< orphan*/ * buffer; } ;
struct TYPE_8__ {scalar_t__ qname_minimisation; scalar_t__ use_caps_bits_for_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_CD ; 
 scalar_t__ DONOT_MINIMISE_STATE ; 
 scalar_t__ LDNS_RCODE_NOERROR ; 
 int /*<<< orphan*/  LDNS_RCODE_SERVFAIL ; 
 void* QUERYTARGETS_STATE ; 
 void* QUERY_RESP_STATE ; 
 scalar_t__ SKIP_MINIMISE_STATE ; 
 scalar_t__ VERB_ALGO ; 
 scalar_t__ VERB_DETAIL ; 
 scalar_t__ caps_failed_rcode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  caps_strip_reply (int /*<<< orphan*/ *) ; 
 TYPE_7__* dns_alloc_msg (int /*<<< orphan*/ *,struct msg_parse*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edns_opt_copy_region (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errinf (struct module_qstate*,char*) ; 
 int /*<<< orphan*/  error_response (struct module_qstate*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inplace_cb_edns_back_parsed_call (TYPE_4__*,struct module_qstate*) ; 
 int /*<<< orphan*/  is_caps_whitelisted (struct iter_env*,struct iter_qstate*) ; 
 int /*<<< orphan*/  iter_dec_attempts (TYPE_5__*,int) ; 
 int /*<<< orphan*/  iter_handle (struct module_qstate*,struct iter_qstate*,struct iter_env*,int) ; 
 int /*<<< orphan*/  log_dns_msg (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  log_name_addr (scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_query_info (scalar_t__,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct msg_parse*,int /*<<< orphan*/ ,int) ; 
 int module_event_capsfail ; 
 int module_event_error ; 
 int module_event_noreply ; 
 int module_event_reply ; 
 int /*<<< orphan*/  outbound_list_remove (int /*<<< orphan*/ *,struct outbound_entry*) ; 
 scalar_t__ parse_extract_edns (struct msg_parse*,struct msg_parse*,int /*<<< orphan*/ ) ; 
 scalar_t__ parse_packet (int /*<<< orphan*/ *,struct msg_parse*,int /*<<< orphan*/ ) ; 
 scalar_t__ regional_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reply_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scrub_message (int /*<<< orphan*/ *,struct msg_parse*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,struct iter_env*) ; 
 int /*<<< orphan*/  sldns_buffer_set_position (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose (scalar_t__,char*) ; 
 scalar_t__ verbosity ; 

__attribute__((used)) static void
process_response(struct module_qstate* qstate, struct iter_qstate* iq, 
	struct iter_env* ie, int id, struct outbound_entry* outbound,
	enum module_ev event)
{
	struct msg_parse* prs;
	struct edns_data edns;
	sldns_buffer* pkt;

	verbose(VERB_ALGO, "process_response: new external response event");
	iq->response = NULL;
	iq->state = QUERY_RESP_STATE;
	if(event == module_event_noreply || event == module_event_error) {
		if(event == module_event_noreply && iq->sent_count >= 3 &&
			qstate->env->cfg->use_caps_bits_for_id &&
			!iq->caps_fallback && !is_caps_whitelisted(ie, iq)) {
			/* start fallback */
			iq->caps_fallback = 1;
			iq->caps_server = 0;
			iq->caps_reply = NULL;
			iq->caps_response = NULL;
			iq->caps_minimisation_state = DONOT_MINIMISE_STATE;
			iq->state = QUERYTARGETS_STATE;
			iq->num_current_queries--;
			/* need fresh attempts for the 0x20 fallback, if
			 * that was the cause for the failure */
			iter_dec_attempts(iq->dp, 3);
			verbose(VERB_DETAIL, "Capsforid: timeouts, starting fallback");
			goto handle_it;
		}
		goto handle_it;
	}
	if( (event != module_event_reply && event != module_event_capsfail)
		|| !qstate->reply) {
		log_err("Bad event combined with response");
		outbound_list_remove(&iq->outlist, outbound);
		errinf(qstate, "module iterator received wrong internal event with a response message");
		(void)error_response(qstate, id, LDNS_RCODE_SERVFAIL);
		return;
	}

	/* parse message */
	prs = (struct msg_parse*)regional_alloc(qstate->env->scratch, 
		sizeof(struct msg_parse));
	if(!prs) {
		log_err("out of memory on incoming message");
		/* like packet got dropped */
		goto handle_it;
	}
	memset(prs, 0, sizeof(*prs));
	memset(&edns, 0, sizeof(edns));
	pkt = qstate->reply->c->buffer;
	sldns_buffer_set_position(pkt, 0);
	if(parse_packet(pkt, prs, qstate->env->scratch) != LDNS_RCODE_NOERROR) {
		verbose(VERB_ALGO, "parse error on reply packet");
		goto handle_it;
	}
	/* edns is not examined, but removed from message to help cache */
	if(parse_extract_edns(prs, &edns, qstate->env->scratch) !=
		LDNS_RCODE_NOERROR)
		goto handle_it;

	/* Copy the edns options we may got from the back end */
	if(edns.opt_list) {
		qstate->edns_opts_back_in = edns_opt_copy_region(edns.opt_list,
			qstate->region);
		if(!qstate->edns_opts_back_in) {
			log_err("out of memory on incoming message");
			/* like packet got dropped */
			goto handle_it;
		}
		if(!inplace_cb_edns_back_parsed_call(qstate->env, qstate)) {
			log_err("unable to call edns_back_parsed callback");
			goto handle_it;
		}
	}

	/* remove CD-bit, we asked for in case we handle validation ourself */
	prs->flags &= ~BIT_CD;

	/* normalize and sanitize: easy to delete items from linked lists */
	if(!scrub_message(pkt, prs, &iq->qinfo_out, iq->dp->name, 
		qstate->env->scratch, qstate->env, ie)) {
		/* if 0x20 enabled, start fallback, but we have no message */
		if(event == module_event_capsfail && !iq->caps_fallback) {
			iq->caps_fallback = 1;
			iq->caps_server = 0;
			iq->caps_reply = NULL;
			iq->caps_response = NULL;
			iq->caps_minimisation_state = DONOT_MINIMISE_STATE;
			iq->state = QUERYTARGETS_STATE;
			iq->num_current_queries--;
			verbose(VERB_DETAIL, "Capsforid: scrub failed, starting fallback with no response");
		}
		goto handle_it;
	}

	/* allocate response dns_msg in region */
	iq->response = dns_alloc_msg(pkt, prs, qstate->region);
	if(!iq->response)
		goto handle_it;
	log_query_info(VERB_DETAIL, "response for", &qstate->qinfo);
	log_name_addr(VERB_DETAIL, "reply from", iq->dp->name, 
		&qstate->reply->addr, qstate->reply->addrlen);
	if(verbosity >= VERB_ALGO)
		log_dns_msg("incoming scrubbed packet:", &iq->response->qinfo, 
			iq->response->rep);
	
	if(event == module_event_capsfail || iq->caps_fallback) {
		if(qstate->env->cfg->qname_minimisation &&
			iq->minimisation_state != DONOT_MINIMISE_STATE) {
			/* Skip QNAME minimisation for next query, since that
			 * one has to match the current query. */
			iq->minimisation_state = SKIP_MINIMISE_STATE;
		}
		/* for fallback we care about main answer, not additionals */
		/* removing that makes comparison more likely to succeed */
		caps_strip_reply(iq->response->rep);

		if(iq->caps_fallback &&
			iq->caps_minimisation_state != iq->minimisation_state) {
			/* QNAME minimisation state has changed, restart caps
			 * fallback. */
			iq->caps_fallback = 0;
		}

		if(!iq->caps_fallback) {
			/* start fallback */
			iq->caps_fallback = 1;
			iq->caps_server = 0;
			iq->caps_reply = iq->response->rep;
			iq->caps_response = iq->response;
			iq->caps_minimisation_state = iq->minimisation_state;
			iq->state = QUERYTARGETS_STATE;
			iq->num_current_queries--;
			verbose(VERB_DETAIL, "Capsforid: starting fallback");
			goto handle_it;
		} else {
			/* check if reply is the same, otherwise, fail */
			if(!iq->caps_reply) {
				iq->caps_reply = iq->response->rep;
				iq->caps_response = iq->response;
				iq->caps_server = -1; /*become zero at ++,
				so that we start the full set of trials */
			} else if(caps_failed_rcode(iq->caps_reply) &&
				!caps_failed_rcode(iq->response->rep)) {
				/* prefer to upgrade to non-SERVFAIL */
				iq->caps_reply = iq->response->rep;
				iq->caps_response = iq->response;
			} else if(!caps_failed_rcode(iq->caps_reply) &&
				caps_failed_rcode(iq->response->rep)) {
				/* if we have non-SERVFAIL as answer then 
				 * we can ignore SERVFAILs for the equality
				 * comparison */
				/* no instructions here, skip other else */
			} else if(caps_failed_rcode(iq->caps_reply) &&
				caps_failed_rcode(iq->response->rep)) {
				/* failure is same as other failure in fallbk*/
				/* no instructions here, skip other else */
			} else if(!reply_equal(iq->response->rep, iq->caps_reply,
				qstate->env->scratch)) {
				verbose(VERB_DETAIL, "Capsforid fallback: "
					"getting different replies, failed");
				outbound_list_remove(&iq->outlist, outbound);
				errinf(qstate, "0x20 failed, then got different replies in fallback");
				(void)error_response(qstate, id, 
					LDNS_RCODE_SERVFAIL);
				return;
			}
			/* continue the fallback procedure at next server */
			iq->caps_server++;
			iq->state = QUERYTARGETS_STATE;
			iq->num_current_queries--;
			verbose(VERB_DETAIL, "Capsforid: reply is equal. "
				"go to next fallback");
			goto handle_it;
		}
	}
	iq->caps_fallback = 0; /* if we were in fallback, 0x20 is OK now */

handle_it:
	outbound_list_remove(&iq->outlist, outbound);
	iter_handle(qstate, iq, ie, id);
}