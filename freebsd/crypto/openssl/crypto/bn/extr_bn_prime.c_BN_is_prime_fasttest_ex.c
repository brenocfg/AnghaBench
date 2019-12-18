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
typedef  scalar_t__ BN_ULONG ;
typedef  int /*<<< orphan*/  BN_MONT_CTX ;
typedef  int /*<<< orphan*/  BN_GENCB ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_GENCB_call (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  BN_MONT_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_MONT_CTX_new () ; 
 int /*<<< orphan*/  BN_MONT_CTX_set (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_add_word (int /*<<< orphan*/ *,int) ; 
 scalar_t__ BN_cmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_copy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_is_bit_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BN_is_odd (int /*<<< orphan*/  const*) ; 
 int BN_is_word (int /*<<< orphan*/  const*,int) ; 
 scalar_t__ BN_mod_word (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  BN_num_bits (int /*<<< orphan*/  const*) ; 
 int BN_prime_checks ; 
 int BN_prime_checks_for_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_priv_rand_range (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_rshift (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BN_sub_word (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BN_value_one () ; 
 int NUMPRIMES ; 
 int* primes ; 
 int witness (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int BN_is_prime_fasttest_ex(const BIGNUM *a, int checks, BN_CTX *ctx_passed,
                            int do_trial_division, BN_GENCB *cb)
{
    int i, j, ret = -1;
    int k;
    BN_CTX *ctx = NULL;
    BIGNUM *A1, *A1_odd, *A3, *check; /* taken from ctx */
    BN_MONT_CTX *mont = NULL;

    /* Take care of the really small primes 2 & 3 */
    if (BN_is_word(a, 2) || BN_is_word(a, 3))
        return 1;

    /* Check odd and bigger than 1 */
    if (!BN_is_odd(a) || BN_cmp(a, BN_value_one()) <= 0)
        return 0;

    if (checks == BN_prime_checks)
        checks = BN_prime_checks_for_size(BN_num_bits(a));

    /* first look for small factors */
    if (do_trial_division) {
        for (i = 1; i < NUMPRIMES; i++) {
            BN_ULONG mod = BN_mod_word(a, primes[i]);
            if (mod == (BN_ULONG)-1)
                goto err;
            if (mod == 0)
                return BN_is_word(a, primes[i]);
        }
        if (!BN_GENCB_call(cb, 1, -1))
            goto err;
    }

    if (ctx_passed != NULL)
        ctx = ctx_passed;
    else if ((ctx = BN_CTX_new()) == NULL)
        goto err;
    BN_CTX_start(ctx);

    A1 = BN_CTX_get(ctx);
    A3 = BN_CTX_get(ctx);
    A1_odd = BN_CTX_get(ctx);
    check = BN_CTX_get(ctx);
    if (check == NULL)
        goto err;

    /* compute A1 := a - 1 */
    if (!BN_copy(A1, a) || !BN_sub_word(A1, 1))
        goto err;
    /* compute A3 := a - 3 */
    if (!BN_copy(A3, a) || !BN_sub_word(A3, 3))
        goto err;

    /* write  A1  as  A1_odd * 2^k */
    k = 1;
    while (!BN_is_bit_set(A1, k))
        k++;
    if (!BN_rshift(A1_odd, A1, k))
        goto err;

    /* Montgomery setup for computations mod a */
    mont = BN_MONT_CTX_new();
    if (mont == NULL)
        goto err;
    if (!BN_MONT_CTX_set(mont, a, ctx))
        goto err;

    for (i = 0; i < checks; i++) {
        /* 1 < check < a-1 */
        if (!BN_priv_rand_range(check, A3) || !BN_add_word(check, 2))
            goto err;

        j = witness(check, a, A1, A1_odd, k, ctx, mont);
        if (j == -1)
            goto err;
        if (j) {
            ret = 0;
            goto err;
        }
        if (!BN_GENCB_call(cb, 1, i))
            goto err;
    }
    ret = 1;
 err:
    if (ctx != NULL) {
        BN_CTX_end(ctx);
        if (ctx_passed == NULL)
            BN_CTX_free(ctx);
    }
    BN_MONT_CTX_free(mont);

    return ret;
}