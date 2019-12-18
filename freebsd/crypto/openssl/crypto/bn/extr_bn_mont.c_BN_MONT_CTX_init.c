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
struct TYPE_3__ {scalar_t__ flags; scalar_t__* n0; int /*<<< orphan*/  Ni; int /*<<< orphan*/  N; int /*<<< orphan*/  RR; scalar_t__ ri; } ;
typedef  TYPE_1__ BN_MONT_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  bn_init (int /*<<< orphan*/ *) ; 

void BN_MONT_CTX_init(BN_MONT_CTX *ctx)
{
    ctx->ri = 0;
    bn_init(&ctx->RR);
    bn_init(&ctx->N);
    bn_init(&ctx->Ni);
    ctx->n0[0] = ctx->n0[1] = 0;
    ctx->flags = 0;
}