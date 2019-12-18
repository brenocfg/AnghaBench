#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int flags; int length; int /*<<< orphan*/ * priv_key; int /*<<< orphan*/ * pub_key; int /*<<< orphan*/  p; int /*<<< orphan*/  g; TYPE_1__* meth; int /*<<< orphan*/  q; int /*<<< orphan*/  lock; int /*<<< orphan*/  method_mont_p; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* bn_mod_exp ) (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ DH ;
typedef  int /*<<< orphan*/  BN_MONT_CTX ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_FLG_CONSTTIME ; 
 int /*<<< orphan*/ * BN_MONT_CTX_set_locked (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_RAND_BOTTOM_ANY ; 
 int /*<<< orphan*/  BN_RAND_TOP_ONE ; 
 int /*<<< orphan*/  BN_clear_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_is_bit_set (int /*<<< orphan*/ ,int) ; 
 scalar_t__ BN_is_one (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_is_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ BN_is_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int BN_num_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_priv_rand (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_priv_rand_range (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BN_secure_new () ; 
 int /*<<< orphan*/  BN_with_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int DH_FLAG_CACHE_MONT_P ; 
 int /*<<< orphan*/  DH_F_GENERATE_KEY ; 
 int /*<<< orphan*/  DH_GENERATOR_2 ; 
 int /*<<< orphan*/  DH_R_MODULUS_TOO_LARGE ; 
 int /*<<< orphan*/  DHerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_BN_LIB ; 
 int OPENSSL_DH_MAX_MODULUS_BITS ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int generate_key(DH *dh)
{
    int ok = 0;
    int generate_new_key = 0;
    unsigned l;
    BN_CTX *ctx = NULL;
    BN_MONT_CTX *mont = NULL;
    BIGNUM *pub_key = NULL, *priv_key = NULL;

    if (BN_num_bits(dh->p) > OPENSSL_DH_MAX_MODULUS_BITS) {
        DHerr(DH_F_GENERATE_KEY, DH_R_MODULUS_TOO_LARGE);
        return 0;
    }

    ctx = BN_CTX_new();
    if (ctx == NULL)
        goto err;

    if (dh->priv_key == NULL) {
        priv_key = BN_secure_new();
        if (priv_key == NULL)
            goto err;
        generate_new_key = 1;
    } else
        priv_key = dh->priv_key;

    if (dh->pub_key == NULL) {
        pub_key = BN_new();
        if (pub_key == NULL)
            goto err;
    } else
        pub_key = dh->pub_key;

    if (dh->flags & DH_FLAG_CACHE_MONT_P) {
        mont = BN_MONT_CTX_set_locked(&dh->method_mont_p,
                                      dh->lock, dh->p, ctx);
        if (!mont)
            goto err;
    }

    if (generate_new_key) {
        if (dh->q) {
            do {
                if (!BN_priv_rand_range(priv_key, dh->q))
                    goto err;
            }
            while (BN_is_zero(priv_key) || BN_is_one(priv_key));
        } else {
            /* secret exponent length */
            l = dh->length ? dh->length : BN_num_bits(dh->p) - 1;
            if (!BN_priv_rand(priv_key, l, BN_RAND_TOP_ONE, BN_RAND_BOTTOM_ANY))
                goto err;
            /*
             * We handle just one known case where g is a quadratic non-residue:
             * for g = 2: p % 8 == 3
             */
            if (BN_is_word(dh->g, DH_GENERATOR_2) && !BN_is_bit_set(dh->p, 2)) {
                /* clear bit 0, since it won't be a secret anyway */
                if (!BN_clear_bit(priv_key, 0))
                    goto err;
            }
        }
    }

    {
        BIGNUM *prk = BN_new();

        if (prk == NULL)
            goto err;
        BN_with_flags(prk, priv_key, BN_FLG_CONSTTIME);

        if (!dh->meth->bn_mod_exp(dh, pub_key, dh->g, prk, dh->p, ctx, mont)) {
            BN_clear_free(prk);
            goto err;
        }
        /* We MUST free prk before any further use of priv_key */
        BN_clear_free(prk);
    }

    dh->pub_key = pub_key;
    dh->priv_key = priv_key;
    ok = 1;
 err:
    if (ok != 1)
        DHerr(DH_F_GENERATE_KEY, ERR_R_BN_LIB);

    if (pub_key != dh->pub_key)
        BN_free(pub_key);
    if (priv_key != dh->priv_key)
        BN_free(priv_key);
    BN_CTX_free(ctx);
    return ok;
}