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
typedef  int /*<<< orphan*/  const EC_POINT ;
typedef  int /*<<< orphan*/  EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int BN_num_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_sub (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_value_one () ; 
 int EC_GROUP_get_order (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_GROUP_method_of (int /*<<< orphan*/  const*) ; 
 scalar_t__ EC_METHOD_get_field_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_POINT_free (int /*<<< orphan*/  const*) ; 
 int EC_POINT_get_affine_coordinates_GFp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int EC_POINT_is_at_infinity (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int EC_POINT_mul (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* EC_POINT_new (int /*<<< orphan*/  const*) ; 
 scalar_t__ NID_X9_62_prime_field ; 
 int SSH_ERR_ALLOC_FAIL ; 
 int SSH_ERR_KEY_INVALID_EC_VALUE ; 
 int SSH_ERR_LIBCRYPTO_ERROR ; 

int
sshkey_ec_validate_public(const EC_GROUP *group, const EC_POINT *public)
{
	BN_CTX *bnctx;
	EC_POINT *nq = NULL;
	BIGNUM *order, *x, *y, *tmp;
	int ret = SSH_ERR_KEY_INVALID_EC_VALUE;

	/*
	 * NB. This assumes OpenSSL has already verified that the public
	 * point lies on the curve. This is done by EC_POINT_oct2point()
	 * implicitly calling EC_POINT_is_on_curve(). If this code is ever
	 * reachable with public points not unmarshalled using
	 * EC_POINT_oct2point then the caller will need to explicitly check.
	 */

	if ((bnctx = BN_CTX_new()) == NULL)
		return SSH_ERR_ALLOC_FAIL;
	BN_CTX_start(bnctx);

	/*
	 * We shouldn't ever hit this case because bignum_get_ecpoint()
	 * refuses to load GF2m points.
	 */
	if (EC_METHOD_get_field_type(EC_GROUP_method_of(group)) !=
	    NID_X9_62_prime_field)
		goto out;

	/* Q != infinity */
	if (EC_POINT_is_at_infinity(group, public))
		goto out;

	if ((x = BN_CTX_get(bnctx)) == NULL ||
	    (y = BN_CTX_get(bnctx)) == NULL ||
	    (order = BN_CTX_get(bnctx)) == NULL ||
	    (tmp = BN_CTX_get(bnctx)) == NULL) {
		ret = SSH_ERR_ALLOC_FAIL;
		goto out;
	}

	/* log2(x) > log2(order)/2, log2(y) > log2(order)/2 */
	if (EC_GROUP_get_order(group, order, bnctx) != 1 ||
	    EC_POINT_get_affine_coordinates_GFp(group, public,
	    x, y, bnctx) != 1) {
		ret = SSH_ERR_LIBCRYPTO_ERROR;
		goto out;
	}
	if (BN_num_bits(x) <= BN_num_bits(order) / 2 ||
	    BN_num_bits(y) <= BN_num_bits(order) / 2)
		goto out;

	/* nQ == infinity (n == order of subgroup) */
	if ((nq = EC_POINT_new(group)) == NULL) {
		ret = SSH_ERR_ALLOC_FAIL;
		goto out;
	}
	if (EC_POINT_mul(group, nq, NULL, public, order, bnctx) != 1) {
		ret = SSH_ERR_LIBCRYPTO_ERROR;
		goto out;
	}
	if (EC_POINT_is_at_infinity(group, nq) != 1)
		goto out;

	/* x < order - 1, y < order - 1 */
	if (!BN_sub(tmp, order, BN_value_one())) {
		ret = SSH_ERR_LIBCRYPTO_ERROR;
		goto out;
	}
	if (BN_cmp(x, tmp) >= 0 || BN_cmp(y, tmp) >= 0)
		goto out;
	ret = 0;
 out:
	BN_CTX_free(bnctx);
	EC_POINT_free(nq);
	return ret;
}