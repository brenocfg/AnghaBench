#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  qname; } ;
struct module_qstate {void** ext_state; TYPE_2__* env; TYPE_1__ qinfo; } ;
struct TYPE_8__ {int /*<<< orphan*/  qclass; } ;
struct iter_qstate {scalar_t__ depth; scalar_t__* target_count; TYPE_3__ qchase; TYPE_4__* dp; } ;
struct iter_env {scalar_t__ max_dependency_depth; scalar_t__ supports_ipv4; scalar_t__ supports_ipv6; } ;
struct delegpt_ns {int resolved; int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; int /*<<< orphan*/  got4; int /*<<< orphan*/  got6; struct delegpt_ns* next; } ;
struct TYPE_9__ {struct delegpt_ns* nslist; } ;
struct TYPE_7__ {int /*<<< orphan*/  rnd; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_MAX_DOMAINLEN ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_A ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_AAAA ; 
 scalar_t__ MAX_TARGET_COUNT ; 
 int /*<<< orphan*/  VERB_QUERY ; 
 scalar_t__ delegpt_count_missing_targets (TYPE_4__*) ; 
 int /*<<< orphan*/  dname_str (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  generate_target_query (struct module_qstate*,struct iter_qstate*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iter_mark_cycle_targets (struct module_qstate*,TYPE_4__*) ; 
 int /*<<< orphan*/  iter_ns_probability (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  log_assert (int) ; 
 void* module_wait_subquery ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,char*,scalar_t__) ; 

__attribute__((used)) static int
query_for_targets(struct module_qstate* qstate, struct iter_qstate* iq,
        struct iter_env* ie, int id, int maxtargets, int* num)
{
	int query_count = 0;
	struct delegpt_ns* ns;
	int missing;
	int toget = 0;

	if(iq->depth == ie->max_dependency_depth)
		return 0;
	if(iq->depth > 0 && iq->target_count &&
		iq->target_count[1] > MAX_TARGET_COUNT) {
		char s[LDNS_MAX_DOMAINLEN+1];
		dname_str(qstate->qinfo.qname, s);
		verbose(VERB_QUERY, "request %s has exceeded the maximum "
			"number of glue fetches %d", s, iq->target_count[1]);
		return 0;
	}

	iter_mark_cycle_targets(qstate, iq->dp);
	missing = (int)delegpt_count_missing_targets(iq->dp);
	log_assert(maxtargets != 0); /* that would not be useful */

	/* Generate target requests. Basically, any missing targets 
	 * are queried for here, regardless if it is necessary to do 
	 * so to continue processing. */
	if(maxtargets < 0 || maxtargets > missing)
		toget = missing;
	else	toget = maxtargets;
	if(toget == 0) {
		*num = 0;
		return 1;
	}
	/* select 'toget' items from the total of 'missing' items */
	log_assert(toget <= missing);

	/* loop over missing targets */
	for(ns = iq->dp->nslist; ns; ns = ns->next) {
		if(ns->resolved)
			continue;

		/* randomly select this item with probability toget/missing */
		if(!iter_ns_probability(qstate->env->rnd, toget, missing)) {
			/* do not select this one, next; select toget number
			 * of items from a list one less in size */
			missing --;
			continue;
		}

		if(ie->supports_ipv6 && !ns->got6) {
			/* Send the AAAA request. */
			if(!generate_target_query(qstate, iq, id, 
				ns->name, ns->namelen,
				LDNS_RR_TYPE_AAAA, iq->qchase.qclass)) {
				*num = query_count;
				if(query_count > 0)
					qstate->ext_state[id] = module_wait_subquery;
				return 0;
			}
			query_count++;
		}
		/* Send the A request. */
		if(ie->supports_ipv4 && !ns->got4) {
			if(!generate_target_query(qstate, iq, id, 
				ns->name, ns->namelen, 
				LDNS_RR_TYPE_A, iq->qchase.qclass)) {
				*num = query_count;
				if(query_count > 0)
					qstate->ext_state[id] = module_wait_subquery;
				return 0;
			}
			query_count++;
		}

		/* mark this target as in progress. */
		ns->resolved = 1;
		missing--;
		toget--;
		if(toget == 0)
			break;
	}
	*num = query_count;
	if(query_count > 0)
		qstate->ext_state[id] = module_wait_subquery;

	return 1;
}