#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * g; int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ DH ;
typedef  int /*<<< orphan*/  BN_GENCB ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_GENCB_call (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_generate_prime_ex (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* BN_new () ; 
 int /*<<< orphan*/  BN_set_word (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  DH_F_DH_BUILTIN_GENPARAMS ; 
 int DH_GENERATOR_2 ; 
 int DH_GENERATOR_5 ; 
 int /*<<< orphan*/  DH_R_BAD_GENERATOR ; 
 int /*<<< orphan*/  DHerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_BN_LIB ; 

__attribute__((used)) static int dh_builtin_genparams(DH *ret, int prime_len, int generator,
                                BN_GENCB *cb)
{
    BIGNUM *t1, *t2;
    int g, ok = -1;
    BN_CTX *ctx = NULL;

    ctx = BN_CTX_new();
    if (ctx == NULL)
        goto err;
    BN_CTX_start(ctx);
    t1 = BN_CTX_get(ctx);
    t2 = BN_CTX_get(ctx);
    if (t2 == NULL)
        goto err;

    /* Make sure 'ret' has the necessary elements */
    if (!ret->p && ((ret->p = BN_new()) == NULL))
        goto err;
    if (!ret->g && ((ret->g = BN_new()) == NULL))
        goto err;

    if (generator <= 1) {
        DHerr(DH_F_DH_BUILTIN_GENPARAMS, DH_R_BAD_GENERATOR);
        goto err;
    }
    if (generator == DH_GENERATOR_2) {
        if (!BN_set_word(t1, 24))
            goto err;
        if (!BN_set_word(t2, 11))
            goto err;
        g = 2;
    } else if (generator == DH_GENERATOR_5) {
        if (!BN_set_word(t1, 60))
            goto err;
        if (!BN_set_word(t2, 23))
            goto err;
        g = 5;
    } else {
        /*
         * in the general case, don't worry if 'generator' is a generator or
         * not: since we are using safe primes, it will generate either an
         * order-q or an order-2q group, which both is OK
         */
        if (!BN_set_word(t1, 12))
            goto err;
        if (!BN_set_word(t2, 11))
            goto err;
        g = generator;
    }

    if (!BN_generate_prime_ex(ret->p, prime_len, 1, t1, t2, cb))
        goto err;
    if (!BN_GENCB_call(cb, 3, 0))
        goto err;
    if (!BN_set_word(ret->g, g))
        goto err;
    ok = 1;
 err:
    if (ok == -1) {
        DHerr(DH_F_DH_BUILTIN_GENPARAMS, ERR_R_BN_LIB);
        ok = 0;
    }

    BN_CTX_end(ctx);
    BN_CTX_free(ctx);
    return ok;
}