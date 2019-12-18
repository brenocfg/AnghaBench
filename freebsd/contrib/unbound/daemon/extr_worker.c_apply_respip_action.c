#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct worker {int /*<<< orphan*/  scratchpad; } ;
struct ub_packed_rrset_key {int dummy; } ;
struct respip_client_info {int dummy; } ;
struct respip_action_info {scalar_t__ action; scalar_t__ addrinfo; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
struct reply_info {int dummy; } ;
struct query_info {int /*<<< orphan*/  local_alias; int /*<<< orphan*/  qclass; int /*<<< orphan*/  qtype; int /*<<< orphan*/  qname; } ;
struct comm_reply {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_TYPE_A ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_AAAA ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_ANY ; 
 scalar_t__ respip_deny ; 
 scalar_t__ respip_inform_deny ; 
 int /*<<< orphan*/  respip_inform_print (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct comm_reply*) ; 
 int /*<<< orphan*/  respip_none ; 
 int /*<<< orphan*/  respip_rewrite_reply (struct query_info const*,struct respip_client_info*,struct reply_info*,struct reply_info**,struct respip_action_info*,struct ub_packed_rrset_key**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
apply_respip_action(struct worker* worker, const struct query_info* qinfo,
	struct respip_client_info* cinfo, struct reply_info* rep,
	struct comm_reply* repinfo, struct ub_packed_rrset_key** alias_rrset,
	struct reply_info** encode_repp)
{
	struct respip_action_info actinfo = {respip_none, NULL};

	if(qinfo->qtype != LDNS_RR_TYPE_A &&
		qinfo->qtype != LDNS_RR_TYPE_AAAA &&
		qinfo->qtype != LDNS_RR_TYPE_ANY)
		return 1;

	if(!respip_rewrite_reply(qinfo, cinfo, rep, encode_repp, &actinfo,
		alias_rrset, 0, worker->scratchpad))
		return 0;

	/* xxx_deny actions mean dropping the reply, unless the original reply
	 * was redirected to response-ip data. */
	if((actinfo.action == respip_deny ||
		actinfo.action == respip_inform_deny) &&
		*encode_repp == rep)
		*encode_repp = NULL;

	/* If address info is returned, it means the action should be an
	 * 'inform' variant and the information should be logged. */
	if(actinfo.addrinfo) {
		respip_inform_print(actinfo.addrinfo, qinfo->qname,
			qinfo->qtype, qinfo->qclass, qinfo->local_alias,
			repinfo);
	}

	return 1;
}