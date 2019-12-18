#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  qclass; } ;
struct module_qstate {TYPE_1__ qinfo; } ;
struct delegpt_ns {int done_pside4; int done_pside6; int /*<<< orphan*/  name; int /*<<< orphan*/  namelen; struct delegpt_ns* next; } ;
struct delegpt {struct delegpt_ns* nslist; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_TYPE_A ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_AAAA ; 
 int /*<<< orphan*/  VERB_QUERY ; 
 scalar_t__ causes_cycle (struct module_qstate*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_nametypeclass (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void 
iter_mark_pside_cycle_targets(struct module_qstate* qstate, struct delegpt* dp)
{
	struct delegpt_ns* ns;
	for(ns = dp->nslist; ns; ns = ns->next) {
		if(ns->done_pside4 && ns->done_pside6)
			continue;
		/* see if this ns as target causes dependency cycle */
		if(causes_cycle(qstate, ns->name, ns->namelen, 
			LDNS_RR_TYPE_A, qstate->qinfo.qclass)) {
			log_nametypeclass(VERB_QUERY, "skipping target due "
			 	"to dependency cycle", ns->name,
				LDNS_RR_TYPE_A, qstate->qinfo.qclass);
			ns->done_pside4 = 1;
		}
		if(causes_cycle(qstate, ns->name, ns->namelen, 
			LDNS_RR_TYPE_AAAA, qstate->qinfo.qclass)) {
			log_nametypeclass(VERB_QUERY, "skipping target due "
			 	"to dependency cycle", ns->name,
				LDNS_RR_TYPE_AAAA, qstate->qinfo.qclass);
			ns->done_pside6 = 1;
		}
	}
}