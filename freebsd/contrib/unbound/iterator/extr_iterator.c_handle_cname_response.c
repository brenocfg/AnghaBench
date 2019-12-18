#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int /*<<< orphan*/  type; int /*<<< orphan*/  dname; } ;
struct ub_packed_rrset_key {TYPE_3__ rk; } ;
struct module_qstate {int dummy; } ;
struct TYPE_4__ {size_t qname_len; int /*<<< orphan*/ * qname; } ;
struct iter_qstate {TYPE_1__ qchase; } ;
struct dns_msg {TYPE_2__* rep; } ;
struct TYPE_5__ {size_t an_numrrsets; size_t ns_numrrsets; struct ub_packed_rrset_key** rrsets; } ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_CNAME ; 
 scalar_t__ LDNS_RR_TYPE_DNAME ; 
 scalar_t__ LDNS_RR_TYPE_NSEC ; 
 scalar_t__ LDNS_RR_TYPE_NSEC3 ; 
 scalar_t__ dname_strict_subdomain_c (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_cname_target (struct ub_packed_rrset_key*,int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/  iter_add_prepend_answer (struct module_qstate*,struct iter_qstate*,struct ub_packed_rrset_key*) ; 
 int /*<<< orphan*/  iter_add_prepend_auth (struct module_qstate*,struct iter_qstate*,struct ub_packed_rrset_key*) ; 
 int /*<<< orphan*/  iter_find_rrset_in_prepend_answer (struct iter_qstate*,struct ub_packed_rrset_key*) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ query_dname_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
handle_cname_response(struct module_qstate* qstate, struct iter_qstate* iq,
        struct dns_msg* msg, uint8_t** mname, size_t* mname_len)
{
	size_t i;
	/* Start with the (current) qname. */
	*mname = iq->qchase.qname;
	*mname_len = iq->qchase.qname_len;

	/* Iterate over the ANSWER rrsets in order, looking for CNAMEs and 
	 * DNAMES. */
	for(i=0; i<msg->rep->an_numrrsets; i++) {
		struct ub_packed_rrset_key* r = msg->rep->rrsets[i];
		/* If there is a (relevant) DNAME, add it to the list.
		 * We always expect there to be CNAME that was generated 
		 * by this DNAME following, so we don't process the DNAME 
		 * directly.  */
		if(ntohs(r->rk.type) == LDNS_RR_TYPE_DNAME &&
			dname_strict_subdomain_c(*mname, r->rk.dname) &&
			!iter_find_rrset_in_prepend_answer(iq, r)) {
			if(!iter_add_prepend_answer(qstate, iq, r))
				return 0;
			continue;
		}

		if(ntohs(r->rk.type) == LDNS_RR_TYPE_CNAME &&
			query_dname_compare(*mname, r->rk.dname) == 0 &&
			!iter_find_rrset_in_prepend_answer(iq, r)) {
			/* Add this relevant CNAME rrset to the prepend list.*/
			if(!iter_add_prepend_answer(qstate, iq, r))
				return 0;
			get_cname_target(r, mname, mname_len);
		}

		/* Other rrsets in the section are ignored. */
	}
	/* add authority rrsets to authority prepend, for wildcarded CNAMEs */
	for(i=msg->rep->an_numrrsets; i<msg->rep->an_numrrsets +
		msg->rep->ns_numrrsets; i++) {
		struct ub_packed_rrset_key* r = msg->rep->rrsets[i];
		/* only add NSEC/NSEC3, as they may be needed for validation */
		if(ntohs(r->rk.type) == LDNS_RR_TYPE_NSEC ||
			ntohs(r->rk.type) == LDNS_RR_TYPE_NSEC3) {
			if(!iter_add_prepend_auth(qstate, iq, r))
				return 0;
		}
	}
	return 1;
}