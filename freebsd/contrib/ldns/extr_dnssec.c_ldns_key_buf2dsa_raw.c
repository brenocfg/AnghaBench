#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
struct TYPE_7__ {int /*<<< orphan*/ * pub_key; int /*<<< orphan*/ * g; int /*<<< orphan*/ * q; int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ DSA ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/ * BN_bin2bn (unsigned char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DSA_free (TYPE_1__*) ; 
 TYPE_1__* DSA_new () ; 
 int /*<<< orphan*/  DSA_set0_key (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DSA_set0_pqg (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t SHA_DIGEST_LENGTH ; 

DSA *
ldns_key_buf2dsa_raw(const unsigned char* key, size_t len)
{
	uint8_t T;
	uint16_t length;
	uint16_t offset;
	DSA *dsa;
	BIGNUM *Q; BIGNUM *P;
	BIGNUM *G; BIGNUM *Y;

	if(len == 0)
		return NULL;
	T = (uint8_t)key[0];
	length = (64 + T * 8);
	offset = 1;

	if (T > 8) {
		return NULL;
	}
	if(len < (size_t)1 + SHA_DIGEST_LENGTH + 3*length)
		return NULL;

	Q = BN_bin2bn(key+offset, SHA_DIGEST_LENGTH, NULL);
	offset += SHA_DIGEST_LENGTH;

	P = BN_bin2bn(key+offset, (int)length, NULL);
	offset += length;

	G = BN_bin2bn(key+offset, (int)length, NULL);
	offset += length;

	Y = BN_bin2bn(key+offset, (int)length, NULL);
	offset += length;

	/* create the key and set its properties */
	if(!Q || !P || !G || !Y || !(dsa = DSA_new())) {
		BN_free(Q);
		BN_free(P);
		BN_free(G);
		BN_free(Y);
		return NULL;
	}
#if OPENSSL_VERSION_NUMBER < 0x10100000 || defined(HAVE_LIBRESSL)
#ifndef S_SPLINT_S
	dsa->p = P;
	dsa->q = Q;
	dsa->g = G;
	dsa->pub_key = Y;
#endif /* splint */
#else /* OPENSSL_VERSION_NUMBER */
	if (!DSA_set0_pqg(dsa, P, Q, G)) {
		/* QPG not yet attached, need to free */
		BN_free(Q);
		BN_free(P);
		BN_free(G);

		DSA_free(dsa);
		BN_free(Y);
		return NULL;
	}
	if (!DSA_set0_key(dsa, Y, NULL)) {
		/* QPG attached, cleaned up by DSA_fre() */
		DSA_free(dsa);
		BN_free(Y);
		return NULL;
	}
#endif /* OPENSSL_VERSION_NUMBER */
	return dsa;
}