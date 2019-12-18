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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  mpz_t ;

/* Variables and functions */
 int crypto_mod_exp (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  mpz_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpz_clears (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ mpz_cmp_d (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mpz_import (int /*<<< orphan*/ ,size_t,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mpz_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpz_inits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpz_powm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 

int crypto_dh_derive_secret(u8 generator, const u8 *prime, size_t prime_len,
			    const u8 *order, size_t order_len,
			    const u8 *privkey, size_t privkey_len,
			    const u8 *pubkey, size_t pubkey_len,
			    u8 *secret, size_t *len)
{
	mpz_t pub;
	int res = -1;

	if (pubkey_len > prime_len ||
	    (pubkey_len == prime_len &&
	     os_memcmp(pubkey, prime, prime_len) >= 0))
		return -1;

	mpz_init(pub);
	mpz_import(pub, pubkey_len, 1, 1, 1, 0, pubkey);
	if (mpz_cmp_d(pub, 1) <= 0)
		goto fail;

	if (order) {
		mpz_t p, q, tmp;
		int failed;

		/* verify: pubkey^q == 1 mod p */
		mpz_inits(p, q, tmp, NULL);
		mpz_import(p, prime_len, 1, 1, 1, 0, prime);
		mpz_import(q, order_len, 1, 1, 1, 0, order);
		mpz_powm(tmp, pub, q, p);
		failed = mpz_cmp_d(tmp, 1) != 0;
		mpz_clears(p, q, tmp, NULL);
		if (failed)
			goto fail;
	}

	res = crypto_mod_exp(pubkey, pubkey_len, privkey, privkey_len,
			     prime, prime_len, secret, len);
fail:
	mpz_clear(pub);
	return res;
}