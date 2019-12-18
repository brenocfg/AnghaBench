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
struct TYPE_3__ {int /*<<< orphan*/ * group; } ;
typedef  TYPE_1__ EC_KEY ;
typedef  int /*<<< orphan*/  BN_CTX ;

/* Variables and functions */
 int EC_GROUP_precompute_mult (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int EC_KEY_precompute_mult(EC_KEY *key, BN_CTX *ctx)
{
    if (key->group == NULL)
        return 0;
    return EC_GROUP_precompute_mult(key->group, ctx);
}