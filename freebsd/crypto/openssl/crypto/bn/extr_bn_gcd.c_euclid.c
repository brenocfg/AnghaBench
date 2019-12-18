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
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 scalar_t__ BN_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ BN_is_odd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_is_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_lshift (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BN_rshift1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_sub (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bn_check_top (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BIGNUM *euclid(BIGNUM *a, BIGNUM *b)
{
    BIGNUM *t;
    int shifts = 0;

    bn_check_top(a);
    bn_check_top(b);

    /* 0 <= b <= a */
    while (!BN_is_zero(b)) {
        /* 0 < b <= a */

        if (BN_is_odd(a)) {
            if (BN_is_odd(b)) {
                if (!BN_sub(a, a, b))
                    goto err;
                if (!BN_rshift1(a, a))
                    goto err;
                if (BN_cmp(a, b) < 0) {
                    t = a;
                    a = b;
                    b = t;
                }
            } else {            /* a odd - b even */

                if (!BN_rshift1(b, b))
                    goto err;
                if (BN_cmp(a, b) < 0) {
                    t = a;
                    a = b;
                    b = t;
                }
            }
        } else {                /* a is even */

            if (BN_is_odd(b)) {
                if (!BN_rshift1(a, a))
                    goto err;
                if (BN_cmp(a, b) < 0) {
                    t = a;
                    a = b;
                    b = t;
                }
            } else {            /* a even - b even */

                if (!BN_rshift1(a, a))
                    goto err;
                if (!BN_rshift1(b, b))
                    goto err;
                shifts++;
            }
        }
        /* 0 <= b <= a */
    }

    if (shifts) {
        if (!BN_lshift(a, a, shifts))
            goto err;
    }
    bn_check_top(a);
    return a;
 err:
    return NULL;
}