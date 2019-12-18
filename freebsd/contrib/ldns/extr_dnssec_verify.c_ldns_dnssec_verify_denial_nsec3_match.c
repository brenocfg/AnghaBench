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
typedef  scalar_t__ ldns_status ;
typedef  int /*<<< orphan*/  ldns_rr_type ;
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_rdf ;
typedef  scalar_t__ ldns_pkt_rcode ;

/* Variables and functions */
 scalar_t__ LDNS_RCODE_NXDOMAIN ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_CNAME ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_DS ; 
 scalar_t__ LDNS_STATUS_DNSSEC_NSEC_RR_NOT_COVERED ; 
 scalar_t__ LDNS_STATUS_DNSSEC_NSEC_WILDCARD_NOT_COVERED ; 
 scalar_t__ LDNS_STATUS_NSEC3_ERR ; 
 scalar_t__ LDNS_STATUS_OK ; 
 int /*<<< orphan*/  ldns_dname_cat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_dname_clone_from (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ldns_dname_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_dname_label_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_dname_left_chop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_dname_new_frm_str (char*) ; 
 int /*<<< orphan*/ * ldns_dnssec_nsec3_closest_encloser (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_nsec3_bitmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_nsec3_hash_name_frm_nsec3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_nsec3_optout (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_nsec_bitmap_covers_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_nsec_covers_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rdf_deep_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_get_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_list_rr (int /*<<< orphan*/ *,size_t) ; 
 size_t ldns_rr_list_rr_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_owner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * next_closer ; 

ldns_status
ldns_dnssec_verify_denial_nsec3_match( ldns_rr *rr
				     , ldns_rr_list *nsecs
				     , ATTR_UNUSED(ldns_rr_list *rrsigs)
				     , ldns_pkt_rcode packet_rcode
				     , ldns_rr_type packet_qtype
				     , bool packet_nodata
				     , ldns_rr **match
				     )
{
	ldns_rdf *closest_encloser;
	ldns_rdf *wildcard;
	ldns_rdf *hashed_wildcard_name;
	bool wildcard_covered = false;
	ldns_rdf *zone_name;
	ldns_rdf *hashed_name;
	/* self assignment to suppress uninitialized warning */
	ldns_rdf *next_closer = next_closer;
	ldns_rdf *hashed_next_closer;
	size_t i;
	ldns_status result = LDNS_STATUS_DNSSEC_NSEC_RR_NOT_COVERED;

	if (match) {
		*match = NULL;
	}

	zone_name = ldns_dname_left_chop(ldns_rr_owner(ldns_rr_list_rr(nsecs,0)));

	/* section 8.4 */
	if (packet_rcode == LDNS_RCODE_NXDOMAIN) {
		closest_encloser = ldns_dnssec_nsec3_closest_encloser(
						   ldns_rr_owner(rr),
						   ldns_rr_get_type(rr),
						   nsecs);
                if(!closest_encloser) {
                        result = LDNS_STATUS_DNSSEC_NSEC_RR_NOT_COVERED;
                        goto done;
                }

		wildcard = ldns_dname_new_frm_str("*");
		(void) ldns_dname_cat(wildcard, closest_encloser);

		for (i = 0; i < ldns_rr_list_rr_count(nsecs); i++) {
			hashed_wildcard_name =
				ldns_nsec3_hash_name_frm_nsec3(ldns_rr_list_rr(nsecs, 0),
										 wildcard
										 );
			(void) ldns_dname_cat(hashed_wildcard_name, zone_name);

			if (ldns_nsec_covers_name(ldns_rr_list_rr(nsecs, i),
								 hashed_wildcard_name)) {
				wildcard_covered = true;
				if (match) {
					*match = ldns_rr_list_rr(nsecs, i);
				}
			}
			ldns_rdf_deep_free(hashed_wildcard_name);
		}

		if (! wildcard_covered) {
			result = LDNS_STATUS_DNSSEC_NSEC_WILDCARD_NOT_COVERED;
		} else {
			result = LDNS_STATUS_OK;
		}
		ldns_rdf_deep_free(closest_encloser);
		ldns_rdf_deep_free(wildcard);

	} else if (packet_nodata && packet_qtype != LDNS_RR_TYPE_DS) {
		/* section 8.5 */
		hashed_name = ldns_nsec3_hash_name_frm_nsec3(
		                   ldns_rr_list_rr(nsecs, 0),
		                   ldns_rr_owner(rr));
		(void) ldns_dname_cat(hashed_name, zone_name);
		for (i = 0; i < ldns_rr_list_rr_count(nsecs); i++) {
			if (ldns_dname_compare(hashed_name,
			         ldns_rr_owner(ldns_rr_list_rr(nsecs, i)))
			    == 0) {
				if (!ldns_nsec_bitmap_covers_type(
					    ldns_nsec3_bitmap(ldns_rr_list_rr(nsecs, i)),
					    packet_qtype)
				    &&
				    !ldns_nsec_bitmap_covers_type(
					    ldns_nsec3_bitmap(ldns_rr_list_rr(nsecs, i)),
					    LDNS_RR_TYPE_CNAME)) {
					result = LDNS_STATUS_OK;
					if (match) {
						*match = ldns_rr_list_rr(nsecs, i);
					}
					goto done;
				}
			}
		}
		result = LDNS_STATUS_DNSSEC_NSEC_RR_NOT_COVERED;
		/* wildcard no data? section 8.7 */
		closest_encloser = ldns_dnssec_nsec3_closest_encloser(
				   ldns_rr_owner(rr),
				   ldns_rr_get_type(rr),
				   nsecs);
		if(!closest_encloser) {
			result = LDNS_STATUS_NSEC3_ERR;
			goto done;
		}
		wildcard = ldns_dname_new_frm_str("*");
		(void) ldns_dname_cat(wildcard, closest_encloser);
		for (i = 0; i < ldns_rr_list_rr_count(nsecs); i++) {
			hashed_wildcard_name =
				ldns_nsec3_hash_name_frm_nsec3(ldns_rr_list_rr(nsecs, 0),
					 wildcard);
			(void) ldns_dname_cat(hashed_wildcard_name, zone_name);

			if (ldns_dname_compare(hashed_wildcard_name,
			         ldns_rr_owner(ldns_rr_list_rr(nsecs, i)))
			    == 0) {
				if (!ldns_nsec_bitmap_covers_type(
					    ldns_nsec3_bitmap(ldns_rr_list_rr(nsecs, i)),
					    packet_qtype)
				    &&
				    !ldns_nsec_bitmap_covers_type(
					    ldns_nsec3_bitmap(ldns_rr_list_rr(nsecs, i)),
					    LDNS_RR_TYPE_CNAME)) {
					result = LDNS_STATUS_OK;
					if (match) {
						*match = ldns_rr_list_rr(nsecs, i);
					}
				}
			}
			ldns_rdf_deep_free(hashed_wildcard_name);
			if (result == LDNS_STATUS_OK) {
				break;
			}
		}
		ldns_rdf_deep_free(closest_encloser);
		ldns_rdf_deep_free(wildcard);
	} else if (packet_nodata && packet_qtype == LDNS_RR_TYPE_DS) {
		/* section 8.6 */
		/* note: up to XXX this is the same as for 8.5 */
		hashed_name = ldns_nsec3_hash_name_frm_nsec3(ldns_rr_list_rr(nsecs,
														 0),
											ldns_rr_owner(rr)
											);
		(void) ldns_dname_cat(hashed_name, zone_name);
		for (i = 0; i < ldns_rr_list_rr_count(nsecs); i++) {
			if (ldns_dname_compare(hashed_name,
							   ldns_rr_owner(ldns_rr_list_rr(nsecs,
													   i)))
			    == 0) {
				if (!ldns_nsec_bitmap_covers_type(
					    ldns_nsec3_bitmap(ldns_rr_list_rr(nsecs, i)),
					    LDNS_RR_TYPE_DS)
				    && 
				    !ldns_nsec_bitmap_covers_type(
					    ldns_nsec3_bitmap(ldns_rr_list_rr(nsecs, i)),
					    LDNS_RR_TYPE_CNAME)) {
					result = LDNS_STATUS_OK;
					if (match) {
						*match = ldns_rr_list_rr(nsecs, i);
					}
					goto done;
				}
			}
		}

		/* XXX see note above */
		result = LDNS_STATUS_DNSSEC_NSEC_RR_NOT_COVERED;

		closest_encloser = ldns_dnssec_nsec3_closest_encloser(
				   ldns_rr_owner(rr),
				   ldns_rr_get_type(rr),
				   nsecs);
		if(!closest_encloser) {
			result = LDNS_STATUS_NSEC3_ERR;
			goto done;
		}
		/* Now check if we have a Opt-Out NSEC3 that covers the "next closer"*/

		if (ldns_dname_label_count(closest_encloser) + 1
		    >= ldns_dname_label_count(ldns_rr_owner(rr))) {
			
			/* Query name *is* the "next closer". */
			hashed_next_closer = hashed_name;
		} else {

			/* "next closer" has less labels than the query name.
			 * Create the name and hash it.
			 */
			next_closer = ldns_dname_clone_from(
					ldns_rr_owner(rr),
					ldns_dname_label_count(ldns_rr_owner(rr))
					- (ldns_dname_label_count(closest_encloser) + 1)
					);
			hashed_next_closer = ldns_nsec3_hash_name_frm_nsec3(
					ldns_rr_list_rr(nsecs, 0),
					next_closer
					);
			(void) ldns_dname_cat(hashed_next_closer, zone_name);
		}
		/* Find the NSEC3 that covers the "next closer" */
		for (i = 0; i < ldns_rr_list_rr_count(nsecs); i++) {
			if (ldns_nsec_covers_name(ldns_rr_list_rr(nsecs, i),
			                          hashed_next_closer) && 
				ldns_nsec3_optout(ldns_rr_list_rr(nsecs, i))) {

				result = LDNS_STATUS_OK;
				if (match) {
					*match = ldns_rr_list_rr(nsecs, i);
				}
				break;
			}
		}
		if (ldns_dname_label_count(closest_encloser) + 1
		    < ldns_dname_label_count(ldns_rr_owner(rr))) {

			/* "next closer" has less labels than the query name.
			 * Dispose of the temporary variables that held that name.
			 */
			ldns_rdf_deep_free(hashed_next_closer);
			ldns_rdf_deep_free(next_closer);
		}
		ldns_rdf_deep_free(closest_encloser);
	}

 done:
	ldns_rdf_deep_free(zone_name);
	return result;
}