#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  N; int /*<<< orphan*/  ri; int /*<<< orphan*/  Ni; } ;
typedef  TYPE_1__ BN_MONT_CTX ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_add (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ BN_copy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_mask_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_rshift (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ BN_ucmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_usub (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bn_check_top (int /*<<< orphan*/ *) ; 
 int bn_from_montgomery_word (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 

int bn_from_mont_fixed_top(BIGNUM *ret, const BIGNUM *a, BN_MONT_CTX *mont,
                           BN_CTX *ctx)
{
    int retn = 0;
#ifdef MONT_WORD
    BIGNUM *t;

    BN_CTX_start(ctx);
    if ((t = BN_CTX_get(ctx)) && BN_copy(t, a)) {
        retn = bn_from_montgomery_word(ret, t, mont);
    }
    BN_CTX_end(ctx);
#else                           /* !MONT_WORD */
    BIGNUM *t1, *t2;

    BN_CTX_start(ctx);
    t1 = BN_CTX_get(ctx);
    t2 = BN_CTX_get(ctx);
    if (t2 == NULL)
        goto err;

    if (!BN_copy(t1, a))
        goto err;
    BN_mask_bits(t1, mont->ri);

    if (!BN_mul(t2, t1, &mont->Ni, ctx))
        goto err;
    BN_mask_bits(t2, mont->ri);

    if (!BN_mul(t1, t2, &mont->N, ctx))
        goto err;
    if (!BN_add(t2, a, t1))
        goto err;
    if (!BN_rshift(ret, t2, mont->ri))
        goto err;

    if (BN_ucmp(ret, &(mont->N)) >= 0) {
        if (!BN_usub(ret, ret, &(mont->N)))
            goto err;
    }
    retn = 1;
    bn_check_top(ret);
 err:
    BN_CTX_end(ctx);
#endif                          /* MONT_WORD */
    return retn;
}