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
typedef  scalar_t__ ldns_rr_type ;
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_rdf ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_RRSIG ; 
 scalar_t__ ldns_dname_compare (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 scalar_t__ const ldns_rdf2rr_type (int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_rr_get_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_list_rr (int /*<<< orphan*/  const*,size_t) ; 
 size_t ldns_rr_list_rr_count (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rr_owner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_rrsig_typecovered (int /*<<< orphan*/ *) ; 

ldns_rr *
ldns_dnssec_get_rrsig_for_name_and_type(const ldns_rdf *name,
                                        const ldns_rr_type type,
                                        const ldns_rr_list *rrs)
{
	size_t i;
	ldns_rr *candidate;

	if (!name || !rrs) {
		return NULL;
	}

	for (i = 0; i < ldns_rr_list_rr_count(rrs); i++) {
		candidate = ldns_rr_list_rr(rrs, i);
		if (ldns_rr_get_type(candidate) == LDNS_RR_TYPE_RRSIG) {
			if (ldns_dname_compare(ldns_rr_owner(candidate),
			                       name) == 0 &&
			    ldns_rdf2rr_type(ldns_rr_rrsig_typecovered(candidate))
			    == type
			    ) {
				return candidate;
			}
		}
	}

	return NULL;
}