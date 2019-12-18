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
struct crypto_ec_point {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  prime_len; int /*<<< orphan*/  ec; int /*<<< orphan*/  sae_rand; int /*<<< orphan*/  peer_commit_element_ecc; struct crypto_ec_point* pwe_ecc; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ crypto_ec_point_add (int /*<<< orphan*/ ,struct crypto_ec_point*,int /*<<< orphan*/ ,struct crypto_ec_point*) ; 
 int /*<<< orphan*/  crypto_ec_point_deinit (struct crypto_ec_point*,int) ; 
 struct crypto_ec_point* crypto_ec_point_init (int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_ec_point_is_at_infinity (int /*<<< orphan*/ ,struct crypto_ec_point*) ; 
 scalar_t__ crypto_ec_point_mul (int /*<<< orphan*/ ,struct crypto_ec_point*,int /*<<< orphan*/ ,struct crypto_ec_point*) ; 
 scalar_t__ crypto_ec_point_to_bin (int /*<<< orphan*/ ,struct crypto_ec_point*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int sae_derive_k_ecc(struct sae_data *sae, u8 *k)
{
	struct crypto_ec_point *K;
	int ret = -1;

	K = crypto_ec_point_init(sae->tmp->ec);
	if (K == NULL)
		goto fail;

	/*
	 * K = scalar-op(rand, (elem-op(scalar-op(peer-commit-scalar, PWE),
	 *                                        PEER-COMMIT-ELEMENT)))
	 * If K is identity element (point-at-infinity), reject
	 * k = F(K) (= x coordinate)
	 */

	if (crypto_ec_point_mul(sae->tmp->ec, sae->tmp->pwe_ecc,
				sae->peer_commit_scalar, K) < 0 ||
	    crypto_ec_point_add(sae->tmp->ec, K,
				sae->tmp->peer_commit_element_ecc, K) < 0 ||
	    crypto_ec_point_mul(sae->tmp->ec, K, sae->tmp->sae_rand, K) < 0 ||
	    crypto_ec_point_is_at_infinity(sae->tmp->ec, K) ||
	    crypto_ec_point_to_bin(sae->tmp->ec, K, k, NULL) < 0) {
		wpa_printf(MSG_DEBUG, "SAE: Failed to calculate K and k");
		goto fail;
	}

	wpa_hexdump_key(MSG_DEBUG, "SAE: k", k, sae->tmp->prime_len);

	ret = 0;
fail:
	crypto_ec_point_deinit(K, 1);
	return ret;
}