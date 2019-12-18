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
typedef  int BN_ULONG ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_RAND_BOTTOM_ODD ; 
 int /*<<< orphan*/  BN_RAND_TOP_ONE ; 
 int /*<<< orphan*/  BN_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_add_word (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BN_mod (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int BN_mod_word (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BN_rand (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_sub (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int NUMPRIMES ; 
 int /*<<< orphan*/  bn_check_top (int /*<<< orphan*/ *) ; 
 scalar_t__* primes ; 

int bn_probable_prime_dh(BIGNUM *rnd, int bits,
                         const BIGNUM *add, const BIGNUM *rem, BN_CTX *ctx)
{
    int i, ret = 0;
    BIGNUM *t1;

    BN_CTX_start(ctx);
    if ((t1 = BN_CTX_get(ctx)) == NULL)
        goto err;

    if (!BN_rand(rnd, bits, BN_RAND_TOP_ONE, BN_RAND_BOTTOM_ODD))
        goto err;

    /* we need ((rnd-rem) % add) == 0 */

    if (!BN_mod(t1, rnd, add, ctx))
        goto err;
    if (!BN_sub(rnd, rnd, t1))
        goto err;
    if (rem == NULL) {
        if (!BN_add_word(rnd, 1))
            goto err;
    } else {
        if (!BN_add(rnd, rnd, rem))
            goto err;
    }

    /* we now have a random number 'rand' to test. */

 loop:
    for (i = 1; i < NUMPRIMES; i++) {
        /* check that rnd is a prime */
        BN_ULONG mod = BN_mod_word(rnd, (BN_ULONG)primes[i]);
        if (mod == (BN_ULONG)-1)
            goto err;
        if (mod <= 1) {
            if (!BN_add(rnd, rnd, add))
                goto err;
            goto loop;
        }
    }
    ret = 1;

 err:
    BN_CTX_end(ctx);
    bn_check_top(rnd);
    return ret;
}