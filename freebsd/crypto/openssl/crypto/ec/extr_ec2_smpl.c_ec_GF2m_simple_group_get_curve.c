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
struct TYPE_3__ {int /*<<< orphan*/  b; int /*<<< orphan*/  a; int /*<<< orphan*/  field; } ;
typedef  TYPE_1__ EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int ec_GF2m_simple_group_get_curve(const EC_GROUP *group, BIGNUM *p,
                                   BIGNUM *a, BIGNUM *b, BN_CTX *ctx)
{
    int ret = 0;

    if (p != NULL) {
        if (!BN_copy(p, group->field))
            return 0;
    }

    if (a != NULL) {
        if (!BN_copy(a, group->a))
            goto err;
    }

    if (b != NULL) {
        if (!BN_copy(b, group->b))
            goto err;
    }

    ret = 1;

 err:
    return ret;
}