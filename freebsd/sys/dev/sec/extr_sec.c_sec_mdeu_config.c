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
typedef  int u_int ;
struct cryptodesc {int crd_alg; } ;

/* Variables and functions */
#define  CRYPTO_MD5 134 
#define  CRYPTO_MD5_HMAC 133 
#define  CRYPTO_SHA1 132 
#define  CRYPTO_SHA1_HMAC 131 
#define  CRYPTO_SHA2_256_HMAC 130 
#define  CRYPTO_SHA2_384_HMAC 129 
#define  CRYPTO_SHA2_512_HMAC 128 
 int EINVAL ; 
 int MD5_HASH_LEN ; 
 int SEC_EU_MDEU_A ; 
 int SEC_EU_MDEU_B ; 
 int SEC_EU_NONE ; 
 int SEC_HMAC_HASH_LEN ; 
 int SEC_MDEU_MODE_HMAC ; 
 int SEC_MDEU_MODE_INIT ; 
 int SEC_MDEU_MODE_MD5 ; 
 int SEC_MDEU_MODE_PD ; 
 int SEC_MDEU_MODE_SHA1 ; 
 int SEC_MDEU_MODE_SHA256 ; 
 int SEC_MDEU_MODE_SHA384 ; 
 int SEC_MDEU_MODE_SHA512 ; 
 int SHA1_HASH_LEN ; 

__attribute__((used)) static int
sec_mdeu_config(struct cryptodesc *crd, u_int *eu, u_int *mode, u_int *hashlen)
{

	*mode = SEC_MDEU_MODE_PD | SEC_MDEU_MODE_INIT;
	*eu = SEC_EU_NONE;

	switch (crd->crd_alg) {
	case CRYPTO_MD5_HMAC:
		*mode |= SEC_MDEU_MODE_HMAC;
		/* FALLTHROUGH */
	case CRYPTO_MD5:
		*eu = SEC_EU_MDEU_A;
		*mode |= SEC_MDEU_MODE_MD5;
		*hashlen = MD5_HASH_LEN;
		break;
	case CRYPTO_SHA1_HMAC:
		*mode |= SEC_MDEU_MODE_HMAC;
		/* FALLTHROUGH */
	case CRYPTO_SHA1:
		*eu = SEC_EU_MDEU_A;
		*mode |= SEC_MDEU_MODE_SHA1;
		*hashlen = SHA1_HASH_LEN;
		break;
	case CRYPTO_SHA2_256_HMAC:
		*mode |= SEC_MDEU_MODE_HMAC | SEC_MDEU_MODE_SHA256;
		*eu = SEC_EU_MDEU_A;
		break;
	case CRYPTO_SHA2_384_HMAC:
		*mode |= SEC_MDEU_MODE_HMAC | SEC_MDEU_MODE_SHA384;
		*eu = SEC_EU_MDEU_B;
		break;
	case CRYPTO_SHA2_512_HMAC:
		*mode |= SEC_MDEU_MODE_HMAC | SEC_MDEU_MODE_SHA512;
		*eu = SEC_EU_MDEU_B;
		break;
	default:
		return (EINVAL);
	}

	if (*mode & SEC_MDEU_MODE_HMAC)
		*hashlen = SEC_HMAC_HASH_LEN;

	return (0);
}