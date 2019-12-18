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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ time_t ;
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_rr_class ;
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_rdf ;
typedef  int /*<<< orphan*/  ldns_key ;

/* Variables and functions */
 scalar_t__ LDNS_DEFAULT_EXP_TIME ; 
 int /*<<< orphan*/  LDNS_RDF_TYPE_ALG ; 
 int /*<<< orphan*/  LDNS_RDF_TYPE_INT16 ; 
 int /*<<< orphan*/  LDNS_RDF_TYPE_INT32 ; 
 int /*<<< orphan*/  LDNS_RDF_TYPE_INT8 ; 
 int /*<<< orphan*/  LDNS_RDF_TYPE_TIME ; 
 int /*<<< orphan*/  LDNS_RDF_TYPE_TYPE ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_RRSIG ; 
 int /*<<< orphan*/  ldns_dname2canonical (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_dname_is_wildcard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_dname_label_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_key_algorithm (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_key_expiration (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_key_inception (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_key_keytag (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_key_pubkey_owner (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_native2rdf_int16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_native2rdf_int32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ldns_native2rdf_int8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ldns_rdf_clone (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_get_class (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_get_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_list_rr (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ldns_rr_new_frm_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_owner (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_rrsig_set_algorithm (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_rrsig_set_expiration (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_rrsig_set_inception (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_rrsig_set_keytag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_rrsig_set_labels (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_rrsig_set_origttl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_rrsig_set_signame (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_rrsig_set_typecovered (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_set_class (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_set_owner (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_set_ttl (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ldns_rr_ttl (int /*<<< orphan*/ ) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

ldns_rr *
ldns_create_empty_rrsig(const ldns_rr_list *rrset,
                        const ldns_key *current_key)
{
	uint32_t orig_ttl;
	ldns_rr_class orig_class;
	time_t now;
	ldns_rr *current_sig;
	uint8_t label_count;
	ldns_rdf *signame;

	label_count = ldns_dname_label_count(ldns_rr_owner(ldns_rr_list_rr(rrset,
	                                                   0)));
        /* RFC4035 2.2: not counting the leftmost label if it is a wildcard */
        if(ldns_dname_is_wildcard(ldns_rr_owner(ldns_rr_list_rr(rrset, 0))))
                label_count --;

	current_sig = ldns_rr_new_frm_type(LDNS_RR_TYPE_RRSIG);

	/* set the type on the new signature */
	orig_ttl = ldns_rr_ttl(ldns_rr_list_rr(rrset, 0));
	orig_class = ldns_rr_get_class(ldns_rr_list_rr(rrset, 0));

	ldns_rr_set_ttl(current_sig, orig_ttl);
	ldns_rr_set_class(current_sig, orig_class);
	ldns_rr_set_owner(current_sig,
			  ldns_rdf_clone(
			       ldns_rr_owner(
				    ldns_rr_list_rr(rrset,
						    0))));

	/* fill in what we know of the signature */

	/* set the orig_ttl */
	(void)ldns_rr_rrsig_set_origttl(
		   current_sig,
		   ldns_native2rdf_int32(LDNS_RDF_TYPE_INT32,
					 orig_ttl));
	/* the signers name */
	signame = ldns_rdf_clone(ldns_key_pubkey_owner(current_key));
	ldns_dname2canonical(signame);
	(void)ldns_rr_rrsig_set_signame(
			current_sig,
			signame);
	/* label count - get it from the first rr in the rr_list */
	(void)ldns_rr_rrsig_set_labels(
			current_sig,
			ldns_native2rdf_int8(LDNS_RDF_TYPE_INT8,
			                     label_count));
	/* inception, expiration */
	now = time(NULL);
	if (ldns_key_inception(current_key) != 0) {
		(void)ldns_rr_rrsig_set_inception(
				current_sig,
				ldns_native2rdf_int32(
				    LDNS_RDF_TYPE_TIME,
				    ldns_key_inception(current_key)));
	} else {
		(void)ldns_rr_rrsig_set_inception(
				current_sig,
				ldns_native2rdf_int32(LDNS_RDF_TYPE_TIME, now));
	}
	if (ldns_key_expiration(current_key) != 0) {
		(void)ldns_rr_rrsig_set_expiration(
				current_sig,
				ldns_native2rdf_int32(
				    LDNS_RDF_TYPE_TIME,
				    ldns_key_expiration(current_key)));
	} else {
		(void)ldns_rr_rrsig_set_expiration(
			     current_sig,
				ldns_native2rdf_int32(
				    LDNS_RDF_TYPE_TIME,
				    now + LDNS_DEFAULT_EXP_TIME));
	}

	(void)ldns_rr_rrsig_set_keytag(
		   current_sig,
		   ldns_native2rdf_int16(LDNS_RDF_TYPE_INT16,
		                         ldns_key_keytag(current_key)));

	(void)ldns_rr_rrsig_set_algorithm(
			current_sig,
			ldns_native2rdf_int8(
			    LDNS_RDF_TYPE_ALG,
			    ldns_key_algorithm(current_key)));

	(void)ldns_rr_rrsig_set_typecovered(
			current_sig,
			ldns_native2rdf_int16(
			    LDNS_RDF_TYPE_TYPE,
			    ldns_rr_get_type(ldns_rr_list_rr(rrset,
			                                     0))));
	return current_sig;
}