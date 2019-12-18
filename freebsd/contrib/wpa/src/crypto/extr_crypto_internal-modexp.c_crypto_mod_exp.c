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
struct bignum {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bignum_deinit (struct bignum*) ; 
 scalar_t__ bignum_exptmod (struct bignum*,struct bignum*,struct bignum*,struct bignum*) ; 
 int bignum_get_unsigned_bin (struct bignum*,int /*<<< orphan*/ *,size_t*) ; 
 struct bignum* bignum_init () ; 
 scalar_t__ bignum_set_unsigned_bin (struct bignum*,int /*<<< orphan*/  const*,size_t) ; 

int crypto_mod_exp(const u8 *base, size_t base_len,
		   const u8 *power, size_t power_len,
		   const u8 *modulus, size_t modulus_len,
		   u8 *result, size_t *result_len)
{
	struct bignum *bn_base, *bn_exp, *bn_modulus, *bn_result;
	int ret = -1;

	bn_base = bignum_init();
	bn_exp = bignum_init();
	bn_modulus = bignum_init();
	bn_result = bignum_init();

	if (bn_base == NULL || bn_exp == NULL || bn_modulus == NULL ||
	    bn_result == NULL)
		goto error;

	if (bignum_set_unsigned_bin(bn_base, base, base_len) < 0 ||
	    bignum_set_unsigned_bin(bn_exp, power, power_len) < 0 ||
	    bignum_set_unsigned_bin(bn_modulus, modulus, modulus_len) < 0)
		goto error;

	if (bignum_exptmod(bn_base, bn_exp, bn_modulus, bn_result) < 0)
		goto error;

	ret = bignum_get_unsigned_bin(bn_result, result, result_len);

error:
	bignum_deinit(bn_base);
	bignum_deinit(bn_exp);
	bignum_deinit(bn_modulus);
	bignum_deinit(bn_result);
	return ret;
}