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
struct sae_data {TYPE_1__* tmp; } ;
struct crypto_bignum {int dummy; } ;
struct TYPE_2__ {scalar_t__ dh; scalar_t__ ec; void* own_commit_scalar; void* sae_rand; int /*<<< orphan*/  order; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_bignum_deinit (struct crypto_bignum*,int) ; 
 void* crypto_bignum_init () ; 
 scalar_t__ dragonfly_generate_scalar (int /*<<< orphan*/ ,void*,struct crypto_bignum*,void*) ; 
 scalar_t__ sae_derive_commit_element_ecc (struct sae_data*,struct crypto_bignum*) ; 
 scalar_t__ sae_derive_commit_element_ffc (struct sae_data*,struct crypto_bignum*) ; 

__attribute__((used)) static int sae_derive_commit(struct sae_data *sae)
{
	struct crypto_bignum *mask;
	int ret;

	mask = crypto_bignum_init();
	if (!sae->tmp->sae_rand)
		sae->tmp->sae_rand = crypto_bignum_init();
	if (!sae->tmp->own_commit_scalar)
		sae->tmp->own_commit_scalar = crypto_bignum_init();
	ret = !mask || !sae->tmp->sae_rand || !sae->tmp->own_commit_scalar ||
		dragonfly_generate_scalar(sae->tmp->order, sae->tmp->sae_rand,
					  mask,
					  sae->tmp->own_commit_scalar) < 0 ||
		(sae->tmp->ec &&
		 sae_derive_commit_element_ecc(sae, mask) < 0) ||
		(sae->tmp->dh &&
		 sae_derive_commit_element_ffc(sae, mask) < 0);
	crypto_bignum_deinit(mask, 1);
	return ret ? -1 : 0;
}