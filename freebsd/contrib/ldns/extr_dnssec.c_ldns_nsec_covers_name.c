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
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  const ldns_rdf ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_FREE (char*) ; 
 scalar_t__ LDNS_RR_TYPE_NSEC ; 
 scalar_t__ LDNS_RR_TYPE_NSEC3 ; 
 int /*<<< orphan*/  LDNS_STATUS_OK ; 
 int /*<<< orphan*/  ldns_dname_cat (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_dname_compare (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* ldns_dname_left_chop (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* ldns_dname_new_frm_str (char*) ; 
 char* ldns_get_errorstr_by_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* ldns_nsec3_next_owner (int /*<<< orphan*/  const*) ; 
 char* ldns_rdf2str (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* ldns_rdf_clone (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rdf_deep_free (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_rr_get_type (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* ldns_rr_owner (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * ldns_rr_rdf (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

bool
ldns_nsec_covers_name(const ldns_rr *nsec, const ldns_rdf *name)
{
	ldns_rdf *nsec_owner = ldns_rr_owner(nsec);
	ldns_rdf *hash_next;
	char *next_hash_str;
	ldns_rdf *nsec_next = NULL;
	ldns_status status;
	ldns_rdf *chopped_dname;
	bool result;

	if (ldns_rr_get_type(nsec) == LDNS_RR_TYPE_NSEC) {
		if (ldns_rr_rdf(nsec, 0) != NULL) {
			nsec_next = ldns_rdf_clone(ldns_rr_rdf(nsec, 0));
		} else {
			return false;
		}
	} else if (ldns_rr_get_type(nsec) == LDNS_RR_TYPE_NSEC3) {
		hash_next = ldns_nsec3_next_owner(nsec);
		next_hash_str = ldns_rdf2str(hash_next);
		nsec_next = ldns_dname_new_frm_str(next_hash_str);
		LDNS_FREE(next_hash_str);
		chopped_dname = ldns_dname_left_chop(nsec_owner);
		status = ldns_dname_cat(nsec_next, chopped_dname);
		ldns_rdf_deep_free(chopped_dname);
		if (status != LDNS_STATUS_OK) {
			printf("error catting: %s\n", ldns_get_errorstr_by_id(status));
		}
	} else {
		ldns_rdf_deep_free(nsec_next);
		return false;
	}

	/* in the case of the last nsec */
	if(ldns_dname_compare(nsec_owner, nsec_next) > 0) {
		result = (ldns_dname_compare(nsec_owner, name) <= 0 ||
				ldns_dname_compare(name, nsec_next) < 0);
	} else if(ldns_dname_compare(nsec_owner, nsec_next) < 0) {
		result = (ldns_dname_compare(nsec_owner, name) <= 0 &&
		          ldns_dname_compare(name, nsec_next) < 0);
	} else {
		result = true;
	}

	ldns_rdf_deep_free(nsec_next);
	return result;
}