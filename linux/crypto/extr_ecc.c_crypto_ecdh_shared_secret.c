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
typedef  int /*<<< orphan*/  const u64 ;
struct ecc_point {int /*<<< orphan*/  const* x; int /*<<< orphan*/  const* y; } ;
struct ecc_curve {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/  const*) ; 
 unsigned int ECC_DIGITS_TO_BYTES_SHIFT ; 
 int ECC_MAX_DIGITS ; 
 int EFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct ecc_point* ecc_alloc_point (unsigned int) ; 
 int /*<<< orphan*/  ecc_free_point (struct ecc_point*) ; 
 struct ecc_curve* ecc_get_curve (unsigned int) ; 
 int ecc_is_pubkey_valid_partial (struct ecc_curve const*,struct ecc_point*) ; 
 scalar_t__ ecc_point_is_zero (struct ecc_point*) ; 
 int /*<<< orphan*/  ecc_point_mult (struct ecc_point*,struct ecc_point*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,struct ecc_curve const*,unsigned int) ; 
 int /*<<< orphan*/  ecc_swap_digits (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/  const*,unsigned int) ; 

int crypto_ecdh_shared_secret(unsigned int curve_id, unsigned int ndigits,
			      const u64 *private_key, const u64 *public_key,
			      u64 *secret)
{
	int ret = 0;
	struct ecc_point *product, *pk;
	u64 priv[ECC_MAX_DIGITS];
	u64 rand_z[ECC_MAX_DIGITS];
	unsigned int nbytes;
	const struct ecc_curve *curve = ecc_get_curve(curve_id);

	if (!private_key || !public_key || !curve ||
	    ndigits > ARRAY_SIZE(priv) || ndigits > ARRAY_SIZE(rand_z)) {
		ret = -EINVAL;
		goto out;
	}

	nbytes = ndigits << ECC_DIGITS_TO_BYTES_SHIFT;

	get_random_bytes(rand_z, nbytes);

	pk = ecc_alloc_point(ndigits);
	if (!pk) {
		ret = -ENOMEM;
		goto out;
	}

	ecc_swap_digits(public_key, pk->x, ndigits);
	ecc_swap_digits(&public_key[ndigits], pk->y, ndigits);
	ret = ecc_is_pubkey_valid_partial(curve, pk);
	if (ret)
		goto err_alloc_product;

	ecc_swap_digits(private_key, priv, ndigits);

	product = ecc_alloc_point(ndigits);
	if (!product) {
		ret = -ENOMEM;
		goto err_alloc_product;
	}

	ecc_point_mult(product, pk, priv, rand_z, curve, ndigits);

	ecc_swap_digits(product->x, secret, ndigits);

	if (ecc_point_is_zero(product))
		ret = -EFAULT;

	ecc_free_point(product);
err_alloc_product:
	ecc_free_point(pk);
out:
	return ret;
}