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
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct ub_packed_rrset_key {TYPE_1__ rk; } ;
struct reply_info {int flags; scalar_t__ ar_numrrsets; int rrset_count; size_t an_numrrsets; size_t ns_numrrsets; struct ub_packed_rrset_key** rrsets; } ;

/* Variables and functions */
 int BIT_AA ; 
 scalar_t__ LDNS_RR_TYPE_NS ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*) ; 

void 
caps_strip_reply(struct reply_info* rep)
{
	size_t i;
	if(!rep) return;
	/* see if message is a referral, in which case the additional and
	 * NS record cannot be removed */
	/* referrals have the AA flag unset (strict check, not elsewhere in
	 * unbound, but for 0x20 this is very convenient). */
	if(!(rep->flags&BIT_AA))
		return;
	/* remove the additional section from the reply */
	if(rep->ar_numrrsets != 0) {
		verbose(VERB_ALGO, "caps fallback: removing additional section");
		rep->rrset_count -= rep->ar_numrrsets;
		rep->ar_numrrsets = 0;
	}
	/* is there an NS set in the authority section to remove? */
	/* the failure case (Cisco firewalls) only has one rrset in authsec */
	for(i=rep->an_numrrsets; i<rep->an_numrrsets+rep->ns_numrrsets; i++) {
		struct ub_packed_rrset_key* s = rep->rrsets[i];
		if(ntohs(s->rk.type) == LDNS_RR_TYPE_NS) {
			/* remove NS rrset and break from loop (loop limits
			 * have changed) */
			/* move last rrset into this position (there is no
			 * additional section any more) */
			verbose(VERB_ALGO, "caps fallback: removing NS rrset");
			if(i < rep->rrset_count-1)
				rep->rrsets[i]=rep->rrsets[rep->rrset_count-1];
			rep->rrset_count --;
			rep->ns_numrrsets --;
			break;
		}
	}
}