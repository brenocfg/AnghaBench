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
struct TYPE_3__ {int /*<<< orphan*/ * priv_key; int /*<<< orphan*/ * pub_key; int /*<<< orphan*/  group; } ;
typedef  int /*<<< orphan*/  EC_POINT ;
typedef  TYPE_1__ EC_KEY ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_is_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  BN_priv_rand_range (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * EC_GROUP_get0_order (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_POINT_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_mul (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_POINT_new (int /*<<< orphan*/ ) ; 

int ec_key_simple_generate_key(EC_KEY *eckey)
{
    int ok = 0;
    BN_CTX *ctx = NULL;
    BIGNUM *priv_key = NULL;
    const BIGNUM *order = NULL;
    EC_POINT *pub_key = NULL;

    if ((ctx = BN_CTX_new()) == NULL)
        goto err;

    if (eckey->priv_key == NULL) {
        priv_key = BN_new();
        if (priv_key == NULL)
            goto err;
    } else
        priv_key = eckey->priv_key;

    order = EC_GROUP_get0_order(eckey->group);
    if (order == NULL)
        goto err;

    do
        if (!BN_priv_rand_range(priv_key, order))
            goto err;
    while (BN_is_zero(priv_key)) ;

    if (eckey->pub_key == NULL) {
        pub_key = EC_POINT_new(eckey->group);
        if (pub_key == NULL)
            goto err;
    } else
        pub_key = eckey->pub_key;

    if (!EC_POINT_mul(eckey->group, pub_key, priv_key, NULL, NULL, ctx))
        goto err;

    eckey->priv_key = priv_key;
    eckey->pub_key = pub_key;

    ok = 1;

 err:
    if (eckey->pub_key == NULL)
        EC_POINT_free(pub_key);
    if (eckey->priv_key != priv_key)
        BN_free(priv_key);
    BN_CTX_free(ctx);
    return ok;
}