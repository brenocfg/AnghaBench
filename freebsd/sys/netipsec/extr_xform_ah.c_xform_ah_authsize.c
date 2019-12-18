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
struct auth_hash {int type; int hashsize; } ;

/* Variables and functions */
 int AH_HMAC_HASHLEN ; 
#define  CRYPTO_AES_128_NIST_GMAC 133 
#define  CRYPTO_AES_192_NIST_GMAC 132 
#define  CRYPTO_AES_256_NIST_GMAC 131 
#define  CRYPTO_SHA2_256_HMAC 130 
#define  CRYPTO_SHA2_384_HMAC 129 
#define  CRYPTO_SHA2_512_HMAC 128 

int
xform_ah_authsize(const struct auth_hash *esph)
{
	int alen;

	if (esph == NULL)
		return 0;

	switch (esph->type) {
	case CRYPTO_SHA2_256_HMAC:
	case CRYPTO_SHA2_384_HMAC:
	case CRYPTO_SHA2_512_HMAC:
		alen = esph->hashsize / 2;	/* RFC4868 2.3 */
		break;

	case CRYPTO_AES_128_NIST_GMAC:
	case CRYPTO_AES_192_NIST_GMAC:
	case CRYPTO_AES_256_NIST_GMAC:
		alen = esph->hashsize;
		break;

	default:
		alen = AH_HMAC_HASHLEN;
		break;
	}

	return alen;
}