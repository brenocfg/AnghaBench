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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EC_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  EC_KEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_KEY_new_by_curve_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_PKEY_assign_EC_KEY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_new () ; 
 scalar_t__ LDNS_ECDSAP256SHA256 ; 
 scalar_t__ LDNS_ECDSAP384SHA384 ; 
 int /*<<< orphan*/  NID_X9_62_prime256v1 ; 
 int /*<<< orphan*/  NID_secp384r1 ; 
 unsigned char POINT_CONVERSION_UNCOMPRESSED ; 
 int /*<<< orphan*/  memmove (unsigned char*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  o2i_ECPublicKey (int /*<<< orphan*/ **,unsigned char const**,int) ; 

EVP_PKEY*
ldns_ecdsa2pkey_raw(const unsigned char* key, size_t keylen, uint8_t algo)
{
	unsigned char buf[256+2]; /* sufficient for 2*384/8+1 */
        const unsigned char* pp = buf;
        EVP_PKEY *evp_key;
        EC_KEY *ec;
	/* check length, which uncompressed must be 2 bignums */
        if(algo == LDNS_ECDSAP256SHA256) {
		if(keylen != 2*256/8) return NULL;
                ec = EC_KEY_new_by_curve_name(NID_X9_62_prime256v1);
        } else if(algo == LDNS_ECDSAP384SHA384) {
		if(keylen != 2*384/8) return NULL;
                ec = EC_KEY_new_by_curve_name(NID_secp384r1);
        } else    ec = NULL;
        if(!ec) return NULL;
	if(keylen+1 > sizeof(buf))
		return NULL; /* sanity check */
	/* prepend the 0x02 (from docs) (or actually 0x04 from implementation
	 * of openssl) for uncompressed data */
	buf[0] = POINT_CONVERSION_UNCOMPRESSED;
	memmove(buf+1, key, keylen);
        if(!o2i_ECPublicKey(&ec, &pp, (int)keylen+1)) {
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