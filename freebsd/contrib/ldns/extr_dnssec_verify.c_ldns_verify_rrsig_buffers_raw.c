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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_buffer ;

/* Variables and functions */
#define  LDNS_DSA 139 
#define  LDNS_DSA_NSEC3 138 
#define  LDNS_ECC_GOST 137 
#define  LDNS_ECDSAP256SHA256 136 
#define  LDNS_ECDSAP384SHA384 135 
#define  LDNS_ED25519 134 
#define  LDNS_ED448 133 
#define  LDNS_RSAMD5 132 
#define  LDNS_RSASHA1 131 
#define  LDNS_RSASHA1_NSEC3 130 
#define  LDNS_RSASHA256 129 
#define  LDNS_RSASHA512 128 
 int /*<<< orphan*/  LDNS_STATUS_CRYPTO_UNKNOWN_ALGO ; 
 int /*<<< orphan*/  ldns_verify_rrsig_dsa_raw (unsigned char*,size_t,int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  ldns_verify_rrsig_ecdsa_raw (unsigned char*,size_t,int /*<<< orphan*/ *,unsigned char*,size_t,int) ; 
 int /*<<< orphan*/  ldns_verify_rrsig_ed25519_raw (unsigned char*,size_t,int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  ldns_verify_rrsig_ed448_raw (unsigned char*,size_t,int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  ldns_verify_rrsig_gost_raw (unsigned char*,size_t,int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  ldns_verify_rrsig_rsamd5_raw (unsigned char*,size_t,int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  ldns_verify_rrsig_rsasha1_raw (unsigned char*,size_t,int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  ldns_verify_rrsig_rsasha256_raw (unsigned char*,size_t,int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  ldns_verify_rrsig_rsasha512_raw (unsigned char*,size_t,int /*<<< orphan*/ *,unsigned char*,size_t) ; 

ldns_status
ldns_verify_rrsig_buffers_raw(unsigned char* sig, size_t siglen,
						ldns_buffer *verify_buf, unsigned char* key, size_t keylen, 
						uint8_t algo)
{
	/* check for right key */
	switch(algo) {
#ifdef USE_DSA
	case LDNS_DSA:
	case LDNS_DSA_NSEC3:
		return ldns_verify_rrsig_dsa_raw(sig,
								   siglen,
								   verify_buf,
								   key,
								   keylen);
		break;
#endif
	case LDNS_RSASHA1:
	case LDNS_RSASHA1_NSEC3:
		return ldns_verify_rrsig_rsasha1_raw(sig,
									  siglen,
									  verify_buf,
									  key,
									  keylen);
		break;
#ifdef USE_SHA2
	case LDNS_RSASHA256:
		return ldns_verify_rrsig_rsasha256_raw(sig,
									    siglen,
									    verify_buf,
									    key,
									    keylen);
		break;
	case LDNS_RSASHA512:
		return ldns_verify_rrsig_rsasha512_raw(sig,
									    siglen,
									    verify_buf,
									    key,
									    keylen);
		break;
#endif
#ifdef USE_GOST
	case LDNS_ECC_GOST:
		return ldns_verify_rrsig_gost_raw(sig, siglen, verify_buf,
			key, keylen);
		break;
#endif
#ifdef USE_ECDSA
        case LDNS_ECDSAP256SHA256:
        case LDNS_ECDSAP384SHA384:
		return ldns_verify_rrsig_ecdsa_raw(sig, siglen, verify_buf,
			key, keylen, algo);
		break;
#endif
#ifdef USE_ED25519
	case LDNS_ED25519:
		return ldns_verify_rrsig_ed25519_raw(sig, siglen, verify_buf,
			key, keylen);
		break;
#endif
#ifdef USE_ED448
	case LDNS_ED448:
		return ldns_verify_rrsig_ed448_raw(sig, siglen, verify_buf,
			key, keylen);
		break;
#endif
	case LDNS_RSAMD5:
		return ldns_verify_rrsig_rsamd5_raw(sig,
									 siglen,
									 verify_buf,
									 key,
									 keylen);
		break;
	default:
		/* do you know this alg?! */
		return LDNS_STATUS_CRYPTO_UNKNOWN_ALGO;
	}
}