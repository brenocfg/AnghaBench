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
typedef  int /*<<< orphan*/ * gcry_mpi_t ;

/* Variables and functions */
 int /*<<< orphan*/  GCRYMPI_FMT_USG ; 
 scalar_t__ GPG_ERR_NO_ERROR ; 
 int /*<<< orphan*/ * gcry_mpi_new (size_t) ; 
 int /*<<< orphan*/  gcry_mpi_powm (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ gcry_mpi_print (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gcry_mpi_release (int /*<<< orphan*/ *) ; 
 scalar_t__ gcry_mpi_scan (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *) ; 

int crypto_mod_exp(const u8 *base, size_t base_len,
		   const u8 *power, size_t power_len,
		   const u8 *modulus, size_t modulus_len,
		   u8 *result, size_t *result_len)
{
	gcry_mpi_t bn_base = NULL, bn_exp = NULL, bn_modulus = NULL,
		bn_result = NULL;
	int ret = -1;

	if (gcry_mpi_scan(&bn_base, GCRYMPI_FMT_USG, base, base_len, NULL) !=
	    GPG_ERR_NO_ERROR ||
	    gcry_mpi_scan(&bn_exp, GCRYMPI_FMT_USG, power, power_len, NULL) !=
	    GPG_ERR_NO_ERROR ||
	    gcry_mpi_scan(&bn_modulus, GCRYMPI_FMT_USG, modulus, modulus_len,
			  NULL) != GPG_ERR_NO_ERROR)
		goto error;
	bn_result = gcry_mpi_new(modulus_len * 8);

	gcry_mpi_powm(bn_result, bn_base, bn_exp, bn_modulus);

	if (gcry_mpi_print(GCRYMPI_FMT_USG, result, *result_len, result_len,
			   bn_result) != GPG_ERR_NO_ERROR)
		goto error;

	ret = 0;

error:
	gcry_mpi_release(bn_base);
	gcry_mpi_release(bn_exp);
	gcry_mpi_release(bn_modulus);
	gcry_mpi_release(bn_result);
	return ret;
}