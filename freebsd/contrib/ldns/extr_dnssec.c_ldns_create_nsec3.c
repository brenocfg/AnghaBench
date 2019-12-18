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
typedef  scalar_t__ uint16_t ;
typedef  scalar_t__ ldns_status ;
typedef  scalar_t__ ldns_rr_type ;
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_rdf ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_TYPE_NSEC3 ; 
 scalar_t__ LDNS_RR_TYPE_RRSIG ; 
 scalar_t__ LDNS_RR_TYPE_SOA ; 
 scalar_t__ LDNS_STATUS_OK ; 
 scalar_t__ ldns_dname_cat (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_dname_compare (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_dnssec_create_nsec_bitmap (scalar_t__*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_nsec3_add_param_rdfs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * ldns_nsec3_hash_name (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_rdf_compare (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rdf_deep_free (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_rr_get_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_list_rr (int /*<<< orphan*/  const*,size_t) ; 
 size_t ldns_rr_list_rr_count (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * ldns_rr_new_frm_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_owner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_push_rdf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_set_owner (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_set_rdf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ldns_rr_set_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rr_list_delegation_only (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

ldns_rr *
ldns_create_nsec3(const ldns_rdf *cur_owner,
                  const ldns_rdf *cur_zone,
                  const ldns_rr_list *rrs,
                  uint8_t algorithm,
                  uint8_t flags,
                  uint16_t iterations,
                  uint8_t salt_length,
                  const uint8_t *salt,
                  bool emptynonterminal)
{
	size_t i;
	ldns_rr *i_rr;
	uint16_t i_type;

	ldns_rr *nsec = NULL;
	ldns_rdf *hashed_owner = NULL;

	ldns_status status;

    ldns_rr_type i_type_list[1024];
	size_t type_count = 0;

	hashed_owner = ldns_nsec3_hash_name(cur_owner,
								 algorithm,
								 iterations,
								 salt_length,
								 salt);
	status = ldns_dname_cat(hashed_owner, cur_zone);
        if(status != LDNS_STATUS_OK) {
		ldns_rdf_deep_free(hashed_owner);
                return NULL;
	}
	nsec = ldns_rr_new_frm_type(LDNS_RR_TYPE_NSEC3);
        if(!nsec) {
		ldns_rdf_deep_free(hashed_owner);
                return NULL;
	}
	ldns_rr_set_type(nsec, LDNS_RR_TYPE_NSEC3);
	ldns_rr_set_owner(nsec, hashed_owner);

	ldns_nsec3_add_param_rdfs(nsec,
						 algorithm,
						 flags,
						 iterations,
						 salt_length,
						 salt);
	(void) ldns_rr_set_rdf(nsec, NULL, 4);


	for (i = 0; i < ldns_rr_list_rr_count(rrs); i++) {
		i_rr = ldns_rr_list_rr(rrs, i);
		if (ldns_rdf_compare(cur_owner,
						 ldns_rr_owner(i_rr)) == 0) {
			i_type = ldns_rr_get_type(i_rr);
			if (type_count == 0 || i_type_list[type_count-1] != i_type) {
				i_type_list[type_count] = i_type;
				type_count++;
			}
		}
	}

	/* add RRSIG anyway, but only if this is not an ENT or
	 * an unsigned delegation */
	if (!emptynonterminal && !rr_list_delegation_only(cur_zone, rrs)) {
		i_type_list[type_count] = LDNS_RR_TYPE_RRSIG;
		type_count++;
	}

	/* and SOA if owner == zone */
	if (ldns_dname_compare(cur_zone, cur_owner) == 0) {
		i_type_list[type_count] = LDNS_RR_TYPE_SOA;
		type_count++;
	}

	ldns_rr_push_rdf(nsec,
				  ldns_dnssec_create_nsec_bitmap(i_type_list,
						type_count, LDNS_RR_TYPE_NSEC3));

	return nsec;
}