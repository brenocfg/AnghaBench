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
struct ub_packed_rrset_key {int dummy; } ;
struct regional {int dummy; } ;
struct iter_qstate {struct iter_prep_list* ns_prepend_list; struct iter_prep_list* an_prepend_list; } ;
struct iter_prep_list {struct ub_packed_rrset_key* rrset; struct iter_prep_list* next; } ;
struct dns_msg {TYPE_1__* rep; } ;
struct TYPE_2__ {size_t rrset_count; int an_numrrsets; size_t ns_numrrsets; int ar_numrrsets; struct ub_packed_rrset_key** rrsets; } ;

/* Variables and functions */
 size_t RR_COUNT_MAX ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  memcpy (struct ub_packed_rrset_key**,struct ub_packed_rrset_key**,int) ; 
 scalar_t__ prepend_is_duplicate (struct ub_packed_rrset_key**,size_t,struct ub_packed_rrset_key*) ; 
 struct ub_packed_rrset_key** regional_alloc (struct regional*,size_t) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
iter_prepend(struct iter_qstate* iq, struct dns_msg* msg, 
	struct regional* region)
{
	struct iter_prep_list* p;
	struct ub_packed_rrset_key** sets;
	size_t num_an = 0, num_ns = 0;;
	for(p = iq->an_prepend_list; p; p = p->next)
		num_an++;
	for(p = iq->ns_prepend_list; p; p = p->next)
		num_ns++;
	if(num_an + num_ns == 0)
		return 1;
	verbose(VERB_ALGO, "prepending %d rrsets", (int)num_an + (int)num_ns);
	if(num_an > RR_COUNT_MAX || num_ns > RR_COUNT_MAX ||
		msg->rep->rrset_count > RR_COUNT_MAX) return 0; /* overflow */
	sets = regional_alloc(region, (num_an+num_ns+msg->rep->rrset_count) *
		sizeof(struct ub_packed_rrset_key*));
	if(!sets) 
		return 0;
	/* ANSWER section */
	num_an = 0;
	for(p = iq->an_prepend_list; p; p = p->next) {
		sets[num_an++] = p->rrset;
	}
	memcpy(sets+num_an, msg->rep->rrsets, msg->rep->an_numrrsets *
		sizeof(struct ub_packed_rrset_key*));
	/* AUTH section */
	num_ns = 0;
	for(p = iq->ns_prepend_list; p; p = p->next) {
		if(prepend_is_duplicate(sets+msg->rep->an_numrrsets+num_an,
			num_ns, p->rrset) || prepend_is_duplicate(
			msg->rep->rrsets+msg->rep->an_numrrsets, 
			msg->rep->ns_numrrsets, p->rrset))
			continue;
		sets[msg->rep->an_numrrsets + num_an + num_ns++] = p->rrset;
	}
	memcpy(sets + num_an + msg->rep->an_numrrsets + num_ns, 
		msg->rep->rrsets + msg->rep->an_numrrsets, 
		(msg->rep->ns_numrrsets + msg->rep->ar_numrrsets) *
		sizeof(struct ub_packed_rrset_key*));

	/* NXDOMAIN rcode can stay if we prepended DNAME/CNAMEs, because
	 * this is what recursors should give. */
	msg->rep->rrset_count += num_an + num_ns;
	msg->rep->an_numrrsets += num_an;
	msg->rep->ns_numrrsets += num_ns;
	msg->rep->rrsets = sets;
	return 1;
}