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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int ldns_rr_type ;
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_rdf ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_FREE (int /*<<< orphan*/ *) ; 
 scalar_t__ LDNS_STATUS_OK ; 
 scalar_t__ ldns_dname_cat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_dname_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_dname_label_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_dname_left_chop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_nsec3_algorithm (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_nsec3_hash_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_nsec3_iterations (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_nsec3_salt_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_nsec3_salt_length (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_nsec_covers_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rdf_clone (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rdf_deep_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rdf_print (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_list_rr (int /*<<< orphan*/ *,size_t) ; 
 size_t ldns_rr_list_rr_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_owner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 
 int verbosity ; 

ldns_rdf *
ldns_nsec3_closest_encloser(ldns_rdf *qname, ldns_rr_type qtype, ldns_rr_list *nsec3s)
{
	/* remember parameters, they must match */
	uint8_t algorithm;
	uint32_t iterations;
	uint8_t salt_length;
	uint8_t *salt;

	ldns_rdf *sname = NULL, *hashed_sname = NULL, *tmp;
	bool flag;
	
	bool exact_match_found;
	bool in_range_found;
	
	ldns_rdf *zone_name = NULL;
	
	size_t nsec_i;
	ldns_rr *nsec;
	ldns_rdf *result = NULL;
	
	if (!qname || !nsec3s || ldns_rr_list_rr_count(nsec3s) < 1) {
		return NULL;
	}

	if (verbosity >= 4) {
		printf(";; finding closest encloser for type %d ", qtype);
		ldns_rdf_print(stdout, qname);
		printf("\n");
	}

	nsec = ldns_rr_list_rr(nsec3s, 0);
	algorithm = ldns_nsec3_algorithm(nsec);
	salt_length = ldns_nsec3_salt_length(nsec);
	salt = ldns_nsec3_salt_data(nsec);
	iterations = ldns_nsec3_iterations(nsec);
	if (salt == NULL) {
		goto done;
	}

	sname = ldns_rdf_clone(qname);
	if (sname == NULL) {
		goto done;
	}

	flag = false;
	
	zone_name = ldns_dname_left_chop(ldns_rr_owner(nsec));
	if (zone_name == NULL) {
		goto done;
	}

	/* algorithm from nsec3-07 8.3 */
	while (ldns_dname_label_count(sname) > 0) {
		exact_match_found = false;
		in_range_found = false;
		
		if (verbosity >= 3) {
			printf(";; ");
			ldns_rdf_print(stdout, sname);
			printf(" hashes to: ");
		}
		hashed_sname = ldns_nsec3_hash_name(sname, algorithm, iterations, salt_length, salt);
		if (hashed_sname == NULL) {
			goto done;
		}

		if (ldns_dname_cat(hashed_sname, zone_name) != LDNS_STATUS_OK){
			goto done;
		}

		if (verbosity >= 3) {
			ldns_rdf_print(stdout, hashed_sname);
			printf("\n");
		}

		for (nsec_i = 0; nsec_i < ldns_rr_list_rr_count(nsec3s); nsec_i++) {
			nsec = ldns_rr_list_rr(nsec3s, nsec_i);
			
			/* check values of iterations etc! */
			
			/* exact match? */
			if (ldns_dname_compare(ldns_rr_owner(nsec), hashed_sname) == 0) {
				if (verbosity >= 4) {
					printf(";; exact match found\n");
				}
			 	exact_match_found = true;
			} else if (ldns_nsec_covers_name(nsec, hashed_sname)) {
				if (verbosity >= 4) {
					printf(";; in range of an nsec\n");
				}
				in_range_found = true;
			}
			
		}
		if (!exact_match_found && in_range_found) {
			flag = true;
		} else if (exact_match_found && flag) {
			result = ldns_rdf_clone(sname);
		} else if (exact_match_found && !flag) {
			// error!
			if (verbosity >= 4) {
				printf(";; the closest encloser is the same name (ie. this is an exact match, ie there is no closest encloser)\n");
			}
			ldns_rdf_deep_free(hashed_sname);
			goto done;
		} else {
			flag = false;
		}
		
		ldns_rdf_deep_free(hashed_sname);
		tmp = sname;
		sname = ldns_dname_left_chop(sname);
		ldns_rdf_deep_free(tmp);
		if (sname == NULL) {
			goto done;
		}
	}

done:
	LDNS_FREE(salt);
	ldns_rdf_deep_free(zone_name);
	ldns_rdf_deep_free(sname);

	if (!result) {
		if (verbosity >= 4) {
			printf(";; no closest encloser found\n");
		}
	}
	
	/* todo checks from end of 6.2. here or in caller? */
	return result;
}