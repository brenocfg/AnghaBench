#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sae_data {TYPE_1__* tmp; } ;
struct crypto_ec_point {int dummy; } ;
struct crypto_bignum {int dummy; } ;
struct TYPE_2__ {int prime_len; int /*<<< orphan*/  ec; } ;

/* Variables and functions */
 int SAE_MAX_ECC_PRIME_LEN ; 
 int /*<<< orphan*/  crypto_ec_point_to_bin (int /*<<< orphan*/ ,struct crypto_ec_point const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sae_cn_confirm (struct sae_data*,int /*<<< orphan*/  const*,struct crypto_bignum const*,int /*<<< orphan*/ *,int,struct crypto_bignum const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sae_cn_confirm_ecc(struct sae_data *sae, const u8 *sc,
			       const struct crypto_bignum *scalar1,
			       const struct crypto_ec_point *element1,
			       const struct crypto_bignum *scalar2,
			       const struct crypto_ec_point *element2,
			       u8 *confirm)
{
	u8 element_b1[2 * SAE_MAX_ECC_PRIME_LEN];
	u8 element_b2[2 * SAE_MAX_ECC_PRIME_LEN];

	crypto_ec_point_to_bin(sae->tmp->ec, element1, element_b1,
			       element_b1 + sae->tmp->prime_len);
	crypto_ec_point_to_bin(sae->tmp->ec, element2, element_b2,
			       element_b2 + sae->tmp->prime_len);

	sae_cn_confirm(sae, sc, scalar1, element_b1, 2 * sae->tmp->prime_len,
		       scalar2, element_b2, 2 * sae->tmp->prime_len, confirm);
}