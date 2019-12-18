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
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_rr_type ;
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_rdf ;
typedef  int /*<<< orphan*/  ldns_pkt ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_TYPE_NSEC ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_NSEC3 ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_RRSIG ; 
 int /*<<< orphan*/  LDNS_SECTION_ANY_NOQUESTION ; 
 int /*<<< orphan*/  LDNS_STATUS_CRYPTO_NO_RRSIG ; 
 int /*<<< orphan*/  LDNS_STATUS_ERR ; 
 int /*<<< orphan*/  LDNS_STATUS_MEM_ERR ; 
 int /*<<< orphan*/  LDNS_STATUS_OK ; 
 int /*<<< orphan*/  get_dnssec_rr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 scalar_t__ ldns_dname_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_dnssec_verify_denial_nsec3_match (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 scalar_t__ ldns_nsec_bitmap_covers_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_nsec_covers_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_nsec_get_bitmap (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_pkt_ancount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_pkt_get_rcode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_pkt_print (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_pkt_rr_list_by_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rdf_clone (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_list_deep_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_list_rr (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ldns_rr_list_rr_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_new () ; 
 int /*<<< orphan*/  ldns_rr_owner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_set_owner (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_set_question (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ldns_rr_set_ttl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_set_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stdout ; 
 int verbosity ; 

ldns_status
ldns_verify_denial(ldns_pkt *pkt, ldns_rdf *name, ldns_rr_type type, ldns_rr_list **nsec_rrs, ldns_rr_list **nsec_rr_sigs)
{
#ifdef HAVE_SSL
	uint16_t nsec_i;

	ldns_rr_list *nsecs;
	ldns_status result;
	
	if (verbosity >= 5) {
		printf("VERIFY DENIAL FROM:\n");
		ldns_pkt_print(stdout, pkt);
	}

	result = LDNS_STATUS_CRYPTO_NO_RRSIG;
	/* Try to see if there are NSECS in the packet */
	nsecs = ldns_pkt_rr_list_by_type(pkt, LDNS_RR_TYPE_NSEC, LDNS_SECTION_ANY_NOQUESTION);
	if (nsecs) {
		for (nsec_i = 0; nsec_i < ldns_rr_list_rr_count(nsecs); nsec_i++) {
			/* there are four options:
			 * - name equals ownername and is covered by the type bitmap
			 * - name equals ownername but is not covered by the type bitmap
			 * - name falls within nsec coverage but is not equal to the owner name
			 * - name falls outside of nsec coverage
			 */
			if (ldns_dname_compare(ldns_rr_owner(ldns_rr_list_rr(nsecs, nsec_i)), name) == 0) {
				/*
				printf("CHECKING NSEC:\n");
				ldns_rr_print(stdout, ldns_rr_list_rr(nsecs, nsec_i));
				printf("DAWASEM\n");
				*/
				if (ldns_nsec_bitmap_covers_type(
					   ldns_nsec_get_bitmap(ldns_rr_list_rr(nsecs,
													nsec_i)),
					   type)) {
					/* Error, according to the nsec this rrset is signed */
					result = LDNS_STATUS_CRYPTO_NO_RRSIG;
				} else {
					/* ok nsec denies existence */
					if (verbosity >= 3) {
						printf(";; Existence of data set with this type denied by NSEC\n");
					}
						/*printf(";; Verifiably insecure.\n");*/
						if (nsec_rrs && nsec_rr_sigs) {
							(void) get_dnssec_rr(pkt, ldns_rr_owner(ldns_rr_list_rr(nsecs, nsec_i)), LDNS_RR_TYPE_NSEC, nsec_rrs, nsec_rr_sigs);
						}
						ldns_rr_list_deep_free(nsecs);
						return LDNS_STATUS_OK;
				}
			} else if (ldns_nsec_covers_name(ldns_rr_list_rr(nsecs, nsec_i), name)) {
				if (verbosity >= 3) {
					printf(";; Existence of data set with this name denied by NSEC\n");
				}
				if (nsec_rrs && nsec_rr_sigs) {
					(void) get_dnssec_rr(pkt, ldns_rr_owner(ldns_rr_list_rr(nsecs, nsec_i)), LDNS_RR_TYPE_NSEC, nsec_rrs, nsec_rr_sigs);
				}
				ldns_rr_list_deep_free(nsecs);
				return LDNS_STATUS_OK;
			} else {
				/* nsec has nothing to do with this data */
			}
		}
		ldns_rr_list_deep_free(nsecs);
	} else if( (nsecs = ldns_pkt_rr_list_by_type(pkt, LDNS_RR_TYPE_NSEC3, LDNS_SECTION_ANY_NOQUESTION)) ) {
                ldns_rr_list* sigs = ldns_pkt_rr_list_by_type(pkt, LDNS_RR_TYPE_RRSIG, LDNS_SECTION_ANY_NOQUESTION);
                ldns_rr* q = ldns_rr_new();
		ldns_rr* match = NULL;

                if(!sigs) {
			if (q) {
                		ldns_rr_free(q);
			}
			ldns_rr_list_deep_free(nsecs);
			return LDNS_STATUS_MEM_ERR;
		}
                if(!q) {
			ldns_rr_list_deep_free(nsecs);
			ldns_rr_list_deep_free(sigs);
			return LDNS_STATUS_MEM_ERR;
		}
                ldns_rr_set_question(q, 1);
                ldns_rr_set_ttl(q, 0);
                ldns_rr_set_owner(q, ldns_rdf_clone(name));
                if(!ldns_rr_owner(q)) {
                	ldns_rr_free(q);
			ldns_rr_list_deep_free(sigs);
			ldns_rr_list_deep_free(nsecs);
			return LDNS_STATUS_MEM_ERR;
		}
                ldns_rr_set_type(q, type);
                
                /* result = ldns_dnssec_verify_denial_nsec3(q, nsecs, sigs, ldns_pkt_get_rcode(pkt), type, ldns_pkt_ancount(pkt) == 0); */
                result = ldns_dnssec_verify_denial_nsec3_match(q, nsecs, sigs, ldns_pkt_get_rcode(pkt), type, ldns_pkt_ancount(pkt) == 0, &match);
		if (result == LDNS_STATUS_OK && match && nsec_rrs && nsec_rr_sigs) {
			(void) get_dnssec_rr(pkt, ldns_rr_owner(match), LDNS_RR_TYPE_NSEC3, nsec_rrs, nsec_rr_sigs);
		}
                ldns_rr_free(q);
		ldns_rr_list_deep_free(nsecs);
		ldns_rr_list_deep_free(sigs);
        }
	return result;
#else
	(void)pkt;
	(void)name;
	(void)type;
	(void)nsec_rrs;
	(void)nsec_rr_sigs;
	return LDNS_STATUS_ERR;
#endif /* HAVE_SSL */
}