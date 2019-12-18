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
struct TYPE_6__ {int /*<<< orphan*/  type; int /*<<< orphan*/ * dname; } ;
struct ub_packed_rrset_key {TYPE_3__ rk; } ;
struct TYPE_5__ {int /*<<< orphan*/  qname; } ;
struct dns_msg {TYPE_2__ qinfo; TYPE_1__* rep; } ;
struct delegpt {int /*<<< orphan*/ * name; } ;
struct TYPE_4__ {size_t an_numrrsets; size_t ns_numrrsets; struct ub_packed_rrset_key** rrsets; } ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_CNAME ; 
 scalar_t__ LDNS_RR_TYPE_DNAME ; 
 scalar_t__ LDNS_RR_TYPE_DS ; 
 scalar_t__ LDNS_RR_TYPE_NSEC ; 
 scalar_t__ LDNS_RR_TYPE_NSEC3 ; 
 scalar_t__ LDNS_RR_TYPE_SOA ; 
 scalar_t__ dname_subdomain_c (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ query_dname_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  val_find_rrset_signer (struct ub_packed_rrset_key*,int /*<<< orphan*/ **,size_t*) ; 

int
iter_ds_toolow(struct dns_msg* msg, struct delegpt* dp)
{
	/* if for query example.com, there is example.com SOA or a subdomain
	 * of example.com, then we are too low and need to fetch NS. */
	size_t i;
	/* if we have a DNAME or CNAME we are probably wrong */
	/* if we have a qtype DS in the answer section, its fine */
	for(i=0; i < msg->rep->an_numrrsets; i++) {
		struct ub_packed_rrset_key* s = msg->rep->rrsets[i];
		if(ntohs(s->rk.type) == LDNS_RR_TYPE_DNAME ||
			ntohs(s->rk.type) == LDNS_RR_TYPE_CNAME) {
			/* not the right answer, maybe too low, check the
			 * RRSIG signer name (if there is any) for a hint
			 * that it is from the dp zone anyway */
			uint8_t* sname;
			size_t slen;
			val_find_rrset_signer(s, &sname, &slen);
			if(sname && query_dname_compare(dp->name, sname)==0)
				return 0; /* it is fine, from the right dp */
			return 1;
		}
		if(ntohs(s->rk.type) == LDNS_RR_TYPE_DS)
			return 0; /* fine, we have a DS record */
	}
	for(i=msg->rep->an_numrrsets;
		i < msg->rep->an_numrrsets + msg->rep->ns_numrrsets; i++) {
		struct ub_packed_rrset_key* s = msg->rep->rrsets[i];
		if(ntohs(s->rk.type) == LDNS_RR_TYPE_SOA) {
			if(dname_subdomain_c(s->rk.dname, msg->qinfo.qname))
				return 1; /* point is too low */
			if(query_dname_compare(s->rk.dname, dp->name)==0)
				return 0; /* right dp */
		}
		if(ntohs(s->rk.type) == LDNS_RR_TYPE_NSEC ||
			ntohs(s->rk.type) == LDNS_RR_TYPE_NSEC3) {
			uint8_t* sname;
			size_t slen;
			val_find_rrset_signer(s, &sname, &slen);
			if(sname && query_dname_compare(dp->name, sname)==0)
				return 0; /* it is fine, from the right dp */
			return 1;
		}
	}
	/* we do not know */
	return 1;
}