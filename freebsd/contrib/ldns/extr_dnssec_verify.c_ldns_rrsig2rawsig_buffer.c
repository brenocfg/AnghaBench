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
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_buffer ;

/* Variables and functions */
#define  LDNS_DH 142 
#define  LDNS_DSA 141 
#define  LDNS_DSA_NSEC3 140 
#define  LDNS_ECC 139 
#define  LDNS_ECC_GOST 138 
#define  LDNS_ECDSAP256SHA256 137 
#define  LDNS_ECDSAP384SHA384 136 
#define  LDNS_ED25519 135 
#define  LDNS_ED448 134 
#define  LDNS_INDIRECT 133 
#define  LDNS_RSAMD5 132 
#define  LDNS_RSASHA1 131 
#define  LDNS_RSASHA1_NSEC3 130 
#define  LDNS_RSASHA256 129 
#define  LDNS_RSASHA512 128 
 int /*<<< orphan*/  LDNS_STATUS_CRYPTO_ALGO_NOT_IMPL ; 
 int /*<<< orphan*/  LDNS_STATUS_CRYPTO_NO_RRSIG ; 
 int /*<<< orphan*/  LDNS_STATUS_CRYPTO_UNKNOWN_ALGO ; 
 int /*<<< orphan*/  LDNS_STATUS_MEM_ERR ; 
 int /*<<< orphan*/  LDNS_STATUS_MISSING_RDATA_FIELDS_RRSIG ; 
 int /*<<< orphan*/  LDNS_STATUS_OK ; 
 int /*<<< orphan*/  ldns_convert_dsa_rrsig_rdf2asn1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_convert_ecdsa_rrsig_rdf2asn1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_convert_ed25519_rrsig_rdf2asn1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_convert_ed448_rrsig_rdf2asn1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rdf2buffer_wire (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ldns_rdf2native_int8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_rdf (int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static ldns_status
ldns_rrsig2rawsig_buffer(ldns_buffer* rawsig_buf, const ldns_rr* rrsig)
{
	uint8_t sig_algo;
       
	if (rrsig == NULL) {
		return LDNS_STATUS_CRYPTO_NO_RRSIG;
	}
	if (ldns_rr_rdf(rrsig, 1) == NULL) {
		return LDNS_STATUS_MISSING_RDATA_FIELDS_RRSIG;
	}
	sig_algo = ldns_rdf2native_int8(ldns_rr_rdf(rrsig, 1));
	/* check for known and implemented algo's now (otherwise 
	 * the function could return a wrong error
	 */
	/* create a buffer with signature rdata */
	/* for some algorithms we need other data than for others... */
	/* (the DSA API wants DER encoding for instance) */

	switch(sig_algo) {
	case LDNS_RSAMD5:
	case LDNS_RSASHA1:
	case LDNS_RSASHA1_NSEC3:
#ifdef USE_SHA2
	case LDNS_RSASHA256:
	case LDNS_RSASHA512:
#endif
#ifdef USE_GOST
	case LDNS_ECC_GOST:
#endif
		if (ldns_rr_rdf(rrsig, 8) == NULL) {
			return LDNS_STATUS_MISSING_RDATA_FIELDS_RRSIG;
		}
		if (ldns_rdf2buffer_wire(rawsig_buf, ldns_rr_rdf(rrsig, 8))
			       	!= LDNS_STATUS_OK) {
			return LDNS_STATUS_MEM_ERR;
		}
		break;
#ifdef USE_DSA
	case LDNS_DSA:
	case LDNS_DSA_NSEC3:
		/* EVP takes rfc2459 format, which is a tad longer than dns format */
		if (ldns_rr_rdf(rrsig, 8) == NULL) {
			return LDNS_STATUS_MISSING_RDATA_FIELDS_RRSIG;
		}
		if (ldns_convert_dsa_rrsig_rdf2asn1(
					rawsig_buf, ldns_rr_rdf(rrsig, 8)) 
				!= LDNS_STATUS_OK) {
			/*
			  if (ldns_rdf2buffer_wire(rawsig_buf,
			  ldns_rr_rdf(rrsig, 8)) != LDNS_STATUS_OK) {
			*/
			return LDNS_STATUS_MEM_ERR;
		}
		break;
#endif
#ifdef USE_ECDSA
        case LDNS_ECDSAP256SHA256:
        case LDNS_ECDSAP384SHA384:
                /* EVP produces an ASN prefix on the signature, which is
                 * not used in the DNS */
		if (ldns_rr_rdf(rrsig, 8) == NULL) {
			return LDNS_STATUS_MISSING_RDATA_FIELDS_RRSIG;
		}
		if (ldns_convert_ecdsa_rrsig_rdf2asn1(
					rawsig_buf, ldns_rr_rdf(rrsig, 8))
				!= LDNS_STATUS_OK) {
			return LDNS_STATUS_MEM_ERR;
                }
                break;
#endif
#ifdef USE_ED25519
	case LDNS_ED25519:
                /* EVP produces an ASN prefix on the signature, which is
                 * not used in the DNS */
		if (ldns_rr_rdf(rrsig, 8) == NULL) {
			return LDNS_STATUS_MISSING_RDATA_FIELDS_RRSIG;
		}
		if (ldns_convert_ed25519_rrsig_rdf2asn1(
			rawsig_buf, ldns_rr_rdf(rrsig, 8)) != LDNS_STATUS_OK) {
			return LDNS_STATUS_MEM_ERR;
                }
		break;
#endif
#ifdef USE_ED448
	case LDNS_ED448:
                /* EVP produces an ASN prefix on the signature, which is
                 * not used in the DNS */
		if (ldns_rr_rdf(rrsig, 8) == NULL) {
			return LDNS_STATUS_MISSING_RDATA_FIELDS_RRSIG;
		}
		if (ldns_convert_ed448_rrsig_rdf2asn1(
			rawsig_buf, ldns_rr_rdf(rrsig, 8)) != LDNS_STATUS_OK) {
			return LDNS_STATUS_MEM_ERR;
                }
		break;
#endif
	case LDNS_DH:
	case LDNS_ECC:
	case LDNS_INDIRECT:
		return LDNS_STATUS_CRYPTO_ALGO_NOT_IMPL;
	default:
		return LDNS_STATUS_CRYPTO_UNKNOWN_ALGO;
	}
	return LDNS_STATUS_OK;
}