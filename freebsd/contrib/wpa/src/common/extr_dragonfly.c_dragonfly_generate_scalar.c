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
struct crypto_bignum {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ crypto_bignum_add (struct crypto_bignum*,struct crypto_bignum*,struct crypto_bignum*) ; 
 int /*<<< orphan*/  crypto_bignum_is_one (struct crypto_bignum*) ; 
 int /*<<< orphan*/  crypto_bignum_is_zero (struct crypto_bignum*) ; 
 scalar_t__ crypto_bignum_mod (struct crypto_bignum*,struct crypto_bignum const*,struct crypto_bignum*) ; 
 scalar_t__ dragonfly_get_rand_2_to_r_1 (struct crypto_bignum*,struct crypto_bignum const*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

int dragonfly_generate_scalar(const struct crypto_bignum *order,
			      struct crypto_bignum *_rand,
			      struct crypto_bignum *_mask,
			      struct crypto_bignum *scalar)
{
	int count;

	/* Select two random values rand,mask such that 1 < rand,mask < r and
	 * rand + mask mod r > 1. */
	for (count = 0; count < 100; count++) {
		if (dragonfly_get_rand_2_to_r_1(_rand, order) &&
		    dragonfly_get_rand_2_to_r_1(_mask, order) &&
		    crypto_bignum_add(_rand, _mask, scalar) == 0 &&
		    crypto_bignum_mod(scalar, order, scalar) == 0 &&
		    !crypto_bignum_is_zero(scalar) &&
		    !crypto_bignum_is_one(scalar))
			return 0;
	}

	/* This should not be reachable in practice if the random number
	 * generation is working. */
	wpa_printf(MSG_INFO,
		   "dragonfly: Unable to get randomness for own scalar");
	return -1;
}