#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  dname; int /*<<< orphan*/  rrset_class; int /*<<< orphan*/  type; } ;
struct ub_packed_rrset_key {TYPE_1__ rk; } ;
struct dns_msg {TYPE_2__* rep; } ;
struct delegpt {int namelabs; int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; } ;
typedef  enum response_type { ____Placeholder_response_type } response_type ;
struct TYPE_5__ {size_t an_numrrsets; size_t ns_numrrsets; struct ub_packed_rrset_key** rrsets; } ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_DNSKEY ; 
 scalar_t__ LDNS_RR_TYPE_NS ; 
 scalar_t__ LDNS_RR_TYPE_SOA ; 
 int RESPONSE_TYPE_ANSWER ; 
 int RESPONSE_TYPE_CNAME ; 
 int RESPONSE_TYPE_REFERRAL ; 
 int dname_count_labels (int /*<<< orphan*/ ) ; 
 scalar_t__ dname_strict_subdomain (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  log_assert (int) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ reply_find_rrset_section_an (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ reply_find_rrset_section_ns (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

int iter_msg_from_zone(struct dns_msg* msg, struct delegpt* dp,
        enum response_type type, uint16_t dclass)
{
	if(!msg || !dp || !msg->rep || !dp->name)
		return 0;
	/* SOA RRset - always from reply zone */
	if(reply_find_rrset_section_an(msg->rep, dp->name, dp->namelen,
		LDNS_RR_TYPE_SOA, dclass) ||
	   reply_find_rrset_section_ns(msg->rep, dp->name, dp->namelen,
		LDNS_RR_TYPE_SOA, dclass))
		return 1;
	if(type == RESPONSE_TYPE_REFERRAL) {
		size_t i;
		/* if it adds a single label, i.e. we expect .com,
		 * and referral to example.com. NS ... , then origin zone
		 * is .com. For a referral to sub.example.com. NS ... then
		 * we do not know, since example.com. may be in between. */
		for(i=0; i<msg->rep->an_numrrsets+msg->rep->ns_numrrsets; 
			i++) {
			struct ub_packed_rrset_key* s = msg->rep->rrsets[i];
			if(ntohs(s->rk.type) == LDNS_RR_TYPE_NS &&
				ntohs(s->rk.rrset_class) == dclass) {
				int l = dname_count_labels(s->rk.dname);
				if(l == dp->namelabs + 1 &&
					dname_strict_subdomain(s->rk.dname,
					l, dp->name, dp->namelabs))
					return 1;
			}
		}
		return 0;
	}
	log_assert(type==RESPONSE_TYPE_ANSWER || type==RESPONSE_TYPE_CNAME);
	/* not a referral, and not lame delegation (upwards), so, 
	 * any NS rrset must be from the zone itself */
	if(reply_find_rrset_section_an(msg->rep, dp->name, dp->namelen,
		LDNS_RR_TYPE_NS, dclass) ||
	   reply_find_rrset_section_ns(msg->rep, dp->name, dp->namelen,
		LDNS_RR_TYPE_NS, dclass))
		return 1;
	/* a DNSKEY set is expected at the zone apex as well */
	/* this is for 'minimal responses' for DNSKEYs */
	if(reply_find_rrset_section_an(msg->rep, dp->name, dp->namelen,
		LDNS_RR_TYPE_DNSKEY, dclass))
		return 1;
	return 0;
}