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
struct crypto_bignum {int dummy; } ;
typedef  int /*<<< orphan*/  element_b2 ;
typedef  int /*<<< orphan*/  element_b1 ;
struct TYPE_2__ {int /*<<< orphan*/  prime_len; } ;

/* Variables and functions */
 int SAE_MAX_PRIME_LEN ; 
 int /*<<< orphan*/  crypto_bignum_to_bin (struct crypto_bignum const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sae_cn_confirm (struct sae_data*,int /*<<< orphan*/  const*,struct crypto_bignum const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct crypto_bignum const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sae_cn_confirm_ffc(struct sae_data *sae, const u8 *sc,
			       const struct crypto_bignum *scalar1,
			       const struct crypto_bignum *element1,
			       const struct crypto_bignum *scalar2,
			       const struct crypto_bignum *element2,
			       u8 *confirm)
{
	u8 element_b1[SAE_MAX_PRIME_LEN];
	u8 element_b2[SAE_MAX_PRIME_LEN];

	crypto_bignum_to_bin(element1, element_b1, sizeof(element_b1),
			     sae->tmp->prime_len);
	crypto_bignum_to_bin(element2, element_b2, sizeof(element_b2),
			     sae->tmp->prime_len);

	sae_cn_confirm(sae, sc, scalar1, element_b1, sae->tmp->prime_len,
		       scalar2, element_b2, sae->tmp->prime_len, confirm);
}