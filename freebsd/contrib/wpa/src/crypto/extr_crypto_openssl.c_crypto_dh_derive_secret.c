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
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/ * BN_bin2bn (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ BN_is_one (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_is_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_exp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int crypto_mod_exp (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,size_t*) ; 

int crypto_dh_derive_secret(u8 generator, const u8 *prime, size_t prime_len,
			    const u8 *order, size_t order_len,
			    const u8 *privkey, size_t privkey_len,
			    const u8 *pubkey, size_t pubkey_len,
			    u8 *secret, size_t *len)
{
	BIGNUM *pub, *p;
	int res = -1;

	pub = BN_bin2bn(pubkey, pubkey_len, NULL);
	p = BN_bin2bn(prime, prime_len, NULL);
	if (!pub || !p || BN_is_zero(pub) || BN_is_one(pub) ||
	    BN_cmp(pub, p) >= 0)
		goto fail;

	if (order) {
		BN_CTX *ctx;
		BIGNUM *q, *tmp;
		int failed;

		/* verify: pubkey^q == 1 mod p */
		q = BN_bin2bn(order, order_len, NULL);
		ctx = BN_CTX_new();
		tmp = BN_new();
		failed = !q || !ctx || !tmp ||
			!BN_mod_exp(tmp, pub, q, p, ctx) ||
			!BN_is_one(tmp);
		BN_clear_free(q);
		BN_clear_free(tmp);
		BN_CTX_free(ctx);
		if (failed)
			goto fail;
	}

	res = crypto_mod_exp(pubkey, pubkey_len, privkey, privkey_len,
			     prime, prime_len, secret, len);
fail:
	BN_clear_free(pub);
	BN_clear_free(p);
	return res;
}