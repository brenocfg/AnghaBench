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
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_is_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  BN_nnmod (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

int SRP_Verify_B_mod_N(const BIGNUM *B, const BIGNUM *N)
{
    BIGNUM *r;
    BN_CTX *bn_ctx;
    int ret = 0;

    if (B == NULL || N == NULL || (bn_ctx = BN_CTX_new()) == NULL)
        return 0;

    if ((r = BN_new()) == NULL)
        goto err;
    /* Checks if B % N == 0 */
    if (!BN_nnmod(r, B, N, bn_ctx))
        goto err;
    ret = !BN_is_zero(r);
 err:
    BN_CTX_free(bn_ctx);
    BN_free(r);
    return ret;
}