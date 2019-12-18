#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int ldns_rr_type ;
typedef  int /*<<< orphan*/  ldns_rr_list ;
struct TYPE_3__ {char* _name; } ;
typedef  TYPE_1__ ldns_rr_descriptor ;
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_rdf ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_FREE (int /*<<< orphan*/ *) ; 
 scalar_t__ LDNS_STATUS_OK ; 
 scalar_t__ ldns_dname_cat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_dname_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_dname_left_chop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_nsec3_algorithm (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_nsec3_hash_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_nsec3_iterations (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_nsec3_salt_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_nsec3_salt_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rdf_clone (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rdf_deep_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rdf_print (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* ldns_rr_descript (int) ; 
 int /*<<< orphan*/ * ldns_rr_list_rr (int /*<<< orphan*/ *,size_t) ; 
 size_t ldns_rr_list_rr_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_owner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 
 int verbosity ; 

ldns_rr *
ldns_nsec3_exact_match(ldns_rdf *qname, ldns_rr_type qtype, ldns_rr_list *nsec3s) {
	uint8_t algorithm;
	uint32_t iterations;
	uint8_t salt_length;
	uint8_t *salt;
	
	ldns_rdf *sname = NULL, *hashed_sname = NULL;
	
	size_t nsec_i;
	ldns_rr *nsec;
	ldns_rr *result = NULL;
	
	const ldns_rr_descriptor *descriptor;
	
	ldns_rdf *zone_name = NULL;
	
	if (verbosity >= 4) {
		printf(";; finding exact match for ");
		descriptor = ldns_rr_descript(qtype);
		if (descriptor && descriptor->_name) {
			printf("%s ", descriptor->_name);
		} else {
			printf("TYPE%d ", qtype);
		}
		ldns_rdf_print(stdout, qname);
		printf("\n");
	}
	
	if (!qname || !nsec3s || ldns_rr_list_rr_count(nsec3s) < 1) {
		if (verbosity >= 4) {
			printf("no qname, nsec3s or list empty\n");
		}
		return NULL;
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
	if (verbosity >= 4) {
		printf(";; owner name hashes to: ");
	}
	hashed_sname = ldns_nsec3_hash_name(sname, algorithm, iterations, salt_length, salt);
	if (hashed_sname == NULL) {
		goto done;
	}
	zone_name = ldns_dname_left_chop(ldns_rr_owner(nsec));
	if (zone_name == NULL) {
		goto done;
	}
	if (ldns_dname_cat(hashed_sname, zone_name) != LDNS_STATUS_OK) {
		goto done;
	};
	
	if (verbosity >= 4) {
		ldns_rdf_print(stdout, hashed_sname);
		printf("\n");
	}

	for (nsec_i = 0; nsec_i < ldns_rr_list_rr_count(nsec3s); nsec_i++) {
		nsec = ldns_rr_list_rr(nsec3s, nsec_i);
		
		/* check values of iterations etc! */
		
		/* exact match? */
		if (ldns_dname_compare(ldns_rr_owner(nsec), hashed_sname) == 0) {
			result = nsec;
			goto done;
		}
		
	}

done:
	ldns_rdf_deep_free(zone_name);
	ldns_rdf_deep_free(sname);
	ldns_rdf_deep_free(hashed_sname);
	LDNS_FREE(salt);
	
	if (verbosity >= 4) {
		if (result) {
			printf(";; Found.\n");
		} else {
			printf(";; Not foud.\n");
		}
	}
	return result;
}