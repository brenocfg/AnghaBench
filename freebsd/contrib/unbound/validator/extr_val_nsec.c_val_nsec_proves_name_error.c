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
struct TYPE_2__ {int /*<<< orphan*/ * dname; } ;
struct ub_packed_rrset_key {TYPE_1__ rk; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_TYPE_DNAME ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_NS ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_SOA ; 
 scalar_t__ dname_canonical_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ dname_strict_subdomain_c (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ dname_subdomain_c (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsec_get_next (struct ub_packed_rrset_key*,int /*<<< orphan*/ **,size_t*) ; 
 scalar_t__ nsec_has_type (struct ub_packed_rrset_key*,int /*<<< orphan*/ ) ; 
 scalar_t__ query_dname_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int 
val_nsec_proves_name_error(struct ub_packed_rrset_key* nsec, uint8_t* qname)
{
	uint8_t* owner = nsec->rk.dname;
	uint8_t* next;
	size_t nlen;
	if(!nsec_get_next(nsec, &next, &nlen))
		return 0;

	/* If NSEC owner == qname, then this NSEC proves that qname exists. */
	if(query_dname_compare(qname, owner) == 0) {
		return 0;
	}

	/* If NSEC is a parent of qname, we need to check the type map
	 * If the parent name has a DNAME or is a delegation point, then 
	 * this NSEC is being misused. */
	if(dname_subdomain_c(qname, owner) && 
		(nsec_has_type(nsec, LDNS_RR_TYPE_DNAME) ||
		(nsec_has_type(nsec, LDNS_RR_TYPE_NS) 
			&& !nsec_has_type(nsec, LDNS_RR_TYPE_SOA))
		)) {
		return 0;
	}

	if(query_dname_compare(owner, next) == 0) {
		/* this nsec is the only nsec */
		/* zone.name NSEC zone.name, disproves everything else */
		/* but only for subdomains of that zone */
		if(dname_strict_subdomain_c(qname, next))
			return 1;
	}
	else if(dname_canonical_compare(owner, next) > 0) {
		/* this is the last nsec, ....(bigger) NSEC zonename(smaller) */
		/* the names after the last (owner) name do not exist 
		 * there are no names before the zone name in the zone 
		 * but the qname must be a subdomain of the zone name(next). */
		if(dname_canonical_compare(owner, qname) < 0 &&
			dname_strict_subdomain_c(qname, next))
			return 1;
	} else {
		/* regular NSEC, (smaller) NSEC (larger) */
		if(dname_canonical_compare(owner, qname) < 0 &&
		   dname_canonical_compare(qname, next) < 0) {
			return 1;
		}
	}
	return 0;
}