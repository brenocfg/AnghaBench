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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_rdf ;

/* Variables and functions */
 int /*<<< orphan*/  ldns_dname_cat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_dname_label_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_dname_left_chop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rdf2native_int32 (int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_rdf2native_int8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ldns_rdf_clone (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rdf_deep_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr2canonical (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_list_rr (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ldns_rr_list_rr_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_owner (int /*<<< orphan*/ ) ; 
 int ldns_rr_rd_count (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rr_rdf (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  ldns_rr_set_owner (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_set_ttl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_str2rdf_dname (int /*<<< orphan*/ **,char*) ; 

__attribute__((used)) static void
ldns_rrset_use_signature_ttl(ldns_rr_list* rrset_clone, const ldns_rr* rrsig)
{
	uint32_t orig_ttl;
	uint16_t i;
	uint8_t label_count;
	ldns_rdf *wildcard_name;
	ldns_rdf *wildcard_chopped;
	ldns_rdf *wildcard_chopped_tmp;
	
	if ((rrsig == NULL) || ldns_rr_rd_count(rrsig) < 4) {
		return;
	}

	orig_ttl = ldns_rdf2native_int32( ldns_rr_rdf(rrsig, 3));
	label_count = ldns_rdf2native_int8(ldns_rr_rdf(rrsig, 2));

	for(i = 0; i < ldns_rr_list_rr_count(rrset_clone); i++) {
		if (label_count < 
		    ldns_dname_label_count(
			   ldns_rr_owner(ldns_rr_list_rr(rrset_clone, i)))) {
			(void) ldns_str2rdf_dname(&wildcard_name, "*");
			wildcard_chopped = ldns_rdf_clone(ldns_rr_owner(
				ldns_rr_list_rr(rrset_clone, i)));
			while (label_count < ldns_dname_label_count(wildcard_chopped)) {
				wildcard_chopped_tmp = ldns_dname_left_chop(
					wildcard_chopped);
				ldns_rdf_deep_free(wildcard_chopped);
				wildcard_chopped = wildcard_chopped_tmp;
			}
			(void) ldns_dname_cat(wildcard_name, wildcard_chopped);
			ldns_rdf_deep_free(wildcard_chopped);
			ldns_rdf_deep_free(ldns_rr_owner(ldns_rr_list_rr(
				rrset_clone, i)));
			ldns_rr_set_owner(ldns_rr_list_rr(rrset_clone, i), 
				wildcard_name);
		}
		ldns_rr_set_ttl(ldns_rr_list_rr(rrset_clone, i), orig_ttl);
		/* convert to lowercase */
		ldns_rr2canonical(ldns_rr_list_rr(rrset_clone, i));
	}
}