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
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_rdf ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_FREE (char*) ; 
 int /*<<< orphan*/  LDNS_STATUS_OK ; 
 int /*<<< orphan*/ * ldns_dname_label (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* ldns_rdf2str (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rdf_deep_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_list_rr (int /*<<< orphan*/ *,size_t) ; 
 int ldns_rr_list_rr_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_owner (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_set_rdf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ldns_str2rdf_b32_ext (int /*<<< orphan*/ **,char*) ; 
 int strlen (char*) ; 

ldns_status
ldns_dnssec_chain_nsec3_list(ldns_rr_list *nsec3_rrs)
{
	size_t i;
	char *next_nsec_owner_str;
	ldns_rdf *next_nsec_owner_label;
	ldns_rdf *next_nsec_rdf;
	ldns_status status = LDNS_STATUS_OK;

	for (i = 0; i < ldns_rr_list_rr_count(nsec3_rrs); i++) {
		if (i == ldns_rr_list_rr_count(nsec3_rrs) - 1) {
			next_nsec_owner_label =
				ldns_dname_label(ldns_rr_owner(ldns_rr_list_rr(nsec3_rrs,
													  0)), 0);
			next_nsec_owner_str = ldns_rdf2str(next_nsec_owner_label);
			if (next_nsec_owner_str[strlen(next_nsec_owner_str) - 1]
			    == '.') {
				next_nsec_owner_str[strlen(next_nsec_owner_str) - 1]
					= '\0';
			}
			status = ldns_str2rdf_b32_ext(&next_nsec_rdf,
									next_nsec_owner_str);
			if (!ldns_rr_set_rdf(ldns_rr_list_rr(nsec3_rrs, i),
							 next_nsec_rdf, 4)) {
				/* todo: error */
			}

			ldns_rdf_deep_free(next_nsec_owner_label);
			LDNS_FREE(next_nsec_owner_str);
		} else {
			next_nsec_owner_label =
				ldns_dname_label(ldns_rr_owner(ldns_rr_list_rr(nsec3_rrs,
													  i + 1)),
							  0);
			next_nsec_owner_str = ldns_rdf2str(next_nsec_owner_label);
			if (next_nsec_owner_str[strlen(next_nsec_owner_str) - 1]
			    == '.') {
				next_nsec_owner_str[strlen(next_nsec_owner_str) - 1]
					= '\0';
			}
			status = ldns_str2rdf_b32_ext(&next_nsec_rdf,
									next_nsec_owner_str);
			ldns_rdf_deep_free(next_nsec_owner_label);
			LDNS_FREE(next_nsec_owner_str);
			if (!ldns_rr_set_rdf(ldns_rr_list_rr(nsec3_rrs, i),
							 next_nsec_rdf, 4)) {
				/* todo: error */
			}
		}
	}
	return status;
}