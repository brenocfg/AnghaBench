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
 int /*<<< orphan*/  crypto_bignum_is_one (struct crypto_bignum*) ; 
 int /*<<< orphan*/  crypto_bignum_is_zero (struct crypto_bignum*) ; 
 scalar_t__ crypto_bignum_rand (struct crypto_bignum*,struct crypto_bignum const*) ; 

__attribute__((used)) static int dragonfly_get_rand_2_to_r_1(struct crypto_bignum *val,
				       const struct crypto_bignum *order)
{
	return crypto_bignum_rand(val, order) == 0 &&
		!crypto_bignum_is_zero(val) &&
		!crypto_bignum_is_one(val);
}