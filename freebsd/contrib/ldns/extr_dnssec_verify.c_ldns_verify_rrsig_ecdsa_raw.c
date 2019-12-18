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
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_buffer ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_sha256 () ; 
 int /*<<< orphan*/ * EVP_sha384 () ; 
 scalar_t__ LDNS_ECDSAP256SHA256 ; 
 int /*<<< orphan*/  LDNS_STATUS_CRYPTO_BOGUS ; 
 int /*<<< orphan*/ * ldns_ecdsa2pkey_raw (unsigned char*,size_t,scalar_t__) ; 
 int /*<<< orphan*/  ldns_verify_rrsig_evp_raw (unsigned char*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static ldns_status
ldns_verify_rrsig_ecdsa_raw(unsigned char* sig, size_t siglen, 
	ldns_buffer* rrset, unsigned char* key, size_t keylen, uint8_t algo)
{
        EVP_PKEY *evp_key;
        ldns_status result;
        const EVP_MD *d;

        evp_key = ldns_ecdsa2pkey_raw(key, keylen, algo);
        if(!evp_key) {
		/* could not convert key */
		return LDNS_STATUS_CRYPTO_BOGUS;
        }
        if(algo == LDNS_ECDSAP256SHA256)
                d = EVP_sha256();
        else    d = EVP_sha384(); /* LDNS_ECDSAP384SHA384 */
	result = ldns_verify_rrsig_evp_raw(sig, siglen, rrset, evp_key, d);
	EVP_PKEY_free(evp_key);
	return result;
}