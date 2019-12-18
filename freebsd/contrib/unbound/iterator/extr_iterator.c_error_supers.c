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
struct TYPE_4__ {scalar_t__ qtype; int /*<<< orphan*/  qname_len; int /*<<< orphan*/  qname; } ;
struct module_qstate {TYPE_2__ qinfo; int /*<<< orphan*/  region; int /*<<< orphan*/  env; scalar_t__* minfo; } ;
struct TYPE_3__ {int /*<<< orphan*/  qclass; } ;
struct iter_qstate {int /*<<< orphan*/  state; int /*<<< orphan*/ * dp; TYPE_1__ qchase; int /*<<< orphan*/  num_target_queries; } ;
struct delegpt_ns {int resolved; } ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_A ; 
 scalar_t__ LDNS_RR_TYPE_AAAA ; 
 scalar_t__ LDNS_RR_TYPE_NS ; 
 int /*<<< orphan*/  QUERYTARGETS_STATE ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  cache_fill_missing (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct delegpt_ns* delegpt_find_ns (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  log_query_info (int /*<<< orphan*/ ,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
error_supers(struct module_qstate* qstate, int id, struct module_qstate* super)
{
	struct iter_qstate* super_iq = (struct iter_qstate*)super->minfo[id];

	if(qstate->qinfo.qtype == LDNS_RR_TYPE_A ||
		qstate->qinfo.qtype == LDNS_RR_TYPE_AAAA) {
		/* mark address as failed. */
		struct delegpt_ns* dpns = NULL;
		super_iq->num_target_queries--; 
		if(super_iq->dp)
			dpns = delegpt_find_ns(super_iq->dp, 
				qstate->qinfo.qname, qstate->qinfo.qname_len);
		if(!dpns) {
			/* not interested */
			/* this can happen, for eg. qname minimisation asked
			 * for an NXDOMAIN to be validated, and used qtype
			 * A for that, and the error of that, the name, is
			 * not listed in super_iq->dp */
			verbose(VERB_ALGO, "subq error, but not interested");
			log_query_info(VERB_ALGO, "superq", &super->qinfo);
			return;
		} else {
			/* see if the failure did get (parent-lame) info */
			if(!cache_fill_missing(super->env, super_iq->qchase.qclass,
				super->region, super_iq->dp))
				log_err("out of memory adding missing");
		}
		dpns->resolved = 1; /* mark as failed */
	}
	if(qstate->qinfo.qtype == LDNS_RR_TYPE_NS) {
		/* prime failed to get delegation */
		super_iq->dp = NULL;
	}
	/* evaluate targets again */
	super_iq->state = QUERYTARGETS_STATE; 
	/* super becomes runnable, and will process this change */
}