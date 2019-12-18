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
struct query_info {scalar_t__ qtype; int qname_len; } ;
typedef  enum sec_status { ____Placeholder_sec_status } sec_status ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_DS ; 
 scalar_t__ LDNS_RR_TYPE_NS ; 
 scalar_t__ LDNS_RR_TYPE_NSEC ; 
 scalar_t__ LDNS_RR_TYPE_SOA ; 
 int /*<<< orphan*/  log_assert (int) ; 
 scalar_t__ nsec_has_type (struct ub_packed_rrset_key*,scalar_t__) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int sec_status_bogus ; 
 int sec_status_insecure ; 
 int sec_status_secure ; 

__attribute__((used)) static enum sec_status 
val_nsec_proves_no_ds(struct ub_packed_rrset_key* nsec, 
	struct query_info* qinfo)
{
	log_assert(qinfo->qtype == LDNS_RR_TYPE_DS);
	log_assert(ntohs(nsec->rk.type) == LDNS_RR_TYPE_NSEC);

	if(nsec_has_type(nsec, LDNS_RR_TYPE_SOA) && qinfo->qname_len != 1) {
		/* SOA present means that this is the NSEC from the child, 
		 * not the parent (so it is the wrong one). */
		return sec_status_bogus;
	}
	if(nsec_has_type(nsec, LDNS_RR_TYPE_DS)) {
		/* DS present means that there should have been a positive 
		 * response to the DS query, so there is something wrong. */
		return sec_status_bogus;
	}

	if(!nsec_has_type(nsec, LDNS_RR_TYPE_NS)) {
		/* If there is no NS at this point at all, then this 
		 * doesn't prove anything one way or the other. */
		return sec_status_insecure;
	}
	/* Otherwise, this proves no DS. */
	return sec_status_secure;
}