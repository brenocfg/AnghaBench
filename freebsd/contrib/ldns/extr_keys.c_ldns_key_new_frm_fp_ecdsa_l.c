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
typedef  int /*<<< orphan*/  token ;
typedef  int /*<<< orphan*/  ldns_rdf ;
typedef  scalar_t__ ldns_algorithm ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EC_KEY ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/ * BN_bin2bn (unsigned char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_KEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_KEY_new_by_curve_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_KEY_set_private_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_assign_EC_KEY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_new () ; 
 scalar_t__ LDNS_ECDSAP256SHA256 ; 
 scalar_t__ LDNS_ECDSAP384SHA384 ; 
 scalar_t__ LDNS_STATUS_OK ; 
 int /*<<< orphan*/  NID_X9_62_prime256v1 ; 
 int /*<<< orphan*/  NID_secp384r1 ; 
 int /*<<< orphan*/  ldns_EC_KEY_calc_public (int /*<<< orphan*/ *) ; 
 int ldns_fget_keyword_data_l (int /*<<< orphan*/ *,char*,char*,char*,char*,int,int*) ; 
 scalar_t__ ldns_rdf_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rdf_deep_free (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_rdf_size (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_str2rdf_b64 (int /*<<< orphan*/ **,char*) ; 

__attribute__((used)) static EVP_PKEY*
ldns_key_new_frm_fp_ecdsa_l(FILE* fp, ldns_algorithm alg, int* line_nr)
{
	char token[16384];
        ldns_rdf* b64rdf = NULL;
        unsigned char* pp;
        BIGNUM* bn;
        EVP_PKEY* evp_key;
        EC_KEY* ec;
	if (ldns_fget_keyword_data_l(fp, "PrivateKey", ": ", token, "\n",
		sizeof(token), line_nr) == -1)
		return NULL;
	if(ldns_str2rdf_b64(&b64rdf, token) != LDNS_STATUS_OK)
		return NULL;
        pp = (unsigned char*)ldns_rdf_data(b64rdf);

        if(alg == LDNS_ECDSAP256SHA256)
                ec = EC_KEY_new_by_curve_name(NID_X9_62_prime256v1);
        else if(alg == LDNS_ECDSAP384SHA384)
                ec = EC_KEY_new_by_curve_name(NID_secp384r1);
        else    ec = NULL;
        if(!ec) {
	        ldns_rdf_deep_free(b64rdf);
                return NULL;
        }
	bn = BN_bin2bn(pp, (int)ldns_rdf_size(b64rdf), NULL);
	ldns_rdf_deep_free(b64rdf);
        if(!bn) {
                EC_KEY_free(ec);
                return NULL;
        }
        EC_KEY_set_private_key(ec, bn);
        BN_free(bn);
        if(!ldns_EC_KEY_calc_public(ec)) {
                EC_KEY_free(ec);
                return NULL;
        }

        evp_key = EVP_PKEY_new();
        if(!evp_key) {
                EC_KEY_free(ec);
                return NULL;
        }
        if (!EVP_PKEY_assign_EC_KEY(evp_key, ec)) {
		EVP_PKEY_free(evp_key);
                EC_KEY_free(ec);
                return NULL;
	}
        return evp_key;
}