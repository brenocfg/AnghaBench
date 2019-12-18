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
struct sae_data {TYPE_1__* tmp; int /*<<< orphan*/  peer_commit_scalar; } ;
struct crypto_bignum {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  prime_len; int /*<<< orphan*/  prime; int /*<<< orphan*/  sae_rand; int /*<<< orphan*/  peer_commit_element_ffc; struct crypto_bignum* pwe_ffc; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  SAE_MAX_PRIME_LEN ; 
 int /*<<< orphan*/  crypto_bignum_deinit (struct crypto_bignum*,int) ; 
 scalar_t__ crypto_bignum_exptmod (struct crypto_bignum*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct crypto_bignum*) ; 
 struct crypto_bignum* crypto_bignum_init () ; 
 scalar_t__ crypto_bignum_is_one (struct crypto_bignum*) ; 
 scalar_t__ crypto_bignum_mulmod (struct crypto_bignum*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct crypto_bignum*) ; 
 scalar_t__ crypto_bignum_to_bin (struct crypto_bignum*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int sae_derive_k_ffc(struct sae_data *sae, u8 *k)
{
	struct crypto_bignum *K;
	int ret = -1;

	K = crypto_bignum_init();
	if (K == NULL)
		goto fail;

	/*
	 * K = scalar-op(rand, (elem-op(scalar-op(peer-commit-scalar, PWE),
	 *                                        PEER-COMMIT-ELEMENT)))
	 * If K is identity element (one), reject.
	 * k = F(K) (= x coordinate)
	 */

	if (crypto_bignum_exptmod(sae->tmp->pwe_ffc, sae->peer_commit_scalar,
				  sae->tmp->prime, K) < 0 ||
	    crypto_bignum_mulmod(K, sae->tmp->peer_commit_element_ffc,
				 sae->tmp->prime, K) < 0 ||
	    crypto_bignum_exptmod(K, sae->tmp->sae_rand, sae->tmp->prime, K) < 0
	    ||
	    crypto_bignum_is_one(K) ||
	    crypto_bignum_to_bin(K, k, SAE_MAX_PRIME_LEN, sae->tmp->prime_len) <
	    0) {
		wpa_printf(MSG_DEBUG, "SAE: Failed to calculate K and k");
		goto fail;
	}

	wpa_hexdump_key(MSG_DEBUG, "SAE: k", k, sae->tmp->prime_len);

	ret = 0;
fail:
	crypto_bignum_deinit(K, 1);
	return ret;
}