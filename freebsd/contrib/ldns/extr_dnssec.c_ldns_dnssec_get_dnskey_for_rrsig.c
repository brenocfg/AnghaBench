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
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_rr ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_DNSKEY ; 
 scalar_t__ ldns_calc_keytag (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_dname_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_rdf2native_int16 (int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_rr_get_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_list_rr (int /*<<< orphan*/  const*,size_t) ; 
 size_t ldns_rr_list_rr_count (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rr_owner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_rrsig_keytag (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rr_rrsig_signame (int /*<<< orphan*/  const*) ; 

ldns_rr *
ldns_dnssec_get_dnskey_for_rrsig(const ldns_rr *rrsig,
						   const ldns_rr_list *rrs)
{
	size_t i;
	ldns_rr *candidate;

	if (!rrsig || !rrs) {
		return NULL;
	}

	for (i = 0; i < ldns_rr_list_rr_count(rrs); i++) {
		candidate = ldns_rr_list_rr(rrs, i);
		if (ldns_rr_get_type(candidate) == LDNS_RR_TYPE_DNSKEY) {
			if (ldns_dname_compare(ldns_rr_owner(candidate),
			                       ldns_rr_rrsig_signame(rrsig)) == 0 &&
			    ldns_rdf2native_int16(ldns_rr_rrsig_keytag(rrsig)) ==
			    ldns_calc_keytag(candidate)
			    ) {
				return candidate;
			}
		}
	}

	return NULL;
}