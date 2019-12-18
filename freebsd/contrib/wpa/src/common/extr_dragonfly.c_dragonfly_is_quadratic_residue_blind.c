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
struct crypto_ec {int dummy; } ;
typedef  struct crypto_bignum const crypto_bignum ;

/* Variables and functions */
 int DRAGONFLY_MAX_ECC_PRIME_LEN ; 
 unsigned int const_time_eq (int,int) ; 
 unsigned int const_time_is_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const_time_select_bin (unsigned int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *) ; 
 int const_time_select_int (unsigned int,int,int) ; 
 int /*<<< orphan*/  crypto_bignum_deinit (struct crypto_bignum const*,int) ; 
 struct crypto_bignum const* crypto_bignum_init () ; 
 struct crypto_bignum const* crypto_bignum_init_set (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  crypto_bignum_is_odd (struct crypto_bignum const*) ; 
 int crypto_bignum_legendre (struct crypto_bignum const*,struct crypto_bignum const*) ; 
 scalar_t__ crypto_bignum_mulmod (struct crypto_bignum const*,struct crypto_bignum const*,struct crypto_bignum const*,struct crypto_bignum const*) ; 
 struct crypto_bignum const* crypto_ec_get_prime (struct crypto_ec*) ; 
 size_t crypto_ec_prime_len (struct crypto_ec*) ; 
 struct crypto_bignum const* dragonfly_get_rand_1_to_p_1 (struct crypto_bignum const*) ; 

int dragonfly_is_quadratic_residue_blind(struct crypto_ec *ec,
					 const u8 *qr, const u8 *qnr,
					 const struct crypto_bignum *val)
{
	struct crypto_bignum *r, *num, *qr_or_qnr = NULL;
	int check, res = -1;
	u8 qr_or_qnr_bin[DRAGONFLY_MAX_ECC_PRIME_LEN];
	const struct crypto_bignum *prime;
	size_t prime_len;
	unsigned int mask;

	prime = crypto_ec_get_prime(ec);
	prime_len = crypto_ec_prime_len(ec);

	/*
	 * Use a blinding technique to mask val while determining whether it is
	 * a quadratic residue modulo p to avoid leaking timing information
	 * while determining the Legendre symbol.
	 *
	 * v = val
	 * r = a random number between 1 and p-1, inclusive
	 * num = (v * r * r) modulo p
	 */
	r = dragonfly_get_rand_1_to_p_1(prime);
	if (!r)
		return -1;

	num = crypto_bignum_init();
	if (!num ||
	    crypto_bignum_mulmod(val, r, prime, num) < 0 ||
	    crypto_bignum_mulmod(num, r, prime, num) < 0)
		goto fail;

	/*
	 * Need to minimize differences in handling different cases, so try to
	 * avoid branches and timing differences.
	 *
	 * If r is odd:
	 * num = (num * qr) module p
	 * LGR(num, p) = 1 ==> quadratic residue
	 * else:
	 * num = (num * qnr) module p
	 * LGR(num, p) = -1 ==> quadratic residue
	 *
	 * mask is set to !odd(r)
	 */
	mask = const_time_is_zero(crypto_bignum_is_odd(r));
	const_time_select_bin(mask, qnr, qr, prime_len, qr_or_qnr_bin);
	qr_or_qnr = crypto_bignum_init_set(qr_or_qnr_bin, prime_len);
	if (!qr_or_qnr ||
	    crypto_bignum_mulmod(num, qr_or_qnr, prime, num) < 0)
		goto fail;
	/* branchless version of check = odd(r) ? 1 : -1, */
	check = const_time_select_int(mask, -1, 1);

	/* Determine the Legendre symbol on the masked value */
	res = crypto_bignum_legendre(num, prime);
	if (res == -2) {
		res = -1;
		goto fail;
	}
	/* branchless version of res = res == check
	 * (res is -1, 0, or 1; check is -1 or 1) */
	mask = const_time_eq(res, check);
	res = const_time_select_int(mask, 1, 0);
fail:
	crypto_bignum_deinit(num, 1);
	crypto_bignum_deinit(r, 1);
	crypto_bignum_deinit(qr_or_qnr, 1);
	return res;
}