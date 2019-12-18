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
struct TYPE_6__ {int /*<<< orphan*/  prime_infos; int /*<<< orphan*/ * q; int /*<<< orphan*/ * p; } ;
struct TYPE_5__ {int /*<<< orphan*/ * r; int /*<<< orphan*/ * pp; } ;
typedef  TYPE_1__ RSA_PRIME_INFO ;
typedef  TYPE_2__ RSA ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_secure_new () ; 
 int sk_RSA_PRIME_INFO_num (int /*<<< orphan*/ ) ; 
 TYPE_1__* sk_RSA_PRIME_INFO_value (int /*<<< orphan*/ ,int) ; 

int rsa_multip_calc_product(RSA *rsa)
{
    RSA_PRIME_INFO *pinfo;
    BIGNUM *p1 = NULL, *p2 = NULL;
    BN_CTX *ctx = NULL;
    int i, rv = 0, ex_primes;

    if ((ex_primes = sk_RSA_PRIME_INFO_num(rsa->prime_infos)) <= 0) {
        /* invalid */
        goto err;
    }

    if ((ctx = BN_CTX_new()) == NULL)
        goto err;

    /* calculate pinfo->pp = p * q for first 'extra' prime */
    p1 = rsa->p;
    p2 = rsa->q;

    for (i = 0; i < ex_primes; i++) {
        pinfo = sk_RSA_PRIME_INFO_value(rsa->prime_infos, i);
        if (pinfo->pp == NULL) {
            pinfo->pp = BN_secure_new();
            if (pinfo->pp == NULL)
                goto err;
        }
        if (!BN_mul(pinfo->pp, p1, p2, ctx))
            goto err;
        /* save previous one */
        p1 = pinfo->pp;
        p2 = pinfo->r;
    }

    rv = 1;
 err:
    BN_CTX_free(ctx);
    return rv;
}