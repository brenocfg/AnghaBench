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
struct TYPE_2__ {scalar_t__ own_commit_element_ecc; int /*<<< orphan*/  ec; int /*<<< orphan*/  pwe_ecc; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ crypto_ec_point_init (int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_ec_point_invert (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ crypto_ec_point_mul (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct crypto_bignum*,scalar_t__) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int sae_derive_commit_element_ecc(struct sae_data *sae,
					 struct crypto_bignum *mask)
{
	/* COMMIT-ELEMENT = inverse(scalar-op(mask, PWE)) */
	if (!sae->tmp->own_commit_element_ecc) {
		sae->tmp->own_commit_element_ecc =
			crypto_ec_point_init(sae->tmp->ec);
		if (!sae->tmp->own_commit_element_ecc)
			return -1;
	}

	if (crypto_ec_point_mul(sae->tmp->ec, sae->tmp->pwe_ecc, mask,
				sae->tmp->own_commit_element_ecc) < 0 ||
	    crypto_ec_point_invert(sae->tmp->ec,
				   sae->tmp->own_commit_element_ecc) < 0) {
		wpa_printf(MSG_DEBUG, "SAE: Could not compute commit-element");
		return -1;
	}

	return 0;
}