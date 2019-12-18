#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
struct TYPE_6__ {int /*<<< orphan*/ * e; int /*<<< orphan*/ * n; } ;
typedef  TYPE_1__ RSA ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_bin2bn (unsigned char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  RSA_free (TYPE_1__*) ; 
 TYPE_1__* RSA_new () ; 
 int /*<<< orphan*/  RSA_set0_key (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memmove (size_t*,unsigned char const*,int) ; 
 size_t ntohs (size_t) ; 

RSA *
ldns_key_buf2rsa_raw(const unsigned char* key, size_t len)
{
	uint16_t offset;
	uint16_t exp;
	uint16_t int16;
	RSA *rsa;
	BIGNUM *modulus;
	BIGNUM *exponent;

	if (len == 0)
		return NULL;
	if (key[0] == 0) {
		if(len < 3)
			return NULL;
		/* need some smart comment here XXX*/
		/* the exponent is too large so it's places
		 * futher...???? */
		memmove(&int16, key+1, 2);
		exp = ntohs(int16);
		offset = 3;
	} else {
		exp = key[0];
		offset = 1;
	}

	/* key length at least one */
	if(len < (size_t)offset + exp + 1)
		return NULL;

	/* Exponent */
	exponent = BN_new();
	if(!exponent) return NULL;
	(void) BN_bin2bn(key+offset, (int)exp, exponent);
	offset += exp;

	/* Modulus */
	modulus = BN_new();
	if(!modulus) {
		BN_free(exponent);
		return NULL;
	}
	/* length of the buffer must match the key length! */
	(void) BN_bin2bn(key+offset, (int)(len - offset), modulus);

	rsa = RSA_new();
	if(!rsa) {
		BN_free(exponent);
		BN_free(modulus);
		return NULL;
	}
#if OPENSSL_VERSION_NUMBER < 0x10100000 || defined(HAVE_LIBRESSL)
#ifndef S_SPLINT_S
	rsa->n = modulus;
	rsa->e = exponent;
#endif /* splint */
#else /* OPENSSL_VERSION_NUMBER */
	if (!RSA_set0_key(rsa, modulus, exponent, NULL)) {
		BN_free(exponent);
		BN_free(modulus);
		RSA_free(rsa);
		return NULL;
	}
#endif /* OPENSSL_VERSION_NUMBER */

	return rsa;
}