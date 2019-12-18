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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  dname; int /*<<< orphan*/  type; int /*<<< orphan*/  rrset_class; } ;
struct ub_packed_rrset_key {TYPE_2__ rk; } ;
struct query_info {scalar_t__ qtype; size_t qname_len; scalar_t__ qclass; int /*<<< orphan*/ * qname; } ;
struct dns_msg {TYPE_1__* rep; } ;
typedef  enum response_type { ____Placeholder_response_type } response_type ;
struct TYPE_3__ {scalar_t__ an_numrrsets; struct ub_packed_rrset_key** rrsets; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 scalar_t__ FLAGS_GET_RCODE (int /*<<< orphan*/ ) ; 
 scalar_t__ LDNS_RCODE_NXDOMAIN ; 
 scalar_t__ LDNS_RR_TYPE_ANY ; 
 scalar_t__ LDNS_RR_TYPE_CNAME ; 
 int RESPONSE_TYPE_ANSWER ; 
 int RESPONSE_TYPE_CNAME ; 
 int /*<<< orphan*/  get_cname_target (struct ub_packed_rrset_key*,int /*<<< orphan*/ **,size_t*) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ query_dname_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

enum response_type 
response_type_from_cache(struct dns_msg* msg, 
	struct query_info* request)
{
	/* If the message is NXDOMAIN, then it is an ANSWER. */
	if(FLAGS_GET_RCODE(msg->rep->flags) == LDNS_RCODE_NXDOMAIN)
		return RESPONSE_TYPE_ANSWER;
	if(request->qtype == LDNS_RR_TYPE_ANY)
		return RESPONSE_TYPE_ANSWER;
	
	/* First we look at the answer section. This can tell us if this is
	 * CNAME or positive ANSWER. */
	if(msg->rep->an_numrrsets > 0) {
		/* Now look at the answer section first. 3 states: 
		 *	o our answer is there directly,
		 *	o our answer is there after a cname,
		 *	o or there is just a cname. */
		uint8_t* mname = request->qname;
		size_t mname_len = request->qname_len;
		size_t i;
		for(i=0; i<msg->rep->an_numrrsets; i++) {
			struct ub_packed_rrset_key* s = msg->rep->rrsets[i];

			/* If we have encountered an answer (before or 
			 * after a CNAME), then we are done! Note that 
			 * if qtype == CNAME then this will be noted as 
			 * an ANSWER before it gets treated as a CNAME, 
			 * as it should */
			if(ntohs(s->rk.type) == request->qtype &&
				ntohs(s->rk.rrset_class) == request->qclass &&
				query_dname_compare(mname, s->rk.dname) == 0) {
				return RESPONSE_TYPE_ANSWER;
			}

			/* If we have encountered a CNAME, make sure that 
			 * it is relevant. */
			if(ntohs(s->rk.type) == LDNS_RR_TYPE_CNAME &&
				query_dname_compare(mname, s->rk.dname) == 0) {
				get_cname_target(s, &mname, &mname_len);
			}
		}

		/* if we encountered a CNAME (or a bunch of CNAMEs), and 
		 * still got to here, then it is a CNAME response. (i.e., 
		 * the CNAME chain didn't terminate in an answer rrset.) */
		if(mname != request->qname) {
			return RESPONSE_TYPE_CNAME;
		}
	}

	/* At this point, since we don't need to detect REFERRAL or LAME 
	 * messages, it can only be an ANSWER. */
	return RESPONSE_TYPE_ANSWER;
}