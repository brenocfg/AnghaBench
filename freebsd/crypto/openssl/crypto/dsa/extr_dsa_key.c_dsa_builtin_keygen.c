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
struct TYPE_3__ {int /*<<< orphan*/ * priv_key; int /*<<< orphan*/ * pub_key; int /*<<< orphan*/  p; int /*<<< orphan*/  g; int /*<<< orphan*/  q; } ;
typedef  TYPE_1__ DSA ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_FLG_CONSTTIME ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_is_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_exp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  BN_priv_rand_range (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BN_secure_new () ; 
 int /*<<< orphan*/  BN_with_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dsa_builtin_keygen(DSA *dsa)
{
    int ok = 0;
    BN_CTX *ctx = NULL;
    BIGNUM *pub_key = NULL, *priv_key = NULL;

    if ((ctx = BN_CTX_new()) == NULL)
        goto err;

    if (dsa->priv_key == NULL) {
        if ((priv_key = BN_secure_new()) == NULL)
            goto err;
    } else
        priv_key = dsa->priv_key;

    do
        if (!BN_priv_rand_range(priv_key, dsa->q))
            goto err;
    while (BN_is_zero(priv_key)) ;

    if (dsa->pub_key == NULL) {
        if ((pub_key = BN_new()) == NULL)
            goto err;
    } else
        pub_key = dsa->pub_key;

    {
        BIGNUM *prk = BN_new();

        if (prk == NULL)
            goto err;
        BN_with_flags(prk, priv_key, BN_FLG_CONSTTIME);

        if (!BN_mod_exp(pub_key, dsa->g, prk, dsa->p, ctx)) {
            BN_free(prk);
            goto err;
        }
        /* We MUST free prk before any further use of priv_key */
        BN_free(prk);
    }

    dsa->priv_key = priv_key;
    dsa->pub_key = pub_key;
    ok = 1;

 err:
    if (pub_key != dsa->pub_key)
        BN_free(pub_key);
    if (priv_key != dsa->priv_key)
        BN_free(priv_key);
    BN_CTX_free(ctx);
    return ok;
}