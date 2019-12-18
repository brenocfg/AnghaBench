#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_60__   TYPE_9__ ;
typedef  struct TYPE_59__   TYPE_8__ ;
typedef  struct TYPE_58__   TYPE_7__ ;
typedef  struct TYPE_57__   TYPE_6__ ;
typedef  struct TYPE_56__   TYPE_5__ ;
typedef  struct TYPE_55__   TYPE_4__ ;
typedef  struct TYPE_54__   TYPE_3__ ;
typedef  struct TYPE_53__   TYPE_39__ ;
typedef  struct TYPE_52__   TYPE_31__ ;
typedef  struct TYPE_51__   TYPE_2__ ;
typedef  struct TYPE_50__   TYPE_25__ ;
typedef  struct TYPE_49__   TYPE_1__ ;
typedef  struct TYPE_48__   TYPE_16__ ;
typedef  struct TYPE_47__   TYPE_13__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_49__ {int /*<<< orphan*/ * dname; } ;
struct ub_packed_rrset_key {TYPE_1__ rk; } ;
struct TYPE_56__ {scalar_t__ qtype; int /*<<< orphan*/  qclass; } ;
struct module_qstate {int query_flags; TYPE_5__ qinfo; TYPE_16__* env; TYPE_3__* reply; int /*<<< orphan*/ * region; int /*<<< orphan*/  reply_origin; int /*<<< orphan*/  prefetch_leeway; int /*<<< orphan*/  no_cache_store; } ;
struct TYPE_52__ {size_t qname_len; int /*<<< orphan*/  qtype; int /*<<< orphan*/ * qname; int /*<<< orphan*/  qclass; } ;
struct TYPE_59__ {int /*<<< orphan*/  qname; } ;
struct iter_qstate {scalar_t__ minimisation_state; int chase_flags; scalar_t__ sent_count; int auth_zone_avoid; TYPE_9__* dp; scalar_t__ auth_zone_response; TYPE_31__ qchase; scalar_t__ num_target_queries; scalar_t__ num_current_queries; int /*<<< orphan*/  outlist; int /*<<< orphan*/  query_restart_count; int /*<<< orphan*/ * dsns_point; TYPE_7__* deleg_msg; TYPE_7__* response; scalar_t__ dnssec_expected; int /*<<< orphan*/  referral_count; TYPE_25__* store_parent_NS; scalar_t__ pside_glue; scalar_t__ query_for_pside_glue; int /*<<< orphan*/  ratelimit_ok; TYPE_8__ qinfo_out; scalar_t__ dnssec_lame_query; scalar_t__ chase_to_rd; int /*<<< orphan*/  minimise_timeout_count; } ;
struct delegpt_addr {int dnsseclame; } ;
typedef  enum response_type { ____Placeholder_response_type } response_type ;
struct TYPE_60__ {scalar_t__ auth_dp; int /*<<< orphan*/ * name; int /*<<< orphan*/  namelen; scalar_t__ has_parent_side_NS; } ;
struct TYPE_47__ {int /*<<< orphan*/  qclass; int /*<<< orphan*/  qtype; int /*<<< orphan*/  qname_len; int /*<<< orphan*/  qname; } ;
struct TYPE_58__ {TYPE_6__* rep; TYPE_13__ qinfo; } ;
struct TYPE_57__ {int an_numrrsets; int ns_numrrsets; int /*<<< orphan*/  flags; TYPE_39__** rrsets; } ;
struct TYPE_55__ {scalar_t__ qname_minimisation_strict; scalar_t__ qname_minimisation; scalar_t__ harden_referral_path; scalar_t__ prefetch_key; scalar_t__ harden_below_nxdomain; int /*<<< orphan*/  disable_dnssec_lame_check; } ;
struct TYPE_54__ {int /*<<< orphan*/  addrlen; int /*<<< orphan*/  addr; } ;
struct TYPE_51__ {int /*<<< orphan*/ * dname; int /*<<< orphan*/  type; } ;
struct TYPE_53__ {TYPE_2__ rk; } ;
struct TYPE_50__ {int /*<<< orphan*/  name; } ;
struct TYPE_48__ {int /*<<< orphan*/  auth_zones; TYPE_4__* cfg; int /*<<< orphan*/ * now; int /*<<< orphan*/  infra_cache; int /*<<< orphan*/  (* detach_subs ) (struct module_qstate*) ;scalar_t__ neg_cache; } ;

/* Variables and functions */
 int BIT_CD ; 
 int BIT_RD ; 
 scalar_t__ DNSSEC_LAME_DETECT_COUNT ; 
 scalar_t__ DONOT_MINIMISE_STATE ; 
 int /*<<< orphan*/  FINISHED_STATE ; 
 scalar_t__ FLAGS_GET_RCODE (int /*<<< orphan*/ ) ; 
 void* INIT_MINIMISE_STATE ; 
 int /*<<< orphan*/  INIT_REQUEST_STATE ; 
 scalar_t__ LDNS_RCODE_NOERROR ; 
 scalar_t__ LDNS_RCODE_NXDOMAIN ; 
 int /*<<< orphan*/  LDNS_RCODE_SERVFAIL ; 
 scalar_t__ LDNS_RCODE_YXDOMAIN ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_CNAME ; 
 scalar_t__ LDNS_RR_TYPE_DNAME ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_DS ; 
 scalar_t__ LDNS_RR_TYPE_NS ; 
 scalar_t__ MINIMISE_STATE ; 
 int /*<<< orphan*/  QUERYTARGETS_STATE ; 
 int RESPONSE_TYPE_ANSWER ; 
 int RESPONSE_TYPE_CNAME ; 
 int RESPONSE_TYPE_LAME ; 
 int RESPONSE_TYPE_REC_LAME ; 
 int RESPONSE_TYPE_REFERRAL ; 
 int RESPONSE_TYPE_THROWAWAY ; 
 int RESPONSE_TYPE_UNTYPED ; 
 scalar_t__ SKIP_MINIMISE_STATE ; 
 scalar_t__ VERB_ALGO ; 
 scalar_t__ VERB_DETAIL ; 
 int /*<<< orphan*/  VERB_QUERY ; 
 int /*<<< orphan*/  auth_zones_can_fallback (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_fill_missing (TYPE_16__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_9__*) ; 
 struct delegpt_addr* delegpt_find_addr (TYPE_9__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_9__* delegpt_from_message (TYPE_7__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  delegpt_log (scalar_t__,TYPE_9__*) ; 
 int /*<<< orphan*/  dname_strict_subdomain_c (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ dname_subdomain_c (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errinf (struct module_qstate*,char*) ; 
 int /*<<< orphan*/  errinf_dname (struct module_qstate*,char*,int /*<<< orphan*/ *) ; 
 int error_response (struct module_qstate*,int,int /*<<< orphan*/ ) ; 
 int final_state (struct iter_qstate*) ; 
 struct ub_packed_rrset_key* find_NS (TYPE_6__*,int,int) ; 
 int /*<<< orphan*/  fptr_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fptr_whitelist_modenv_detach_subs (int /*<<< orphan*/  (*) (struct module_qstate*)) ; 
 int /*<<< orphan*/  generate_dnskey_prefetch (struct module_qstate*,struct iter_qstate*,int) ; 
 int /*<<< orphan*/  generate_ns_check (struct module_qstate*,struct iter_qstate*,int) ; 
 int /*<<< orphan*/  generate_sub_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct module_qstate*,int,struct iter_qstate*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct module_qstate**,int) ; 
 int /*<<< orphan*/  get_cname_target (TYPE_39__*,int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/  handle_cname_response (struct module_qstate*,struct iter_qstate*,TYPE_7__*,int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/  infra_ratelimit_dec (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  infra_set_lame (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inplace_cb_query_response_call (TYPE_16__*,struct module_qstate*,TYPE_7__*) ; 
 int /*<<< orphan*/  iter_dns_store (TYPE_16__*,TYPE_13__*,TYPE_6__*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ iter_dp_cangodown (TYPE_31__*,TYPE_9__*) ; 
 scalar_t__ iter_ds_toolow (TYPE_7__*,TYPE_9__*) ; 
 scalar_t__ iter_indicates_dnssec (TYPE_16__*,TYPE_9__*,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iter_merge_retry_counts (TYPE_9__*,TYPE_25__*) ; 
 int /*<<< orphan*/  iter_msg_from_zone (TYPE_7__*,TYPE_9__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iter_msg_has_dnssec (TYPE_7__*) ; 
 int /*<<< orphan*/  iter_scrub_ds (TYPE_7__*,struct ub_packed_rrset_key*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iter_scrub_nxdomain (TYPE_7__*) ; 
 int /*<<< orphan*/  iter_store_parentside_NS (TYPE_16__*,TYPE_6__*) ; 
 int /*<<< orphan*/  iter_store_parentside_rrset (TYPE_16__*,scalar_t__) ; 
 int /*<<< orphan*/  log_dns_msg (char*,TYPE_13__*,TYPE_6__*) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  log_query_info (int /*<<< orphan*/ ,char*,TYPE_13__*) ; 
 int /*<<< orphan*/  log_rrset_key (scalar_t__,char*,scalar_t__) ; 
 int /*<<< orphan*/  log_warn (char*,int) ; 
 int next_state (struct iter_qstate*,int /*<<< orphan*/ ) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outbound_list_clear (int /*<<< orphan*/ *) ; 
 int processDSNSFind (struct module_qstate*,struct iter_qstate*,int) ; 
 scalar_t__ query_dname_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ reply_find_rrset (TYPE_6__*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ reply_find_rrset_section_an (TYPE_6__*,int /*<<< orphan*/ *,size_t,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ reply_find_rrset_section_ns (TYPE_6__*,int /*<<< orphan*/ *,size_t,scalar_t__,int /*<<< orphan*/ ) ; 
 int response_type_from_server (int,TYPE_7__*,TYPE_8__*,TYPE_9__*) ; 
 int /*<<< orphan*/  sock_list_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct module_qstate*) ; 
 int /*<<< orphan*/  stub2 (struct module_qstate*) ; 
 int /*<<< orphan*/  stub3 (struct module_qstate*) ; 
 int /*<<< orphan*/  stub4 (struct module_qstate*) ; 
 int /*<<< orphan*/  stub5 (struct module_qstate*) ; 
 int /*<<< orphan*/  stub6 (struct module_qstate*) ; 
 int /*<<< orphan*/  val_neg_addreferral (scalar_t__,TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verbose (scalar_t__,char*,...) ; 
 scalar_t__ verbosity ; 

__attribute__((used)) static int
processQueryResponse(struct module_qstate* qstate, struct iter_qstate* iq,
	int id)
{
	int dnsseclame = 0;
	enum response_type type;
	iq->num_current_queries--;

	if(!inplace_cb_query_response_call(qstate->env, qstate, iq->response))
		log_err("unable to call query_response callback");

	if(iq->response == NULL) {
		/* Don't increment qname when QNAME minimisation is enabled */
		if(qstate->env->cfg->qname_minimisation) {
			iq->minimise_timeout_count++;
			iq->minimisation_state = SKIP_MINIMISE_STATE;
		}
		iq->chase_to_rd = 0;
		iq->dnssec_lame_query = 0;
		verbose(VERB_ALGO, "query response was timeout");
		return next_state(iq, QUERYTARGETS_STATE);
	}
	type = response_type_from_server(
		(int)((iq->chase_flags&BIT_RD) || iq->chase_to_rd),
		iq->response, &iq->qinfo_out, iq->dp);
	iq->chase_to_rd = 0;
	if(type == RESPONSE_TYPE_REFERRAL && (iq->chase_flags&BIT_RD) &&
		!iq->auth_zone_response) {
		/* When forwarding (RD bit is set), we handle referrals 
		 * differently. No queries should be sent elsewhere */
		type = RESPONSE_TYPE_ANSWER;
	}
	if(!qstate->env->cfg->disable_dnssec_lame_check && iq->dnssec_expected 
                && !iq->dnssec_lame_query &&
		!(iq->chase_flags&BIT_RD) 
		&& iq->sent_count < DNSSEC_LAME_DETECT_COUNT
		&& type != RESPONSE_TYPE_LAME 
		&& type != RESPONSE_TYPE_REC_LAME 
		&& type != RESPONSE_TYPE_THROWAWAY 
		&& type != RESPONSE_TYPE_UNTYPED) {
		/* a possible answer, see if it is missing DNSSEC */
		/* but not when forwarding, so we dont mark fwder lame */
		if(!iter_msg_has_dnssec(iq->response)) {
			/* Mark this address as dnsseclame in this dp,
			 * because that will make serverselection disprefer
			 * it, but also, once it is the only final option,
			 * use dnssec-lame-bypass if it needs to query there.*/
			if(qstate->reply) {
				struct delegpt_addr* a = delegpt_find_addr(
					iq->dp, &qstate->reply->addr,
					qstate->reply->addrlen);
				if(a) a->dnsseclame = 1;
			}
			/* test the answer is from the zone we expected,
		 	 * otherwise, (due to parent,child on same server), we
		 	 * might mark the server,zone lame inappropriately */
			if(!iter_msg_from_zone(iq->response, iq->dp, type,
				iq->qchase.qclass))
				qstate->reply = NULL;
			type = RESPONSE_TYPE_LAME;
			dnsseclame = 1;
		}
	} else iq->dnssec_lame_query = 0;
	/* see if referral brings us close to the target */
	if(type == RESPONSE_TYPE_REFERRAL) {
		struct ub_packed_rrset_key* ns = find_NS(
			iq->response->rep, iq->response->rep->an_numrrsets,
			iq->response->rep->an_numrrsets 
			+ iq->response->rep->ns_numrrsets);
		if(!ns) ns = find_NS(iq->response->rep, 0, 
				iq->response->rep->an_numrrsets);
		if(!ns || !dname_strict_subdomain_c(ns->rk.dname, iq->dp->name) 
			|| !dname_subdomain_c(iq->qchase.qname, ns->rk.dname)){
			verbose(VERB_ALGO, "bad referral, throwaway");
			type = RESPONSE_TYPE_THROWAWAY;
		} else
			iter_scrub_ds(iq->response, ns, iq->dp->name);
	} else iter_scrub_ds(iq->response, NULL, NULL);
	if(type == RESPONSE_TYPE_THROWAWAY &&
		FLAGS_GET_RCODE(iq->response->rep->flags) == LDNS_RCODE_YXDOMAIN) {
		/* YXDOMAIN is a permanent error, no need to retry */
		type = RESPONSE_TYPE_ANSWER;
	}
	if(type == RESPONSE_TYPE_CNAME && iq->response->rep->an_numrrsets >= 1
		&& ntohs(iq->response->rep->rrsets[0]->rk.type) == LDNS_RR_TYPE_DNAME) {
		uint8_t* sname = NULL;
		size_t snamelen = 0;
		get_cname_target(iq->response->rep->rrsets[0], &sname,
			&snamelen);
		if(snamelen && dname_subdomain_c(sname, iq->response->rep->rrsets[0]->rk.dname)) {
			/* DNAME to a subdomain loop; do not recurse */
			type = RESPONSE_TYPE_ANSWER;
		}
	} else if(type == RESPONSE_TYPE_CNAME &&
		iq->qchase.qtype == LDNS_RR_TYPE_CNAME &&
		iq->minimisation_state == MINIMISE_STATE &&
		query_dname_compare(iq->qchase.qname, iq->qinfo_out.qname) == 0) {
		/* The minimised query for full QTYPE and hidden QTYPE can be
		 * classified as CNAME response type, even when the original
		 * QTYPE=CNAME. This should be treated as answer response type.
		 */
		type = RESPONSE_TYPE_ANSWER;
	}

	/* handle each of the type cases */
	if(type == RESPONSE_TYPE_ANSWER) {
		/* ANSWER type responses terminate the query algorithm, 
		 * so they sent on their */
		if(verbosity >= VERB_DETAIL) {
			verbose(VERB_DETAIL, "query response was %s",
				FLAGS_GET_RCODE(iq->response->rep->flags)
				==LDNS_RCODE_NXDOMAIN?"NXDOMAIN ANSWER":
				(iq->response->rep->an_numrrsets?"ANSWER":
				"nodata ANSWER"));
		}
		/* if qtype is DS, check we have the right level of answer,
		 * like grandchild answer but we need the middle, reject it */
		if(iq->qchase.qtype == LDNS_RR_TYPE_DS && !iq->dsns_point
			&& !(iq->chase_flags&BIT_RD)
			&& iter_ds_toolow(iq->response, iq->dp)
			&& iter_dp_cangodown(&iq->qchase, iq->dp)) {
			/* close down outstanding requests to be discarded */
			outbound_list_clear(&iq->outlist);
			iq->num_current_queries = 0;
			fptr_ok(fptr_whitelist_modenv_detach_subs(
				qstate->env->detach_subs));
			(*qstate->env->detach_subs)(qstate);
			iq->num_target_queries = 0;
			return processDSNSFind(qstate, iq, id);
		}
		if(!qstate->no_cache_store)
			iter_dns_store(qstate->env, &iq->response->qinfo,
				iq->response->rep, 0, qstate->prefetch_leeway,
				iq->dp&&iq->dp->has_parent_side_NS,
				qstate->region, qstate->query_flags);
		/* close down outstanding requests to be discarded */
		outbound_list_clear(&iq->outlist);
		iq->num_current_queries = 0;
		fptr_ok(fptr_whitelist_modenv_detach_subs(
			qstate->env->detach_subs));
		(*qstate->env->detach_subs)(qstate);
		iq->num_target_queries = 0;
		if(qstate->reply)
			sock_list_insert(&qstate->reply_origin, 
				&qstate->reply->addr, qstate->reply->addrlen, 
				qstate->region);
		if(iq->minimisation_state != DONOT_MINIMISE_STATE
			&& !(iq->chase_flags & BIT_RD)) {
			if(FLAGS_GET_RCODE(iq->response->rep->flags) != 
				LDNS_RCODE_NOERROR) {
				if(qstate->env->cfg->qname_minimisation_strict) {
					if(FLAGS_GET_RCODE(iq->response->rep->flags) ==
						LDNS_RCODE_NXDOMAIN) {
						iter_scrub_nxdomain(iq->response);
						return final_state(iq);
					}
					return error_response(qstate, id,
						LDNS_RCODE_SERVFAIL);
				}
				/* Best effort qname-minimisation. 
				 * Stop minimising and send full query when
				 * RCODE is not NOERROR. */
				iq->minimisation_state = DONOT_MINIMISE_STATE;
			}
			if(FLAGS_GET_RCODE(iq->response->rep->flags) ==
				LDNS_RCODE_NXDOMAIN) {
				/* Stop resolving when NXDOMAIN is DNSSEC
				 * signed. Based on assumption that nameservers
				 * serving signed zones do not return NXDOMAIN
				 * for empty-non-terminals. */
				if(iq->dnssec_expected)
					return final_state(iq);
				/* Make subrequest to validate intermediate
				 * NXDOMAIN if harden-below-nxdomain is
				 * enabled. */
				if(qstate->env->cfg->harden_below_nxdomain) {
					struct module_qstate* subq = NULL;
					log_query_info(VERB_QUERY,
						"schedule NXDOMAIN validation:",
						&iq->response->qinfo);
					if(!generate_sub_request(
						iq->response->qinfo.qname,
						iq->response->qinfo.qname_len,
						iq->response->qinfo.qtype,
						iq->response->qinfo.qclass,
						qstate, id, iq,
						INIT_REQUEST_STATE,
						FINISHED_STATE, &subq, 1))
						verbose(VERB_ALGO,
						"could not validate NXDOMAIN "
						"response");
					outbound_list_clear(&iq->outlist);
					iq->num_current_queries = 0;
					fptr_ok(fptr_whitelist_modenv_detach_subs(
						qstate->env->detach_subs));
					(*qstate->env->detach_subs)(qstate);
					iq->num_target_queries = 0;
				}
			}
			return next_state(iq, QUERYTARGETS_STATE);
		}
		return final_state(iq);
	} else if(type == RESPONSE_TYPE_REFERRAL) {
		/* REFERRAL type responses get a reset of the 
		 * delegation point, and back to the QUERYTARGETS_STATE. */
		verbose(VERB_DETAIL, "query response was REFERRAL");

		if(!(iq->chase_flags & BIT_RD) && !iq->ratelimit_ok) {
			/* we have a referral, no ratelimit, we can send
			 * our queries to the given name */
			infra_ratelimit_dec(qstate->env->infra_cache,
				iq->dp->name, iq->dp->namelen,
				*qstate->env->now);
		}

		/* if hardened, only store referral if we asked for it */
		if(!qstate->no_cache_store &&
		(!qstate->env->cfg->harden_referral_path ||
		    (  qstate->qinfo.qtype == LDNS_RR_TYPE_NS 
			&& (qstate->query_flags&BIT_RD) 
			&& !(qstate->query_flags&BIT_CD)
			   /* we know that all other NS rrsets are scrubbed
			    * away, thus on referral only one is left.
			    * see if that equals the query name... */
			&& ( /* auth section, but sometimes in answer section*/
			  reply_find_rrset_section_ns(iq->response->rep,
				iq->qchase.qname, iq->qchase.qname_len,
				LDNS_RR_TYPE_NS, iq->qchase.qclass)
			  || reply_find_rrset_section_an(iq->response->rep,
				iq->qchase.qname, iq->qchase.qname_len,
				LDNS_RR_TYPE_NS, iq->qchase.qclass)
			  )
		    ))) {
			/* Store the referral under the current query */
			/* no prefetch-leeway, since its not the answer */
			iter_dns_store(qstate->env, &iq->response->qinfo,
				iq->response->rep, 1, 0, 0, NULL, 0);
			if(iq->store_parent_NS)
				iter_store_parentside_NS(qstate->env, 
					iq->response->rep);
			if(qstate->env->neg_cache)
				val_neg_addreferral(qstate->env->neg_cache, 
					iq->response->rep, iq->dp->name);
		}
		/* store parent-side-in-zone-glue, if directly queried for */
		if(!qstate->no_cache_store && iq->query_for_pside_glue
			&& !iq->pside_glue) {
				iq->pside_glue = reply_find_rrset(iq->response->rep, 
					iq->qchase.qname, iq->qchase.qname_len, 
					iq->qchase.qtype, iq->qchase.qclass);
				if(iq->pside_glue) {
					log_rrset_key(VERB_ALGO, "found parent-side "
						"glue", iq->pside_glue);
					iter_store_parentside_rrset(qstate->env,
						iq->pside_glue);
				}
		}

		/* Reset the event state, setting the current delegation 
		 * point to the referral. */
		iq->deleg_msg = iq->response;
		iq->dp = delegpt_from_message(iq->response, qstate->region);
		if (qstate->env->cfg->qname_minimisation)
			iq->minimisation_state = INIT_MINIMISE_STATE;
		if(!iq->dp) {
			errinf(qstate, "malloc failure, for delegation point");
			return error_response(qstate, id, LDNS_RCODE_SERVFAIL);
		}
		if(!cache_fill_missing(qstate->env, iq->qchase.qclass, 
			qstate->region, iq->dp)) {
			errinf(qstate, "malloc failure, copy extra info into delegation point");
			return error_response(qstate, id, LDNS_RCODE_SERVFAIL);
		}
		if(iq->store_parent_NS && query_dname_compare(iq->dp->name,
			iq->store_parent_NS->name) == 0)
			iter_merge_retry_counts(iq->dp, iq->store_parent_NS);
		delegpt_log(VERB_ALGO, iq->dp);
		/* Count this as a referral. */
		iq->referral_count++;
		iq->sent_count = 0;
		/* see if the next dp is a trust anchor, or a DS was sent
		 * along, indicating dnssec is expected for next zone */
		iq->dnssec_expected = iter_indicates_dnssec(qstate->env, 
			iq->dp, iq->response, iq->qchase.qclass);
		/* if dnssec, validating then also fetch the key for the DS */
		if(iq->dnssec_expected && qstate->env->cfg->prefetch_key &&
			!(qstate->query_flags&BIT_CD))
			generate_dnskey_prefetch(qstate, iq, id);

		/* spawn off NS and addr to auth servers for the NS we just
		 * got in the referral. This gets authoritative answer
		 * (answer section trust level) rrset. 
		 * right after, we detach the subs, answer goes to cache. */
		if(qstate->env->cfg->harden_referral_path)
			generate_ns_check(qstate, iq, id);

		/* stop current outstanding queries. 
		 * FIXME: should the outstanding queries be waited for and
		 * handled? Say by a subquery that inherits the outbound_entry.
		 */
		outbound_list_clear(&iq->outlist);
		iq->num_current_queries = 0;
		fptr_ok(fptr_whitelist_modenv_detach_subs(
			qstate->env->detach_subs));
		(*qstate->env->detach_subs)(qstate);
		iq->num_target_queries = 0;
		verbose(VERB_ALGO, "cleared outbound list for next round");
		return next_state(iq, QUERYTARGETS_STATE);
	} else if(type == RESPONSE_TYPE_CNAME) {
		uint8_t* sname = NULL;
		size_t snamelen = 0;
		/* CNAME type responses get a query restart (i.e., get a 
		 * reset of the query state and go back to INIT_REQUEST_STATE).
		 */
		verbose(VERB_DETAIL, "query response was CNAME");
		if(verbosity >= VERB_ALGO)
			log_dns_msg("cname msg", &iq->response->qinfo, 
				iq->response->rep);
		/* if qtype is DS, check we have the right level of answer,
		 * like grandchild answer but we need the middle, reject it */
		if(iq->qchase.qtype == LDNS_RR_TYPE_DS && !iq->dsns_point
			&& !(iq->chase_flags&BIT_RD)
			&& iter_ds_toolow(iq->response, iq->dp)
			&& iter_dp_cangodown(&iq->qchase, iq->dp)) {
			outbound_list_clear(&iq->outlist);
			iq->num_current_queries = 0;
			fptr_ok(fptr_whitelist_modenv_detach_subs(
				qstate->env->detach_subs));
			(*qstate->env->detach_subs)(qstate);
			iq->num_target_queries = 0;
			return processDSNSFind(qstate, iq, id);
		}
		/* Process the CNAME response. */
		if(!handle_cname_response(qstate, iq, iq->response, 
			&sname, &snamelen)) {
			errinf(qstate, "malloc failure, CNAME info");
			return error_response(qstate, id, LDNS_RCODE_SERVFAIL);
		}
		/* cache the CNAME response under the current query */
		/* NOTE : set referral=1, so that rrsets get stored but not 
		 * the partial query answer (CNAME only). */
		/* prefetchleeway applied because this updates answer parts */
		if(!qstate->no_cache_store)
			iter_dns_store(qstate->env, &iq->response->qinfo,
				iq->response->rep, 1, qstate->prefetch_leeway,
				iq->dp&&iq->dp->has_parent_side_NS, NULL,
				qstate->query_flags);
		/* set the current request's qname to the new value. */
		iq->qchase.qname = sname;
		iq->qchase.qname_len = snamelen;
		/* Clear the query state, since this is a query restart. */
		iq->deleg_msg = NULL;
		iq->dp = NULL;
		iq->dsns_point = NULL;
		iq->auth_zone_response = 0;
		iq->sent_count = 0;
		if(iq->minimisation_state != MINIMISE_STATE)
			/* Only count as query restart when it is not an extra
			 * query as result of qname minimisation. */
			iq->query_restart_count++;
		if(qstate->env->cfg->qname_minimisation)
			iq->minimisation_state = INIT_MINIMISE_STATE;

		/* stop current outstanding queries. 
		 * FIXME: should the outstanding queries be waited for and
		 * handled? Say by a subquery that inherits the outbound_entry.
		 */
		outbound_list_clear(&iq->outlist);
		iq->num_current_queries = 0;
		fptr_ok(fptr_whitelist_modenv_detach_subs(
			qstate->env->detach_subs));
		(*qstate->env->detach_subs)(qstate);
		iq->num_target_queries = 0;
		if(qstate->reply)
			sock_list_insert(&qstate->reply_origin, 
				&qstate->reply->addr, qstate->reply->addrlen, 
				qstate->region);
		verbose(VERB_ALGO, "cleared outbound list for query restart");
		/* go to INIT_REQUEST_STATE for new qname. */
		return next_state(iq, INIT_REQUEST_STATE);
	} else if(type == RESPONSE_TYPE_LAME) {
		/* Cache the LAMEness. */
		verbose(VERB_DETAIL, "query response was %sLAME",
			dnsseclame?"DNSSEC ":"");
		if(!dname_subdomain_c(iq->qchase.qname, iq->dp->name)) {
			log_err("mark lame: mismatch in qname and dpname");
			/* throwaway this reply below */
		} else if(qstate->reply) {
			/* need addr for lameness cache, but we may have
			 * gotten this from cache, so test to be sure */
			if(!infra_set_lame(qstate->env->infra_cache, 
				&qstate->reply->addr, qstate->reply->addrlen, 
				iq->dp->name, iq->dp->namelen, 
				*qstate->env->now, dnsseclame, 0,
				iq->qchase.qtype))
				log_err("mark host lame: out of memory");
		}
	} else if(type == RESPONSE_TYPE_REC_LAME) {
		/* Cache the LAMEness. */
		verbose(VERB_DETAIL, "query response REC_LAME: "
			"recursive but not authoritative server");
		if(!dname_subdomain_c(iq->qchase.qname, iq->dp->name)) {
			log_err("mark rec_lame: mismatch in qname and dpname");
			/* throwaway this reply below */
		} else if(qstate->reply) {
			/* need addr for lameness cache, but we may have
			 * gotten this from cache, so test to be sure */
			verbose(VERB_DETAIL, "mark as REC_LAME");
			if(!infra_set_lame(qstate->env->infra_cache, 
				&qstate->reply->addr, qstate->reply->addrlen, 
				iq->dp->name, iq->dp->namelen, 
				*qstate->env->now, 0, 1, iq->qchase.qtype))
				log_err("mark host lame: out of memory");
		} 
	} else if(type == RESPONSE_TYPE_THROWAWAY) {
		/* LAME and THROWAWAY responses are handled the same way. 
		 * In this case, the event is just sent directly back to 
		 * the QUERYTARGETS_STATE without resetting anything, 
		 * because, clearly, the next target must be tried. */
		verbose(VERB_DETAIL, "query response was THROWAWAY");
	} else {
		log_warn("A query response came back with an unknown type: %d",
			(int)type);
	}

	/* LAME, THROWAWAY and "unknown" all end up here.
	 * Recycle to the QUERYTARGETS state to hopefully try a 
	 * different target. */
	if (qstate->env->cfg->qname_minimisation &&
		!qstate->env->cfg->qname_minimisation_strict)
		iq->minimisation_state = DONOT_MINIMISE_STATE;
	if(iq->auth_zone_response) {
		/* can we fallback? */
		iq->auth_zone_response = 0;
		if(!auth_zones_can_fallback(qstate->env->auth_zones,
			iq->dp->name, iq->dp->namelen, qstate->qinfo.qclass)) {
			verbose(VERB_ALGO, "auth zone response bad, and no"
				" fallback possible, servfail");
			errinf_dname(qstate, "response is bad, no fallback, "
				"for auth zone", iq->dp->name);
			return error_response(qstate, id, LDNS_RCODE_SERVFAIL);
		}
		verbose(VERB_ALGO, "auth zone response was bad, "
			"fallback enabled");
		iq->auth_zone_avoid = 1;
		if(iq->dp->auth_dp) {
			/* we are using a dp for the auth zone, with no
			 * nameservers, get one first */
			iq->dp = NULL;
			return next_state(iq, INIT_REQUEST_STATE);
		}
	}
	return next_state(iq, QUERYTARGETS_STATE);
}