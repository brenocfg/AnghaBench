#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_13__ ;
typedef  struct TYPE_14__   TYPE_12__ ;

/* Type definitions */
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_16__ {int /*<<< orphan*/  ans_secure; scalar_t__ extended; int /*<<< orphan*/ * ans_rcode; int /*<<< orphan*/  ans_bogus; } ;
struct TYPE_19__ {TYPE_12__* cfg; scalar_t__ need_to_validate; int /*<<< orphan*/ * now; } ;
struct worker {TYPE_1__ stats; int /*<<< orphan*/  scratchpad; TYPE_4__ env; } ;
struct query_info {int /*<<< orphan*/  local_alias; int /*<<< orphan*/  qclass; int /*<<< orphan*/  qtype; int /*<<< orphan*/  qname_len; int /*<<< orphan*/  qname; } ;
struct edns_data {int udp_size; int bits; int /*<<< orphan*/ * opt_list; scalar_t__ ext_rcode; void* edns_version; } ;
struct TYPE_17__ {int /*<<< orphan*/  local_alias; } ;
struct dns_msg {TYPE_2__ qinfo; TYPE_3__* rep; } ;
struct delegpt {int dummy; } ;
struct comm_reply {TYPE_13__* c; } ;
struct TYPE_18__ {int flags; } ;
struct TYPE_15__ {int /*<<< orphan*/  buffer; } ;
struct TYPE_14__ {int /*<<< orphan*/  val_clean_additional; scalar_t__ ignore_cd; } ;

/* Variables and functions */
 int BIT_CD ; 
 int BIT_QR ; 
 int BIT_RA ; 
 void* EDNS_ADVERTISED_SIZE ; 
 void* EDNS_ADVERTISED_VERSION ; 
 int EDNS_DO ; 
 int LDNS_RCODE_MASK ; 
 size_t LDNS_RCODE_SERVFAIL ; 
 int /*<<< orphan*/  apply_edns_options (struct edns_data*,struct edns_data*,TYPE_12__*,TYPE_13__*,int /*<<< orphan*/ ) ; 
 int check_delegation_secure (TYPE_3__*) ; 
 int /*<<< orphan*/  deleg_remove_nonsecure_additional (TYPE_3__*) ; 
 struct delegpt* dns_cache_find_delegation (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dns_msg**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error_encode (int /*<<< orphan*/ ,size_t,TYPE_2__*,int,int,struct edns_data*) ; 
 int /*<<< orphan*/  inplace_cb_reply_cache_call (TYPE_4__*,struct query_info*,int /*<<< orphan*/ *,TYPE_3__*,int,struct edns_data*,struct comm_reply*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inplace_cb_reply_servfail_call (TYPE_4__*,struct query_info*,int /*<<< orphan*/ *,TYPE_3__*,size_t,struct edns_data*,struct comm_reply*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reply_info_answer_encode (TYPE_2__*,TYPE_3__*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,struct edns_data*,int,int) ; 
#define  sec_status_bogus 133 
#define  sec_status_indeterminate 132 
#define  sec_status_insecure 131 
#define  sec_status_secure 130 
#define  sec_status_secure_sentinel_fail 129 
#define  sec_status_unchecked 128 
 int /*<<< orphan*/  server_stats_insrcode (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
answer_norec_from_cache(struct worker* worker, struct query_info* qinfo,
	uint16_t id, uint16_t flags, struct comm_reply* repinfo, 
	struct edns_data* edns)
{
	/* for a nonrecursive query return either:
	 * 	o an error (servfail; we try to avoid this)
	 * 	o a delegation (closest we have; this routine tries that)
	 * 	o the answer (checked by answer_from_cache) 
	 *
	 * So, grab a delegation from the rrset cache. 
	 * Then check if it needs validation, if so, this routine fails,
	 * so that iterator can prime and validator can verify rrsets.
	 */
	struct edns_data edns_bak;
	uint16_t udpsize = edns->udp_size;
	int secure = 0;
	time_t timenow = *worker->env.now;
	int must_validate = (!(flags&BIT_CD) || worker->env.cfg->ignore_cd)
		&& worker->env.need_to_validate;
	struct dns_msg *msg = NULL;
	struct delegpt *dp;

	dp = dns_cache_find_delegation(&worker->env, qinfo->qname, 
		qinfo->qname_len, qinfo->qtype, qinfo->qclass,
		worker->scratchpad, &msg, timenow);
	if(!dp) { /* no delegation, need to reprime */
		return 0;
	}
	/* In case we have a local alias, copy it into the delegation message.
	 * Shallow copy should be fine, as we'll be done with msg in this
	 * function. */
	msg->qinfo.local_alias = qinfo->local_alias;
	if(must_validate) {
		switch(check_delegation_secure(msg->rep)) {
		case sec_status_unchecked:
			/* some rrsets have not been verified yet, go and 
			 * let validator do that */
			return 0;
		case sec_status_bogus:
		case sec_status_secure_sentinel_fail:
			/* some rrsets are bogus, reply servfail */
			edns->edns_version = EDNS_ADVERTISED_VERSION;
			edns->udp_size = EDNS_ADVERTISED_SIZE;
			edns->ext_rcode = 0;
			edns->bits &= EDNS_DO;
			if(!inplace_cb_reply_servfail_call(&worker->env, qinfo, NULL,
				msg->rep, LDNS_RCODE_SERVFAIL, edns, repinfo, worker->scratchpad))
					return 0;
			error_encode(repinfo->c->buffer, LDNS_RCODE_SERVFAIL, 
				&msg->qinfo, id, flags, edns);
			if(worker->stats.extended) {
				worker->stats.ans_bogus++;
				worker->stats.ans_rcode[LDNS_RCODE_SERVFAIL]++;
			}
			return 1;
		case sec_status_secure:
			/* all rrsets are secure */
			/* remove non-secure rrsets from the add. section*/
			if(worker->env.cfg->val_clean_additional)
				deleg_remove_nonsecure_additional(msg->rep);
			secure = 1;
			break;
		case sec_status_indeterminate:
		case sec_status_insecure:
		default:
			/* not secure */
			secure = 0;
			break;
		}
	}
	/* return this delegation from the cache */
	edns_bak = *edns;
	edns->edns_version = EDNS_ADVERTISED_VERSION;
	edns->udp_size = EDNS_ADVERTISED_SIZE;
	edns->ext_rcode = 0;
	edns->bits &= EDNS_DO;
	if(!inplace_cb_reply_cache_call(&worker->env, qinfo, NULL, msg->rep,
		(int)(flags&LDNS_RCODE_MASK), edns, repinfo, worker->scratchpad))
			return 0;
	msg->rep->flags |= BIT_QR|BIT_RA;
	if(!apply_edns_options(edns, &edns_bak, worker->env.cfg,
		repinfo->c, worker->scratchpad) ||
		!reply_info_answer_encode(&msg->qinfo, msg->rep, id, flags, 
		repinfo->c->buffer, 0, 1, worker->scratchpad,
		udpsize, edns, (int)(edns->bits & EDNS_DO), secure)) {
		if(!inplace_cb_reply_servfail_call(&worker->env, qinfo, NULL, NULL,
			LDNS_RCODE_SERVFAIL, edns, repinfo, worker->scratchpad))
				edns->opt_list = NULL;
		error_encode(repinfo->c->buffer, LDNS_RCODE_SERVFAIL, 
			&msg->qinfo, id, flags, edns);
	}
	if(worker->stats.extended) {
		if(secure) worker->stats.ans_secure++;
		server_stats_insrcode(&worker->stats, repinfo->c->buffer);
	}
	return 1;
}