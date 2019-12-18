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
struct sae_temporary_data {int /*<<< orphan*/  pw_id; int /*<<< orphan*/  anti_clogging_token; int /*<<< orphan*/  peer_commit_element_ecc; int /*<<< orphan*/  own_commit_element_ecc; int /*<<< orphan*/  pwe_ecc; int /*<<< orphan*/  peer_commit_element_ffc; int /*<<< orphan*/  own_commit_element_ffc; int /*<<< orphan*/  own_commit_scalar; int /*<<< orphan*/  pwe_ffc; int /*<<< orphan*/  sae_rand; int /*<<< orphan*/  order_buf; int /*<<< orphan*/  prime_buf; int /*<<< orphan*/  ec; } ;
struct sae_data {struct sae_temporary_data* tmp; } ;

/* Variables and functions */
 int /*<<< orphan*/  bin_clear_free (struct sae_temporary_data*,int) ; 
 int /*<<< orphan*/  crypto_bignum_deinit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  crypto_ec_deinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_ec_point_deinit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ ) ; 

void sae_clear_temp_data(struct sae_data *sae)
{
	struct sae_temporary_data *tmp;
	if (sae == NULL || sae->tmp == NULL)
		return;
	tmp = sae->tmp;
	crypto_ec_deinit(tmp->ec);
	crypto_bignum_deinit(tmp->prime_buf, 0);
	crypto_bignum_deinit(tmp->order_buf, 0);
	crypto_bignum_deinit(tmp->sae_rand, 1);
	crypto_bignum_deinit(tmp->pwe_ffc, 1);
	crypto_bignum_deinit(tmp->own_commit_scalar, 0);
	crypto_bignum_deinit(tmp->own_commit_element_ffc, 0);
	crypto_bignum_deinit(tmp->peer_commit_element_ffc, 0);
	crypto_ec_point_deinit(tmp->pwe_ecc, 1);
	crypto_ec_point_deinit(tmp->own_commit_element_ecc, 0);
	crypto_ec_point_deinit(tmp->peer_commit_element_ecc, 0);
	wpabuf_free(tmp->anti_clogging_token);
	os_free(tmp->pw_id);
	bin_clear_free(tmp, sizeof(*tmp));
	sae->tmp = NULL;
}