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
struct TYPE_3__ {int /*<<< orphan*/ * dname; int /*<<< orphan*/  type; int /*<<< orphan*/  rrset_class; } ;
struct ub_packed_rrset_key {TYPE_1__ rk; } ;
struct query_info {size_t qname_len; scalar_t__ qtype; scalar_t__ qclass; int /*<<< orphan*/ * qname; } ;
struct dns_msg {TYPE_2__* rep; } ;
struct delegpt {int /*<<< orphan*/ * name; } ;
typedef  enum response_type { ____Placeholder_response_type } response_type ;
struct TYPE_4__ {int flags; size_t an_numrrsets; size_t ns_numrrsets; struct ub_packed_rrset_key** rrsets; } ;

/* Variables and functions */
 int BIT_AA ; 
 int BIT_RA ; 
 scalar_t__ FLAGS_GET_RCODE (int) ; 
 scalar_t__ LDNS_RCODE_NOERROR ; 
 scalar_t__ LDNS_RCODE_NXDOMAIN ; 
 scalar_t__ LDNS_RR_TYPE_ANY ; 
 scalar_t__ LDNS_RR_TYPE_CNAME ; 
 scalar_t__ LDNS_RR_TYPE_NS ; 
 scalar_t__ LDNS_RR_TYPE_SOA ; 
 int RESPONSE_TYPE_ANSWER ; 
 int RESPONSE_TYPE_CNAME ; 
 int RESPONSE_TYPE_LAME ; 
 int RESPONSE_TYPE_REC_LAME ; 
 int RESPONSE_TYPE_REFERRAL ; 
 int RESPONSE_TYPE_THROWAWAY ; 
 scalar_t__ dname_strict_subdomain_c (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ dname_subdomain_c (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_cname_target (struct ub_packed_rrset_key*,int /*<<< orphan*/ **,size_t*) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ query_dname_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

enum response_type 
response_type_from_server(int rdset,
	struct dns_msg* msg, struct query_info* request, struct delegpt* dp)
{
	uint8_t* origzone = (uint8_t*)"\000"; /* the default */
	struct ub_packed_rrset_key* s;
	size_t i;

	if(!msg || !request)
		return RESPONSE_TYPE_THROWAWAY;
	
	/* If the message is NXDOMAIN, then it answers the question. */
	if(FLAGS_GET_RCODE(msg->rep->flags) == LDNS_RCODE_NXDOMAIN) {
		/* make sure its not recursive when we don't want it to */
		if( (msg->rep->flags&BIT_RA) &&
			!(msg->rep->flags&BIT_AA) && !rdset)
				return RESPONSE_TYPE_REC_LAME;
		/* it could be a CNAME with NXDOMAIN rcode */
		for(i=0; i<msg->rep->an_numrrsets; i++) {
			s = msg->rep->rrsets[i];
			if(ntohs(s->rk.type) == LDNS_RR_TYPE_CNAME &&
				query_dname_compare(request->qname,
				s->rk.dname) == 0) {
				return RESPONSE_TYPE_CNAME;
			}
		}
		return RESPONSE_TYPE_ANSWER;
	}
	
	/* Other response codes mean (so far) to throw the response away as
	 * meaningless and move on to the next nameserver. */
	if(FLAGS_GET_RCODE(msg->rep->flags) != LDNS_RCODE_NOERROR)
		return RESPONSE_TYPE_THROWAWAY;

	/* Note: TC bit has already been handled */

	if(dp) {
		origzone = dp->name;
	}

	/* First we look at the answer section. This can tell us if this is a
	 * CNAME or ANSWER or (provisional) ANSWER. */
	if(msg->rep->an_numrrsets > 0) {
		uint8_t* mname = request->qname;
		size_t mname_len = request->qname_len;

		/* Now look at the answer section first. 3 states: our 
		 * answer is there directly, our answer is there after 
		 * a cname, or there is just a cname. */
		for(i=0; i<msg->rep->an_numrrsets; i++) {
			s = msg->rep->rrsets[i];
			
			/* if the answer section has NS rrset, and qtype ANY 
		 	 * and the delegation is lower, and no CNAMEs followed,
		 	 * this is a referral where the NS went to AN section */
			if((request->qtype == LDNS_RR_TYPE_ANY ||
				request->qtype == LDNS_RR_TYPE_NS) &&
				ntohs(s->rk.type) == LDNS_RR_TYPE_NS &&
				ntohs(s->rk.rrset_class) == request->qclass &&
				dname_strict_subdomain_c(s->rk.dname, 
				origzone)) {
				if((msg->rep->flags&BIT_AA))
					return RESPONSE_TYPE_ANSWER;
				return RESPONSE_TYPE_REFERRAL;
			}

			/* If we have encountered an answer (before or 
			 * after a CNAME), then we are done! Note that 
			 * if qtype == CNAME then this will be noted as an
			 * ANSWER before it gets treated as a CNAME, as 
			 * it should. */
			if(ntohs(s->rk.type) == request->qtype &&
				ntohs(s->rk.rrset_class) == request->qclass &&
				query_dname_compare(mname, s->rk.dname) == 0) {
				if((msg->rep->flags&BIT_AA))
					return RESPONSE_TYPE_ANSWER;
				/* If the AA bit isn't on, and we've seen 
				 * the answer, we only provisionally say 
				 * 'ANSWER' -- it very well could be a 
				 * REFERRAL. */
				break;
			}

			/* If we have encountered a CNAME, make sure that 
			 * it is relevant. */
			if(ntohs(s->rk.type) == LDNS_RR_TYPE_CNAME &&
				query_dname_compare(mname, s->rk.dname) == 0) {
				get_cname_target(s, &mname, &mname_len);
			}
		}
		/* not a referral, and qtype any, thus an answer */
		if(request->qtype == LDNS_RR_TYPE_ANY)
			return RESPONSE_TYPE_ANSWER;
		/* if we encountered a CNAME (or a bunch of CNAMEs), and 
		 * still got to here, then it is a CNAME response. 
		 * (This is regardless of the AA bit at this point) */
		if(mname != request->qname) {
			return RESPONSE_TYPE_CNAME;
		}
	}

	/* Looking at the authority section, we just look and see if 
	 * there is a SOA record, that means a NOERROR/NODATA */
	for(i = msg->rep->an_numrrsets; i < (msg->rep->an_numrrsets +
		msg->rep->ns_numrrsets); i++) {
		s = msg->rep->rrsets[i];

		/* The normal way of detecting NOERROR/NODATA. */
		if(ntohs(s->rk.type) == LDNS_RR_TYPE_SOA &&
			dname_subdomain_c(request->qname, s->rk.dname)) {
			/* we do our own recursion, thank you */
			if( (msg->rep->flags&BIT_RA) &&
				!(msg->rep->flags&BIT_AA) && !rdset)
				return RESPONSE_TYPE_REC_LAME;
			return RESPONSE_TYPE_ANSWER;
		}
	}
	/* Looking at the authority section, we just look and see if 
	 * there is a delegation NS set, turning it into a delegation. 
	 * Otherwise, we will have to conclude ANSWER (either it is 
	 * NOERROR/NODATA, or an non-authoritative answer). */
	for(i = msg->rep->an_numrrsets; i < (msg->rep->an_numrrsets +
		msg->rep->ns_numrrsets); i++) {
		s = msg->rep->rrsets[i];

		/* Detect REFERRAL/LAME/ANSWER based on the relationship 
		 * of the NS set to the originating zone name. */
		if(ntohs(s->rk.type) == LDNS_RR_TYPE_NS) {
			/* If we are getting an NS set for the zone we 
			 * thought we were contacting, then it is an answer.*/
			if(query_dname_compare(s->rk.dname, origzone) == 0) {
				/* see if mistakenly a recursive server was
				 * deployed and is responding nonAA */
				if( (msg->rep->flags&BIT_RA) &&
					!(msg->rep->flags&BIT_AA) && !rdset)
					return RESPONSE_TYPE_REC_LAME;
				/* Or if a lame server is deployed,
				 * which gives ns==zone delegation from cache 
				 * without AA bit as well, with nodata nosoa*/
				/* real answer must be +AA and SOA RFC(2308),
				 * so this is wrong, and we SERVFAIL it if
				 * this is the only possible reply, if it
				 * is misdeployed the THROWAWAY makes us pick
				 * the next server from the selection */
				if(msg->rep->an_numrrsets==0 &&
					!(msg->rep->flags&BIT_AA) && !rdset)
					return RESPONSE_TYPE_THROWAWAY;
				return RESPONSE_TYPE_ANSWER;
			}
			/* If we are getting a referral upwards (or to 
			 * the same zone), then the server is 'lame'. */
			if(dname_subdomain_c(origzone, s->rk.dname)) {
				if(rdset) /* forward or reclame not LAME */
					return RESPONSE_TYPE_THROWAWAY;
				return RESPONSE_TYPE_LAME;
			}
			/* If the NS set is below the delegation point we 
			 * are on, and it is non-authoritative, then it is 
			 * a referral, otherwise it is an answer. */
			if(dname_subdomain_c(s->rk.dname, origzone)) {
				/* NOTE: I no longer remember in what case 
				 * we would like this to be an answer. 
				 * NODATA should have a SOA or nothing, 
				 * not an NS rrset. 
				 * True, referrals should not have the AA 
				 * bit set, but... */
				 
				/* if((msg->rep->flags&BIT_AA))
					return RESPONSE_TYPE_ANSWER; */
				return RESPONSE_TYPE_REFERRAL;
			}
			/* Otherwise, the NS set is irrelevant. */
		}
	}

	/* If we've gotten this far, this is NOERROR/NODATA (which could 
	 * be an entirely empty message) */
	/* check if recursive answer; saying it has empty cache */
	if( (msg->rep->flags&BIT_RA) && !(msg->rep->flags&BIT_AA) && !rdset)
		return RESPONSE_TYPE_REC_LAME;
	return RESPONSE_TYPE_ANSWER;
}