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
struct ub_packed_rrset_key {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  qclass; } ;
struct module_qstate {scalar_t__ return_rcode; int /*<<< orphan*/  region; TYPE_3__ qinfo; struct dns_msg* return_msg; scalar_t__* minfo; } ;
struct iter_qstate {scalar_t__ num_current_queries; void* state; struct dns_msg* response; } ;
struct TYPE_4__ {int /*<<< orphan*/  qclass; } ;
struct dns_msg {TYPE_2__* rep; TYPE_1__ qinfo; } ;
typedef  int /*<<< orphan*/  dest ;
struct TYPE_5__ {size_t rrset_count; int an_numrrsets; int ns_numrrsets; int ar_numrrsets; scalar_t__ security; scalar_t__ qdcount; scalar_t__ ttl; scalar_t__ prefetch_ttl; scalar_t__ serve_expired_ttl; struct ub_packed_rrset_key** rrsets; int /*<<< orphan*/  flags; scalar_t__ authoritative; } ;

/* Variables and functions */
 void* FINISHED_STATE ; 
 scalar_t__ LDNS_RCODE_NOERROR ; 
 size_t RR_COUNT_MAX ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 struct dns_msg* dns_copy_msg (struct dns_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  log_query_info (int /*<<< orphan*/ ,char*,TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (struct ub_packed_rrset_key**,struct ub_packed_rrset_key**,int) ; 
 struct ub_packed_rrset_key** regional_alloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
processClassResponse(struct module_qstate* qstate, int id,
	struct module_qstate* forq)
{
	struct iter_qstate* foriq = (struct iter_qstate*)forq->minfo[id];
	struct dns_msg* from = qstate->return_msg;
	log_query_info(VERB_ALGO, "processClassResponse", &qstate->qinfo);
	log_query_info(VERB_ALGO, "processClassResponse super", &forq->qinfo);
	if(qstate->return_rcode != LDNS_RCODE_NOERROR) {
		/* cause servfail for qclass ANY query */
		foriq->response = NULL;
		foriq->state = FINISHED_STATE;
		return;
	}
	/* append result */
	if(!foriq->response) {
		/* allocate the response: copy RCODE, sec_state */
		foriq->response = dns_copy_msg(from, forq->region);
		if(!foriq->response) {
			log_err("malloc failed for qclass ANY response"); 
			foriq->state = FINISHED_STATE;
			return;
		}
		foriq->response->qinfo.qclass = forq->qinfo.qclass;
		/* qclass ANY does not receive the AA flag on replies */
		foriq->response->rep->authoritative = 0; 
	} else {
		struct dns_msg* to = foriq->response;
		/* add _from_ this response _to_ existing collection */
		/* if there are records, copy RCODE */
		/* lower sec_state if this message is lower */
		if(from->rep->rrset_count != 0) {
			size_t n = from->rep->rrset_count+to->rep->rrset_count;
			struct ub_packed_rrset_key** dest, **d;
			/* copy appropriate rcode */
			to->rep->flags = from->rep->flags;
			/* copy rrsets */
			if(from->rep->rrset_count > RR_COUNT_MAX ||
				to->rep->rrset_count > RR_COUNT_MAX) {
				log_err("malloc failed (too many rrsets) in collect ANY"); 
				foriq->state = FINISHED_STATE;
				return; /* integer overflow protection */
			}
			dest = regional_alloc(forq->region, sizeof(dest[0])*n);
			if(!dest) {
				log_err("malloc failed in collect ANY"); 
				foriq->state = FINISHED_STATE;
				return;
			}
			d = dest;
			/* copy AN */
			memcpy(dest, to->rep->rrsets, to->rep->an_numrrsets
				* sizeof(dest[0]));
			dest += to->rep->an_numrrsets;
			memcpy(dest, from->rep->rrsets, from->rep->an_numrrsets
				* sizeof(dest[0]));
			dest += from->rep->an_numrrsets;
			/* copy NS */
			memcpy(dest, to->rep->rrsets+to->rep->an_numrrsets,
				to->rep->ns_numrrsets * sizeof(dest[0]));
			dest += to->rep->ns_numrrsets;
			memcpy(dest, from->rep->rrsets+from->rep->an_numrrsets,
				from->rep->ns_numrrsets * sizeof(dest[0]));
			dest += from->rep->ns_numrrsets;
			/* copy AR */
			memcpy(dest, to->rep->rrsets+to->rep->an_numrrsets+
				to->rep->ns_numrrsets,
				to->rep->ar_numrrsets * sizeof(dest[0]));
			dest += to->rep->ar_numrrsets;
			memcpy(dest, from->rep->rrsets+from->rep->an_numrrsets+
				from->rep->ns_numrrsets,
				from->rep->ar_numrrsets * sizeof(dest[0]));
			/* update counts */
			to->rep->rrsets = d;
			to->rep->an_numrrsets += from->rep->an_numrrsets;
			to->rep->ns_numrrsets += from->rep->ns_numrrsets;
			to->rep->ar_numrrsets += from->rep->ar_numrrsets;
			to->rep->rrset_count = n;
		}
		if(from->rep->security < to->rep->security) /* lowest sec */
			to->rep->security = from->rep->security;
		if(from->rep->qdcount != 0) /* insert qd if appropriate */
			to->rep->qdcount = from->rep->qdcount;
		if(from->rep->ttl < to->rep->ttl) /* use smallest TTL */
			to->rep->ttl = from->rep->ttl;
		if(from->rep->prefetch_ttl < to->rep->prefetch_ttl)
			to->rep->prefetch_ttl = from->rep->prefetch_ttl;
		if(from->rep->serve_expired_ttl < to->rep->serve_expired_ttl)
			to->rep->serve_expired_ttl = from->rep->serve_expired_ttl;
	}
	/* are we done? */
	foriq->num_current_queries --;
	if(foriq->num_current_queries == 0)
		foriq->state = FINISHED_STATE;
}