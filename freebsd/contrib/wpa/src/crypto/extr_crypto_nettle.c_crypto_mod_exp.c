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
 int /*<<< orphan*/  mpz_clears (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpz_export (int /*<<< orphan*/ *,size_t*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpz_import (int /*<<< orphan*/ ,size_t,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mpz_inits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpz_powm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t mpz_sizeinbase (int /*<<< orphan*/ ,int) ; 

int crypto_mod_exp(const u8 *base, size_t base_len,
		   const u8 *power, size_t power_len,
		   const u8 *modulus, size_t modulus_len,
		   u8 *result, size_t *result_len)
{
	mpz_t bn_base, bn_exp, bn_modulus, bn_result;
	int ret = -1;
	size_t len;

	mpz_inits(bn_base, bn_exp, bn_modulus, bn_result, NULL);
	mpz_import(bn_base, base_len, 1, 1, 1, 0, base);
	mpz_import(bn_exp, power_len, 1, 1, 1, 0, power);
	mpz_import(bn_modulus, modulus_len, 1, 1, 1, 0, modulus);

	mpz_powm(bn_result, bn_base, bn_exp, bn_modulus);
	len = mpz_sizeinbase(bn_result, 2);
	len = (len + 7) / 8;
	if (*result_len < len)
		goto error;
	mpz_export(result, result_len, 1, 1, 1, 0, bn_result);
	ret = 0;

error:
	mpz_clears(bn_base, bn_exp, bn_modulus, bn_result, NULL);
	return ret;
}