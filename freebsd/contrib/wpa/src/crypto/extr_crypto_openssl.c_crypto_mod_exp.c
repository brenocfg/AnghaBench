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
 size_t BN_bn2bin (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/ *) ; 
 int BN_mod_exp_mont_consttime (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 

int crypto_mod_exp(const u8 *base, size_t base_len,
		   const u8 *power, size_t power_len,
		   const u8 *modulus, size_t modulus_len,
		   u8 *result, size_t *result_len)
{
	BIGNUM *bn_base, *bn_exp, *bn_modulus, *bn_result;
	int ret = -1;
	BN_CTX *ctx;

	ctx = BN_CTX_new();
	if (ctx == NULL)
		return -1;

	bn_base = BN_bin2bn(base, base_len, NULL);
	bn_exp = BN_bin2bn(power, power_len, NULL);
	bn_modulus = BN_bin2bn(modulus, modulus_len, NULL);
	bn_result = BN_new();

	if (bn_base == NULL || bn_exp == NULL || bn_modulus == NULL ||
	    bn_result == NULL)
		goto error;

	if (BN_mod_exp_mont_consttime(bn_result, bn_base, bn_exp, bn_modulus,
				      ctx, NULL) != 1)
		goto error;

	*result_len = BN_bn2bin(bn_result, result);
	ret = 0;

error:
	BN_clear_free(bn_base);
	BN_clear_free(bn_exp);
	BN_clear_free(bn_modulus);
	BN_clear_free(bn_result);
	BN_CTX_free(ctx);
	return ret;
}