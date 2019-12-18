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
typedef  unsigned char uint16_t ;
typedef  int /*<<< orphan*/  sldns_algorithm ;

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
 int /*<<< orphan*/  memmove (unsigned char*,unsigned char const*,int) ; 
 unsigned char ntohs (unsigned char) ; 

size_t
sldns_rr_dnskey_key_size_raw(const unsigned char* keydata,
	const size_t len, int alg)
{
	/* for DSA keys */
	uint8_t t;
	
	/* for RSA keys */
	uint16_t exp;
	uint16_t int16;
	
	switch ((sldns_algorithm)alg) {
	case LDNS_DSA:
	case LDNS_DSA_NSEC3:
		if (len > 0) {
			t = keydata[0];
			return (64 + t*8)*8;
		} else {
			return 0;
		}
		break;
	case LDNS_RSAMD5:
	case LDNS_RSASHA1:
	case LDNS_RSASHA1_NSEC3:
#ifdef USE_SHA2
	case LDNS_RSASHA256:
	case LDNS_RSASHA512:
#endif
		if (len > 0) {
			if (keydata[0] == 0) {
				/* big exponent */
				if (len > 3) {
					memmove(&int16, keydata + 1, 2);
					exp = ntohs(int16);
					return (len - exp - 3)*8;
				} else {
					return 0;
				}
			} else {
				exp = keydata[0];
				return (len-exp-1)*8;
			}
		} else {
			return 0;
		}
		break;
#ifdef USE_GOST
	case LDNS_ECC_GOST:
		return 512;
#endif
#ifdef USE_ECDSA
        case LDNS_ECDSAP256SHA256:
                return 256;
        case LDNS_ECDSAP384SHA384:
                return 384;
#endif
#ifdef USE_ED25519
	case LDNS_ED25519:
		return 256;
#endif
#ifdef USE_ED448
	case LDNS_ED448:
		return 456;
#endif
	default:
		return 0;
	}
}