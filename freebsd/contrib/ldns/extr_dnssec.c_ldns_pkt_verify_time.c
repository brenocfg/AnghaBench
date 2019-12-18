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
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  ldns_status ;
typedef  scalar_t__ ldns_rr_type ;
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_rdf ;
typedef  int /*<<< orphan*/  ldns_pkt ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RDF_TYPE_TYPE ; 
 scalar_t__ LDNS_RR_TYPE_RRSIG ; 
 int /*<<< orphan*/  LDNS_SECTION_ANY_NOQUESTION ; 
 int /*<<< orphan*/  LDNS_STATUS_ERR ; 
 scalar_t__ htons (scalar_t__) ; 
 int /*<<< orphan*/ * ldns_pkt_rr_list_by_name_and_type (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rdf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rdf_new (int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  ldns_rr_list_deep_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_list_subtype_by_rdf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_verify_time (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

ldns_status
ldns_pkt_verify_time(const ldns_pkt *p, ldns_rr_type t, const ldns_rdf *o, 
		const ldns_rr_list *k, const ldns_rr_list *s, 
		time_t check_time, ldns_rr_list *good_keys)
{
	ldns_rr_list *rrset;
	ldns_rr_list *sigs;
	ldns_rr_list *sigs_covered;
	ldns_rdf *rdf_t;
	ldns_rr_type t_netorder;

	if (!k) {
		return LDNS_STATUS_ERR;
		/* return LDNS_STATUS_CRYPTO_NO_DNSKEY; */
	}

	if (t == LDNS_RR_TYPE_RRSIG) {
		/* we don't have RRSIG(RRSIG) (yet? ;-) ) */
		return LDNS_STATUS_ERR;
	}

	if (s) {
		/* if s is not NULL, the sigs are given to use */
		sigs = (ldns_rr_list *)s;
	} else {
		/* otherwise get them from the packet */
		sigs = ldns_pkt_rr_list_by_name_and_type(p, o,
				LDNS_RR_TYPE_RRSIG,
				LDNS_SECTION_ANY_NOQUESTION);
		if (!sigs) {
			/* no sigs */
			return LDNS_STATUS_ERR;
			/* return LDNS_STATUS_CRYPTO_NO_RRSIG; */
		}
	}

	/* rrsig are subtyped, so now we need to find the correct
	 * sigs for the type t
	 */
	t_netorder = htons(t); /* rdf are in network order! */
	/* a type identifier is a 16-bit number, so the size is 2 bytes */
	rdf_t = ldns_rdf_new(LDNS_RDF_TYPE_TYPE, 2, &t_netorder);

	sigs_covered = ldns_rr_list_subtype_by_rdf(sigs, rdf_t, 0);
	ldns_rdf_free(rdf_t);
	if (! sigs_covered) {
		if (! s) {
			ldns_rr_list_deep_free(sigs);
		}
		return LDNS_STATUS_ERR;
	}
	ldns_rr_list_deep_free(sigs_covered);

	rrset = ldns_pkt_rr_list_by_name_and_type(p, o, t,
			LDNS_SECTION_ANY_NOQUESTION);
	if (!rrset) {
		if (! s) {
			ldns_rr_list_deep_free(sigs);
		}
		return LDNS_STATUS_ERR;
	}
	return ldns_verify_time(rrset, sigs, k, check_time, good_keys);
}