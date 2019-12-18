#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ldns_status ;
typedef  scalar_t__ ldns_rr_type ;
typedef  int /*<<< orphan*/  ldns_rr ;
struct TYPE_5__ {scalar_t__ rrsets; TYPE_2__* nsec_signatures; int /*<<< orphan*/ * nsec; } ;
typedef  TYPE_1__ ldns_dnssec_name ;
struct TYPE_6__ {int /*<<< orphan*/ * rr; } ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_NSEC ; 
 scalar_t__ LDNS_RR_TYPE_NSEC3 ; 
 scalar_t__ LDNS_RR_TYPE_RRSIG ; 
 int /*<<< orphan*/  LDNS_STATUS_ERR ; 
 int /*<<< orphan*/  LDNS_STATUS_OK ; 
 int /*<<< orphan*/  ldns_dnssec_rrs_add_rr (TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* ldns_dnssec_rrs_new () ; 
 int /*<<< orphan*/  ldns_dnssec_rrsets_add_rr (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_dnssec_rrsets_new () ; 
 scalar_t__ ldns_rdf2rr_type (int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_rr_get_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_rrsig_typecovered (int /*<<< orphan*/ *) ; 

ldns_status
ldns_dnssec_name_add_rr(ldns_dnssec_name *name,
				    ldns_rr *rr)
{
	ldns_status result = LDNS_STATUS_OK;
	ldns_rr_type rr_type;
	ldns_rr_type typecovered = 0;

	/* special handling for NSEC3 and NSECX covering RRSIGS */

	if (!name || !rr) {
		return LDNS_STATUS_ERR;
	}

	rr_type = ldns_rr_get_type(rr);

	if (rr_type == LDNS_RR_TYPE_RRSIG) {
		typecovered = ldns_rdf2rr_type(ldns_rr_rrsig_typecovered(rr));
	}

	if (rr_type == LDNS_RR_TYPE_NSEC ||
	    rr_type == LDNS_RR_TYPE_NSEC3) {
		/* XX check if is already set (and error?) */
		name->nsec = rr;
	} else if (typecovered == LDNS_RR_TYPE_NSEC ||
			 typecovered == LDNS_RR_TYPE_NSEC3) {
		if (name->nsec_signatures) {
			result = ldns_dnssec_rrs_add_rr(name->nsec_signatures, rr);
		} else {
			name->nsec_signatures = ldns_dnssec_rrs_new();
			name->nsec_signatures->rr = rr;
		}
	} else {
		/* it's a 'normal' RR, add it to the right rrset */
		if (name->rrsets) {
			result = ldns_dnssec_rrsets_add_rr(name->rrsets, rr);
		} else {
			name->rrsets = ldns_dnssec_rrsets_new();
			result = ldns_dnssec_rrsets_add_rr(name->rrsets, rr);
		}
	}
	return result;
}