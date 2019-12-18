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
typedef  int uint16_t ;
struct query_info {scalar_t__ qtype; int /*<<< orphan*/  qname_len; int /*<<< orphan*/  qname; } ;
struct delegpt_ns {int /*<<< orphan*/  name; scalar_t__ resolved; struct delegpt_ns* next; } ;
struct delegpt {int /*<<< orphan*/  name; struct delegpt_ns* nslist; scalar_t__ result_list; scalar_t__ usable_list; } ;

/* Variables and functions */
 int BIT_RD ; 
 scalar_t__ LDNS_RR_TYPE_A ; 
 scalar_t__ LDNS_RR_TYPE_AAAA ; 
 scalar_t__ delegpt_find_ns (struct delegpt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dname_subdomain_c (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int 
iter_dp_is_useless(struct query_info* qinfo, uint16_t qflags, 
	struct delegpt* dp)
{
	struct delegpt_ns* ns;
	/* check:
	 *      o RD qflag is on.
	 *      o no addresses are provided.
	 *      o all NS items are required glue.
	 * OR
	 *      o RD qflag is on.
	 *      o no addresses are provided.
	 *      o the query is for one of the nameservers in dp,
	 *        and that nameserver is a glue-name for this dp.
	 */
	if(!(qflags&BIT_RD))
		return 0;
	/* either available or unused targets */
	if(dp->usable_list || dp->result_list)
		return 0;
	
	/* see if query is for one of the nameservers, which is glue */
	if( (qinfo->qtype == LDNS_RR_TYPE_A ||
		qinfo->qtype == LDNS_RR_TYPE_AAAA) &&
		dname_subdomain_c(qinfo->qname, dp->name) &&
		delegpt_find_ns(dp, qinfo->qname, qinfo->qname_len))
		return 1;
	
	for(ns = dp->nslist; ns; ns = ns->next) {
		if(ns->resolved) /* skip failed targets */
			continue;
		if(!dname_subdomain_c(ns->name, dp->name))
			return 0; /* one address is not required glue */
	}
	return 1;
}