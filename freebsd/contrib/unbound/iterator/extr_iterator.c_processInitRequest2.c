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
typedef  int /*<<< orphan*/  uint8_t ;
struct module_qstate {TYPE_1__* env; int /*<<< orphan*/  qinfo; } ;
struct TYPE_7__ {size_t qname_len; scalar_t__ qtype; int /*<<< orphan*/  qclass; int /*<<< orphan*/ * qname; } ;
struct iter_qstate {TYPE_3__ qchase; scalar_t__ refetch_glue; TYPE_4__* dp; } ;
struct iter_hints_stub {TYPE_2__* dp; } ;
struct TYPE_8__ {size_t namelen; int /*<<< orphan*/ * name; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; int /*<<< orphan*/  has_parent_side_NS; } ;
struct TYPE_5__ {int /*<<< orphan*/  hints; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_REQUEST_3_STATE ; 
 int /*<<< orphan*/  LDNS_RCODE_SERVFAIL ; 
 scalar_t__ LDNS_RR_TYPE_DS ; 
 int /*<<< orphan*/  VERB_QUERY ; 
 int /*<<< orphan*/  auth_zone_delegpt (struct module_qstate*,struct iter_qstate*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  dname_is_root (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dname_remove_label (int /*<<< orphan*/ **,size_t*) ; 
 scalar_t__ dname_subdomain_c (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errinf (struct module_qstate*,char*) ; 
 int error_response (struct module_qstate*,int,int /*<<< orphan*/ ) ; 
 struct iter_hints_stub* hints_lookup_stub (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  log_query_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int next_state (struct iter_qstate*,int /*<<< orphan*/ ) ; 
 scalar_t__ prime_stub (struct module_qstate*,struct iter_qstate*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
processInitRequest2(struct module_qstate* qstate, struct iter_qstate* iq,
	int id)
{
	uint8_t* delname;
	size_t delnamelen;
	log_query_info(VERB_QUERY, "resolving (init part 2): ", 
		&qstate->qinfo);

	delname = iq->qchase.qname;
	delnamelen = iq->qchase.qname_len;
	if(iq->refetch_glue) {
		struct iter_hints_stub* stub;
		if(!iq->dp) {
			log_err("internal or malloc fail: no dp for refetch");
			errinf(qstate, "malloc failure, no delegation info");
			return error_response(qstate, id, LDNS_RCODE_SERVFAIL);
		}
		/* Do not send queries above stub, do not set delname to dp if
		 * this is above stub without stub-first. */
		stub = hints_lookup_stub(
			qstate->env->hints, iq->qchase.qname, iq->qchase.qclass,
			iq->dp);
		if(!stub || !stub->dp->has_parent_side_NS || 
			dname_subdomain_c(iq->dp->name, stub->dp->name)) {
			delname = iq->dp->name;
			delnamelen = iq->dp->namelen;
		}
	}
	if(iq->qchase.qtype == LDNS_RR_TYPE_DS || iq->refetch_glue) {
		if(!dname_is_root(delname))
			dname_remove_label(&delname, &delnamelen);
		iq->refetch_glue = 0; /* if CNAME causes restart, no refetch */
	}

	/* see if we have an auth zone to answer from, improves dp from cache
	 * (if any dp from cache) with auth zone dp, if that is lower */
	if(!auth_zone_delegpt(qstate, iq, delname, delnamelen))
		return error_response(qstate, id, LDNS_RCODE_SERVFAIL);

	/* Check to see if we need to prime a stub zone. */
	if(prime_stub(qstate, iq, id, delname, iq->qchase.qclass)) {
		/* A priming sub request was made */
		return 0;
	}

	/* most events just get forwarded to the next state. */
	return next_state(iq, INIT_REQUEST_3_STATE);
}