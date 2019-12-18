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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {size_t dname_len; int /*<<< orphan*/  dname; int /*<<< orphan*/  rrset_class; int /*<<< orphan*/  type; } ;
struct ub_packed_rrset_key {TYPE_1__ rk; } ;
struct reply_info {size_t an_numrrsets; struct ub_packed_rrset_key** rrsets; } ;
struct query_info {size_t qname_len; scalar_t__ qclass; int /*<<< orphan*/ * qname; } ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_CNAME ; 
 int /*<<< orphan*/  get_cname_target (struct ub_packed_rrset_key*,int /*<<< orphan*/ **,size_t*) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ query_dname_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

uint8_t* 
reply_find_final_cname_target(struct query_info* qinfo, struct reply_info* rep)
{
	uint8_t* sname = qinfo->qname;
	size_t snamelen = qinfo->qname_len;
	size_t i;
	for(i=0; i<rep->an_numrrsets; i++) {
		struct ub_packed_rrset_key* s = rep->rrsets[i];
		/* follow CNAME chain (if any) */
		if(ntohs(s->rk.type) == LDNS_RR_TYPE_CNAME && 
			ntohs(s->rk.rrset_class) == qinfo->qclass && 
			snamelen == s->rk.dname_len &&
			query_dname_compare(sname, s->rk.dname) == 0) {
			get_cname_target(s, &sname, &snamelen);
		}
	}
	if(sname != qinfo->qname)
		return sname;
	return NULL;
}