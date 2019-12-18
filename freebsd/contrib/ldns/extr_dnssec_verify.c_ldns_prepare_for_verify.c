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
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_buffer ;

/* Variables and functions */
 scalar_t__ LDNS_STATUS_CRYPTO_TYPE_COVERED_ERR ; 
 scalar_t__ LDNS_STATUS_MEM_ERR ; 
 scalar_t__ LDNS_STATUS_OK ; 
 int /*<<< orphan*/  ldns_dname2canonical (int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_rdf2rr_type (int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_rr_get_type (int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_rr_list2buffer_wire (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_list_rr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_list_sort (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_owner (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rr_rrsig_typecovered (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rrset_use_signature_ttl (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_rrsig2buffer_wire (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_rrsig2rawsig_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static ldns_status
ldns_prepare_for_verify(ldns_buffer* rawsig_buf, ldns_buffer* verify_buf, 
	ldns_rr_list* rrset_clone, const ldns_rr* rrsig)
{
	ldns_status result;

	/* canonicalize the sig */
	ldns_dname2canonical(ldns_rr_owner(rrsig));
	
	/* check if the typecovered is equal to the type checked */
	if (ldns_rdf2rr_type(ldns_rr_rrsig_typecovered(rrsig)) !=
	    ldns_rr_get_type(ldns_rr_list_rr(rrset_clone, 0)))
		return LDNS_STATUS_CRYPTO_TYPE_COVERED_ERR;
	
	/* create a buffer with b64 signature rdata */
	result = ldns_rrsig2rawsig_buffer(rawsig_buf, rrsig);
	if(result != LDNS_STATUS_OK)
		return result;

	/* use TTL from signature. Use wildcard names for wildcards */
	/* also canonicalizes rrset_clone */
	ldns_rrset_use_signature_ttl(rrset_clone, rrsig);

	/* sort the rrset in canonical order  */
	ldns_rr_list_sort(rrset_clone);

	/* put the signature rr (without the b64) to the verify_buf */
	if (ldns_rrsig2buffer_wire(verify_buf, rrsig) != LDNS_STATUS_OK)
		return LDNS_STATUS_MEM_ERR;

	/* add the rrset in verify_buf */
	if(ldns_rr_list2buffer_wire(verify_buf, rrset_clone) 
		!= LDNS_STATUS_OK)
		return LDNS_STATUS_MEM_ERR;

	return LDNS_STATUS_OK;
}