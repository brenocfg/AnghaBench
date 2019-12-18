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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  rrset_class; int /*<<< orphan*/  type; int /*<<< orphan*/  dname; } ;
struct ub_packed_rrset_key {TYPE_1__ rk; } ;
struct dns_msg {TYPE_2__* rep; } ;
struct TYPE_4__ {size_t an_numrrsets; size_t ns_numrrsets; size_t rrset_count; struct ub_packed_rrset_key** rrsets; } ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_DS ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  dname_subdomain_c (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_nametypeclass (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memmove (struct ub_packed_rrset_key**,struct ub_packed_rrset_key**,int) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ query_dname_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
iter_scrub_ds(struct dns_msg* msg, struct ub_packed_rrset_key* ns, uint8_t* z)
{
	/* Only the DS record for the delegation itself is expected.
	 * We allow DS for everything between the bailiwick and the 
	 * zonecut, thus DS records must be at or above the zonecut.
	 * And the DS records must be below the server authority zone.
	 * The answer section is already scrubbed. */
	size_t i = msg->rep->an_numrrsets;
	while(i < (msg->rep->an_numrrsets + msg->rep->ns_numrrsets)) {
		struct ub_packed_rrset_key* s = msg->rep->rrsets[i];
		if(ntohs(s->rk.type) == LDNS_RR_TYPE_DS &&
			(!ns || !dname_subdomain_c(ns->rk.dname, s->rk.dname)
			|| query_dname_compare(z, s->rk.dname) == 0)) {
			log_nametypeclass(VERB_ALGO, "removing irrelevant DS",
				s->rk.dname, ntohs(s->rk.type),
				ntohs(s->rk.rrset_class));
			memmove(msg->rep->rrsets+i, msg->rep->rrsets+i+1,
				sizeof(struct ub_packed_rrset_key*) * 
				(msg->rep->rrset_count-i-1));
			msg->rep->ns_numrrsets--;
			msg->rep->rrset_count--;
			/* stay at same i, but new record */
			continue;
		}
		i++;
	}
}